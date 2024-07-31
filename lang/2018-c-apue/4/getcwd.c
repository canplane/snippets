#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXSIZE 1000

int main(void)
{
    DIR *dp;
    struct dirent *drp;
    char path_pwd[MAXSIZE] = ".";       // 작업 디렉터리를 기준으로 한 루트 디렉터리의 상대 경로
    char path[MAXSIZE] = "";            // 작업 디렉터리의 절대 경로
    char path_tmp[MAXSIZE];
    struct stat *stbuf = (struct stat *)malloc(sizeof(struct stat));
    ino_t ino_current, ino_parent, ino_whence;
    
    stat("/", stbuf);                   // 현재 디렉터리(.)의 아이노드가 루트 디렉터리의 아이노드와 같은지 판별
    while (1)
    {
        dp = opendir(path_pwd);
        while ((drp = readdir(dp)) != NULL)
        {
            if (!strcmp(drp->d_name, "."))  // 현재 디렉터리(.)의 아이노드
                ino_current = drp->d_ino;
            else if (!strcmp(drp->d_name, ".."))
                ino_parent = drp->d_ino;    // 부모 디렉터리(..)의 아이노드
            else if (strcmp(path_pwd, "./") && drp->d_ino == ino_whence)
            // 작업 디렉터리로부터 최소 한번 이상 거슬러 올라간 시점에서 어떤 자식에서 거슬러 왔는지 판별하고, 그 아이노드를 지칭하는 디렉터리 이름을 절대 경로에 붙인다. 
            {
                if (!strcmp(path, ""))  // 한번 거슬러 올라간 경우 (절대 경로의 마지막 문자열에 /를 붙이지 않기 위해서 경우를 나눴다.)
                    strcat(path, drp->d_name);
                else                    // 그 다음부터
                {
                    snprintf(path_tmp, MAXSIZE, "%s/%s", drp->d_name, path);
                    strcpy(path, path_tmp); // 문자열 수정이니까 버퍼에 임시 저장하고 다시 복사해야 함.
                }
            }
            else
                continue;
        }
        closedir(dp);
        
        if (stbuf->st_ino != ino_current)   // 현재 디렉터리의 아이노드가 루트 디렉터리의 아이노드와 같지 않으면,
        {
            ino_whence = ino_current;       // 더 거슬러 올라가기 전에 현재 디렉터리의 아이노드를 기록한다.
            strcat(path_pwd, "/..");        // 그리고 거슬러 올라갈 상대 경로도 추가한다. (작업 디렉터리는 바꾸지 않음)
        }
        else
        {
            snprintf(path_tmp, MAXSIZE, "/%s", path);   // 같으면 처음 문자열에 /를 추가한다.
            strcpy(path, path_tmp);
            break;
        }
    }
    free(stbuf);
    printf("%s\n", path);
    
    return 0;
}