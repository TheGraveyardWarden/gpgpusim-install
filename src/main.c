#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "stepmgr.h"
#include "rand_str.h"
#include "exec.h"

#define STEPMGR_STEP_SZ 0x10

enum command {
	COMMAND_NONE = 0,
	COMMAND_INSTALL,
	COMMAND_REINSTALL,
};

static void usage(const char *prog)
{
	printf("usage: %s COMMAND [OPTIONS]\n", prog);
	printf("\nCOMMANDS:\n");
	printf("\t reinstall: restart the operation and ignore checkpoints\n");
	printf("\t install: start installation\n");
	printf("\nOPTIONS\n");
	printf("\t -g: path to gcc 5 tar file (if not present it will be downloaded)\n");
	printf("\t -c: path to cuda 9 run file (if not present it will be downloaded)\n");
	printf("\t -d: path to install debian (if not present /opt/wheezy)\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	struct stepmgr stepmgr;
	char logfile[64];
	char token[10];
	char *gccpath = NULL, *cudapath = NULL, *debpath = NULL;
	int opt;
	enum command command = COMMAND_NONE;

	while ((opt = getopt(argc, argv, "g:c:d:")) != -1)
	{
		switch(opt)
		{
			case 'g':
				gccpath = optarg;
				break;
			case 'c':
				cudapath = optarg;
				break;
			case 'd':
				debpath = optarg;
				break;
			default:
				usage(argv[0]);
		}
	}

	if (!argv[optind])
		usage(argv[0]);

	if (!strncmp("install", argv[optind], 7))
		command = COMMAND_INSTALL;
	else if (!strncmp("reinstall", argv[optind], 9))
		command = COMMAND_REINSTALL;

	if (command == COMMAND_NONE)
		usage(argv[0]);

	if (!debpath)
		debpath = "/opt/wheezy";

	if (!cudapath)
	{
		if (exec("./scripts/download.sh 'https://developer.nvidia.com/compute/cuda/9.0/Prod/local_installers/cuda_9.0.176_384.81_linux-run' ./assets/cuda_9.run") != 0)
		{
			printf("download failed\nrun the program again to continue download.\n");
			exit(1);
		}
		cudapath = "./assets/cuda_9.run";
	}

	if (!gccpath)
	{
		if (exec("./scripts/download.sh 'https://s32.picofile.com/d/8480766934/15eaf298-3d2d-4036-9d89-e7a3d950c8df/gcc_5_debs.tar' ./assets/gcc-5.debs.tar") != 0)
		{
			printf("download failed\nrun the program again to continue download.\n");
			exit(1);
		}
		gccpath = "./assets/gcc-5.debs.tar";
	}

	if (geteuid() != 0)
	{
		printf("must be root\n");
		exit(1);
	}

	stepmgr_new(&stepmgr, STEPMGR_STEP_SZ);

	struct step step;
	step.finished = 0;
	step_set_name(&step, "Installing Debian 7 in %s", debpath);
	step_set_cmd(&step, "debootstrap wheezy %s http://archive.debian.org/debian", debpath);
	stepmgr_add_step(&stepmgr, &step);

	step_set_name(&step, "Setup fresh installed debian's environment");
	step_set_cmd(&step, "./scripts/setup_env.sh %s", debpath);
	stepmgr_add_step(&stepmgr, &step);

	step_set_name(&step, "Installing gcc 5");
	step_set_cmd(&step, "./scripts/install-gcc-5.sh %s %s", debpath, gccpath);
	stepmgr_add_step(&stepmgr, &step);

	step_set_name(&step, "Installing cuda 9");
	step_set_cmd(&step, "./scripts/install-cuda-9.sh %s %s", debpath, cudapath);
	stepmgr_add_step(&stepmgr, &step);

	step_set_name(&step, "Cloning gpgpusim");
	step_set_cmd(&step, "/bin/git clone https://github.com/thegraveyardwarden/gpgpusim.git");
	stepmgr_add_step(&stepmgr, &step);

	step_set_name(&step, "Installing gpgpusim in %s", debpath);
	step_set_cmd(&step, "./scripts/install-gpgpusim.sh %s", debpath);
	stepmgr_add_step(&stepmgr, &step);

	stepmgr_init(&stepmgr,
							 "/etc/gpgpusim_checkpoint",
							 command == COMMAND_REINSTALL);

	rand_str(token, 10);
	snprintf(logfile, 64, "/tmp/gpgpusim_install_%s.log", token);
	printf("Installing gpgpusim\nyou can use 'tail -f %s' to see what's happening\n", logfile);

	stepmgr_run(&stepmgr, logfile);

	return 0;
}
