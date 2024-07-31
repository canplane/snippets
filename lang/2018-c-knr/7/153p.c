#include <stdio.h>

main()
{
    char *s = "string\n";
    printf(s);

    int i = 65;
    double f = 12.34;

    printf("%.3s %.8s", s, s);
    printf("%.3d %.3f\n", i, f);
    printf("%.1d %.1f\n", i, f);
}