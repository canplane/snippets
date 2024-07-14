#include <unistd.h>
#include <stdio.h>

#define BUFSZ 1024
char rbuf[BUFSZ], wbuf[BUFSZ] = "hi\n";

int main()
{
    int fdA[2], fdB[2];
    if (pipe(fdA) < 0 || pipe(fdB) < 0) {   // one pipe is unidirectional
        fprintf(stderr, "pipe error");
        return 1;
    }

    int pid;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error");
        return 2;
    }

    if (pid == 0) {     // child
        printf("<< (this is child)\n");
        close(fdA[0]), write(fdA[1], wbuf, BUFSZ);  // nonblocking send
        close(fdB[1]), read(fdB[0], rbuf, BUFSZ);   // blocking receive
        printf("<< %s", rbuf);
        printf("<< (child terminated)\n");
    }
    else {              // parent
        printf(">> (this is parent)\n");
        close(fdA[1]), read(fdA[0], rbuf, BUFSZ);   // blocking receive
        close(fdB[0]), write(fdB[1], wbuf, BUFSZ);  // nonblocking send
        printf(">> %s", rbuf);
        printf(">> (parent terminated)\n");
    }
}