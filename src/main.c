#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "stepmgr.h"
#include "rand_str.h"

static void usage(const char *prog)
{
	printf("usage: %s [COMMANDS]\n", prog);
	printf("\nCOMMANDS:\n");
	printf("\t -r: restart the operation and ignore checkpoints\n");
	printf("\t -i: start installtion\n");
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
	char reset = 0;
	char install = 0;
	int opt;

	while ((opt = getopt(argc, argv, "ri")) != -1)
	{
		switch(opt)
		{
			case 'r':
				reset = 1;
				break;
			case 'i':
				install = 1;
				break;
			default:
				usage(argv[0]);
		}
	}

	if (!install && !reset)
		usage(argv[0]);

	if (geteuid() != 0)
	{
		printf("must be root\n");
		exit(1);
	}

	stepmgr_init(&stepmgr,
							 steps,
							 sizeof(steps) / sizeof(struct step),
							 "/etc/gpgpusim_checkpoint", reset);

	rand_str(token, 10);
	snprintf(logfile, 64, "/tmp/gpgpusim_install_%s.log", token);
	printf("Installing gpgpusim\nyou can use 'tail -f %s' to see what's happening\n", logfile);

	stepmgr_run(&stepmgr, logfile);
}
