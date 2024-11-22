#include "step.h"
#include <string.h>
#include <stdio.h>

void step_new(struct step *step, const char *name, const char *cmd)
{
	step->name = (char*)name;
	step->cmd = (char*)cmd;
	step->finished = 0;
}

void step_print(struct step *step)
{
	printf("step { name: %s, finished: %s }\n",
				 step->name, step->finished ? "true" : "false");
}
