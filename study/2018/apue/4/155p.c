/* Test to make hard link for regular file */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    if (link("tempfile", "../tempfile") < 0)
        perror(NULL);
    return 0;
}

/*
ls -l 명령을 통해 st_nlink의 값이 2가 바뀐 것을 알 수 있다.
그런데 파인더를 통해 기존 주소(하드 링크)의 파일을 열고 메모장으로 바꾸고 저장하면
새로 생성한 주소의 데이터와 같지 않아진다는 것을 발견할 수 있다.
또한 st_nlink 값이 다시 1로 돌아가 있다.
다른 방법으로 cat file > <하드 링크>로 데이터를 저장하면 st_nlink 값도 변하지 않으며
모든 링크에 대해 변경된 데이터가 동기화되어 있는 것을 발견할 수 있다.
즉, 개념 상의 문제는 없으며 메모장 프로그램을 통해 저장하는 과정이
새 데이터 블록을 생성하여 기록하고, 이전 데이터 블록에 대하여 링크 해제를 하는 방식이라고 파악된다.
*/