#ifndef _STEP_H_
#define _STEP_H_

#define STEP_NAME_SZ 128
#define STEP_CMD_SZ  128

struct step
{
	char name[STEP_NAME_SZ];
	char cmd[STEP_CMD_SZ];
	char finished;
};

void step_new(struct step *step, const char *name, const char *cmd);
void step_print(struct step *step);

#endif
