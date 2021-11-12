/* 
 * fork and cwd test
 * 210728
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

char buf[1024];

int main(int argc, char *argv[])
{
	printf("%s %s\n", argv[0], getcwd(buf, 1024));

	pid_t pid;

	pid = fork();
	
	if (pid < 0) {
		fprintf(stderr, "An error occured\n");
	}
	else if (pid == 0) {
		printf("Child Process : %i\n", getpid());
	}
	else {
		wait(NULL);
		printf("Parent Process : %i\n", pid);
	}
}
