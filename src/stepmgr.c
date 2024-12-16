#include "stepmgr.h"
#include "exec.h"
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void stepmgr_new(struct stepmgr *stepmgr, size_t stepsz)
{
	stepmgr->steps = malloc(stepsz * sizeof(struct step));
	if (!stepmgr->steps)
	{
		perror("malloc()");
		exit(1);
	}

	stepmgr->stepsz = stepsz;
	stepmgr->nr_steps = 0;
}

void stepmgr_add_step(struct stepmgr *stepmgr, struct step *step)
{
	if (stepmgr->nr_steps == stepmgr->stepsz)
	{
		printf("no more room\n");
		exit(1);
	}

	step_new(&stepmgr->steps[stepmgr->nr_steps++], step->name, step->cmd);
}

void
stepmgr_init(struct stepmgr *stepmgr,
						 const char *filepath,
						 char reset)
{
	int fd;
	if ((fd = open(filepath, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
	{
		perror("open()");
		exit(1);
	}

	if ((stepmgr->stream = fdopen(fd, "a+")) == NULL)
	{
		perror("fdopen()");
		exit(1);
	}

	if (reset)
	{
		exec("/bin/echo > %s", filepath);
		exec("/bin/rm /tmp/gpgpusim_rbind 2>/dev/null");
		// remove gpgpusim-use as well
		return;
	}

	ssize_t nread;
	size_t linesz;
	char *line = NULL;
	while ((nread = getline(&line, &linesz, stepmgr->stream)) != -1)
	{
		line[nread - 1] = 0;

		for (int i = 0; i < stepmgr->nr_steps; i++)
			if (!strncmp(stepmgr->steps[i].name, line, strlen(stepmgr->steps[i].name)))
			{
				stepmgr->steps[i].finished = 1;
				break;
			}
	}

	free(line);
}

void stepmgr_print(struct stepmgr *stepmgr)
{
	printf("Total number of steps: %d\n", stepmgr->stepsz);

	for (int i = 0; i < stepmgr->nr_steps; i++)
		step_print(&stepmgr->steps[i]);
}

void stepmgr_run(struct stepmgr *stepmgr, const char *logfile)
{
	int ret;

	for (int i = 0; i < stepmgr->nr_steps; i++)
	{
		struct step *this = &stepmgr->steps[i];
		if (this->finished)
		{
			printf("%s already done\n", this->name);
			continue;
		}

		printf("%s...", this->name);
		fflush(stdout);

		ret = exec("/bin/echo \"%s\" >> %s ; %s >> %s 2>> %s",
							 this->name, logfile, this->cmd, logfile, logfile);
		
		exec("/bin/echo '-----------------------------' >> %s", logfile);

		if (!ret)
		{
			printf(" DONE\n");
			stepmgr_save(stepmgr, i);
			continue;
		}

		printf("\n");
		printf("error occured while running: %s\n", this->cmd);
		printf("for more details see %s\n", logfile);
		printf("fix it manually then run this program again. dont worry your progess is saved :)\n");
		exit(1);
	}
}

void stepmgr_save(struct stepmgr *stepmgr, size_t step_idx)
{
	const char *name = stepmgr->steps[step_idx].name;

	size_t nwrite = fwrite(name, strlen(name), 1, stepmgr->stream);
	if (nwrite < 0)
	{
		perror("fwrite()");
		exit(1);
	}

	nwrite = fwrite("\n", 1, 1, stepmgr->stream);
	if (nwrite < 0)
	{
		perror("fwrite()");
		exit(1);
	}

	fflush(stepmgr->stream);
}
