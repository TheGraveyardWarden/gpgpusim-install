#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "stepmgr.h"
#include "rand_str.h"

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

static struct step steps[] = {
	{ .name = "Installing Debian 7 in /opt/wheezy", .cmd = "/bin/debootstrap wheezy /opt/wheezy http://archive.debian.org/debian" },
	{ .name = "Setup fresh installed debian's environment", .cmd = "./scripts/setup_env.sh" },
	{ .name = "Installing gcc 5", .cmd = "./scripts/install-gcc-5.sh" },
};

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

	if (geteuid() != 0)
	{
		printf("must be root\n");
		exit(1);
	}

	stepmgr_init(&stepmgr,
							 steps,
							 sizeof(steps) / sizeof(struct step),
							 "/etc/gpgpusim_checkpoint",
							 command == COMMAND_REINSTALL);

	rand_str(token, 10);
	snprintf(logfile, 64, "/tmp/gpgpusim_install_%s.log", token);
	printf("Installing gpgpusim\nyou can use 'tail -f %s' to see what's happening\n", logfile);

	stepmgr_run(&stepmgr, logfile);
}
