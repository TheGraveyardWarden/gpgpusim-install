#include "step.h"
#include <string.h>
#include <stdio.h>

void step_new(struct step *step, const char *name, const char *cmd)
{
	strncpy(step->name, name, STEP_NAME_SZ);
	strncpy(step->cmd, cmd, STEP_CMD_SZ);
	step->finished = 0;
}

void step_print(struct step *step)
{
	printf("step { name: %s, finished: %s }\n",
				 step->name, step->finished ? "true" : "false");
}
