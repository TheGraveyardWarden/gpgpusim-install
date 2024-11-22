#ifndef _STEPMGR_H_
#define _STEPMGR_H_

#include "step.h"
#include <stdio.h>

struct stepmgr {
	struct step *steps;
	size_t stepsz, nr_steps;
	FILE *stream; // this is checkpoint file
};

void stepmgr_new(struct stepmgr *stepmgr, size_t stepsz);
void stepmgr_add_step(struct stepmgr *stepmgr, struct step *step);

void
stepmgr_init(struct stepmgr *stepmgr,
						 const char *filepath,
						 char reset);

void stepmgr_print(struct stepmgr *stepmgr);
void stepmgr_run(struct stepmgr *stepmgr, const char *logfile);
void stepmgr_save(struct stepmgr *stepmgr, size_t step_idx);

#endif
