/* 
 * fork return test
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2021-07-28
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	int status = -1;

	pid = fork();

	if (pid < 0)
		;
	else if (pid == 0)
		exit(-1);
	else
		printf("%i %i, %i %i\n", pid, wait(&status), status, WEXITSTATUS(status));  // (status >> 8) & 0xff);

	return 0;
}
