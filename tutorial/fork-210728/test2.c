// orphan process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();
	
	if (pid < 0) {
		fprintf(stderr, "An error occured\n");
	}
	else if (pid == 0) {
		printf("Child Process : %i\n", getppid());
		sleep(3);
		printf("Child Process : %i\n", getppid());
	}
	else {
		sleep(1);
		printf("Parent Process : Fork off and die\n");
		exit(0);
	}
}
