#include <grp.h>
#include <unistd.h>
#include <stdio.h>
#define MAXLEN  16

gid_t gr_gids[MAXLEN];

int main(void)
{
    int n;
    struct group *p;

    if ((n = getgroups(MAXLEN, gr_gids)) < 0)
        return -1;
    
    for (int i = 0; i < n; i++)
    {
        p = getgrgid(*(gr_gids+i));
        printf("%s[%u]\n", p->gr_name, *(gr_gids+i));
    }
    return 0;
}