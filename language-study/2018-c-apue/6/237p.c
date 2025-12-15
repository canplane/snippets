// 추가 그룹 ID들 중에 패스워드 파일에서의 그룹 ID가 포함되어 있는 것 같다.
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct passwd   *pwbuf;
    struct group    *grbuf;
    gid_t           *grouplist, *ptr;
    int             gidsetsize;
    
    pwbuf = getpwuid(getuid());
    //pwbuf = getpwnam(argv[1]);
    /*
    setpwent();
    if (argc > 1) {
        while ((pwbuf = getpwent()) != NULL)
            if (!strcmp(pwbuf->pw_name, argv[1]))
                break;
    }
    else {
        while ((pwbuf = getpwent()) != NULL)
            if (pwbuf->pw_uid == getuid())
                break;
    }
    endpwent();
    */
    printf("Welcome, %s!\n", pwbuf->pw_gecos);
    
    grbuf = getgrgid(getgid());
    //grbuf = getgrgid(pwbuf->pw_gid);
    /*
    setgrent();
    while ((grbuf = getgrent()) != NULL)
        if (pwbuf->pw_gid == grbuf->gr_gid)
            break;
    endgrent();
    */
    printf("The name of group ID : %s\n", grbuf->gr_name);

    /*
    printf("%u, %u, %u, %u, %u\n", getuid(), pwbuf->pw_uid, getgid(), grbuf->gr_gid, pwbuf->pw_gid);
    : uid, gid끼리는 모두 같은 값이 나온다.
    */

    gidsetsize = getgroups(0, NULL);
    grouplist = ptr = (gid_t *)malloc(gidsetsize * sizeof(gid_t));
    
    getgroups(gidsetsize, grouplist);
    printf("The Names of Supplementary group IDs : {\n");
    while (gidsetsize-- > 0) {
        grbuf = getgrgid(*ptr++);
        printf("\t%s\n", grbuf->gr_name);
    }
    printf("}\n");
    free(grouplist);

    return 0;
}