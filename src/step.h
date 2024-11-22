#ifndef _STEP_H_
#define _STEP_H_

struct step
{
	char *name, *cmd;
	char finished;
};

void step_new(struct step *step, const char *name, const char *cmd);
void step_print(struct step *step);

#endif
