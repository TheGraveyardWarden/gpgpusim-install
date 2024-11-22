#ifndef _EXEC_H_
#define _EXEC_H_

/*	Runs cmd until completion.
 *	Return value:
 *		0 on success
 *		< 0 child was terminated by a signal. return value is signal number * -1
 *		> 0 return value is cmd exit status
 */
int exec(const char *cmd, ...);

#endif
