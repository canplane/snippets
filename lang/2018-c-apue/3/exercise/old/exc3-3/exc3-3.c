#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int
main (void)
{
    int input, output1, output2, input_dup, n;
    char buf1[4096], buf2[4096];

    input = open("input", O_RDONLY);

    output1 = open("output1", O_WRONLY);
    output2 = open("output2", O_WRONLY);

    printf("input : %d, input_dup : %d\n", input, input_dup = fcntl(input, F_DUPFD, 0)); //fcntl | dup
    
    printf("input_bufsize : %d\n", n = pread(input, buf1, 4096, 0L)); //read -> pread | read & lseek (caution! : offset)
    write(output1, buf1, n);
    
    printf("input_dup_bufsize : %d\n", n = pread(input_dup, buf2, 4096, 0L));
    write(output2, buf2, n);

    printf("close(input) return : %d\n", close(input));
    printf("close(input_dup) return : %d\n", close(input_dup));
    close(output1);
    close(output2);

    printf("\n");
    return 0;
}
