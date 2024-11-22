#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int exec(const char *cmd) {
	pid_t pid;
	int wstatus, ret;

	pid = fork();
	if (pid == 0) {
		execl("/bin/sh", "/bin/sh", "-c", cmd, NULL);
		perror("execv()");
		exit(100);
	}
	else {
		if (waitpid(pid, &wstatus, 0) < 0) {
			perror("waitpid()");
			exit(1);
		}
		if (WIFEXITED(wstatus)) {
			ret = WEXITSTATUS(wstatus);
			return ret;
		}
		else if (WIFSIGNALED(wstatus)) {
			ret = WTERMSIG(wstatus);
			return ret * -1;
		}
	}

	// unreachable
	return 0;
}

