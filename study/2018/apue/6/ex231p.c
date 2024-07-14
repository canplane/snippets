#include <pwd.h>
#include <stddef.h>     /* to refer to NULL */
#include <string.h>

struct passwd *
getpwnam(const char *name)
{
    struct passwd   *ptr;

    setpwent();         /* 호출자가 이미 getpwent를 호출했을 가능성을 대비 */
    while ((ptr = getpwent()) != NULL)
        if (strcmp(name, ptr->pw_name) == 0)
            break;      /* 부합하는 항목을 발견 */
    endpwent();
    return(ptr);        /* 부함하는 항목을 발견하지 못했으면 ptr는 NULL임 */
}