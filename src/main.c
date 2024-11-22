#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "stepmgr.h"
#include "rand_str.h"

static void usage(const char *prog)
{
	printf("usage: %s [OPTIONS]\n", prog);
	printf("\nOPTIONS:\n");
	printf("\t -r: restart the operation and ignore checkpoints\n");
	exit(1);
}

static struct step steps[] = {
	{ .name = "step 1", .cmd = "cat /etc/passwd" },
	{ .name = "step 2", .cmd = "cat /home/t5/Docs/gpgpusim-install/Makefile" },
	{ .name = "step 3", .cmd = "cat /etc/shadow" },
	{ .name = "step 4", .cmd = "ls /home/t5" },
	{ .name = "step 5", .cmd = "ls /opt" },
};

int main(int argc, char *argv[])
{
	struct stepmgr stepmgr;
	char logfile[64];
	char token[10];
	char reset = 0;
	int opt;

	while ((opt = getopt(argc, argv, "r")) != -1)
	{
		switch(opt)
		{
			case 'r':
				reset = 1;
				break;
			default:
				usage(argv[0]);
		}
	}

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

	stepmgr_run(&stepmgr, logfile);
}
