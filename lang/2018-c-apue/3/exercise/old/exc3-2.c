#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int
main (int argc, char* argv[])
{
    char* path;
    int d1, d2;

    if (argc != 2)
        printf("Command Line Arguments Error!");
// how do I use stdin without command line argument? in stdin, only I know file description...
    else
    {
        path = argv[1];
        if ((d1 = open(path, O_RDONLY)) < 0)
            printf("File Open Error!");
        else
        {
            d2 = open(path, O_RDONLY);
            printf("%d %d", d1, d2);
            close(d1);
            close(d2);
        }
    }
    printf("\n");
    return 0;
}
