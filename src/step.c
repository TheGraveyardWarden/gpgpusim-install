#include "step.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


void step_new(struct step *step, const char *name, const char *cmd)
{
	strncpy(step->name, name, STEP_NAME_SZ);
	strncpy(step->cmd, cmd, STEP_CMD_SZ);
	step->finished = 0;
}

void step_print(struct step *step)
{
	printf("step { name: %s, cmd: %s, finished: %s }\n",
				 step->name, step->cmd, step->finished ? "true" : "false");
}

void step_set_name(struct step *step, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(step->name, STEP_NAME_SZ, fmt, ap);
	va_end(ap);

	return;
}

void step_set_cmd(struct step *step, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(step->cmd, STEP_CMD_SZ, fmt, ap);
	va_end(ap);

	return;
}

