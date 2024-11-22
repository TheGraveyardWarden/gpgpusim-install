#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdarg.h>


int exec(const char *cmd, ...) {
	pid_t pid;
	int wstatus, ret;
	va_list ap;
	char *c = NULL;
	size_t size = 0;

	va_start(ap, cmd);
	ret = vsnprintf(c, size, cmd, ap);
	va_end(ap);

	if (ret < 0) {
		return -1;
	}

	size = (size_t)ret + 1;
	c = malloc(size);
	if (c == NULL) {
		return -1;
	}

	va_start(ap, cmd);
	ret = vsnprintf(c, size, cmd, ap);
	va_end(ap);

	if (ret < 0) {
		free(c);
		return -1;
	}

	pid = fork();
	if (pid == 0) {
		execl("/bin/sh", "/bin/sh", "-c", c, NULL);
		perror("execv()");
		exit(100);
	}
	else {
		free(c);
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

