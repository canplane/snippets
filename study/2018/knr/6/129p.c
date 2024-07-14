/* C99에서 부분적으로 가능한 가변인자 배열 선언 및 컴퓨터 구조에 대한 고찰 */

#include <stdio.h>

int arr1[5];
// 전역 배열 : 메모리 할당은 상수로만 지정할 수 있고, 0으로 초기화된다.
int *mkarr(char* name, int size);
void printarr(char *name, int *p, int size);

int main(void)
{
    int arr2[5];
    // 지역 배열 : 0으로 초기화되지 않는다.
    int *arr3, *arr4;
    int n;

    // arr0 : 표준 입력으로 가변 배열 선언
    scanf("%d", &n);
    int arr0[n];
    for (int i = 0; i < n; i++)
        arr0[i] = i+1;
    printarr("arr0", arr0, n);
    printf("\n");

    // arr1 : 전역 고정 배열
    printarr("arr1", arr1, 5);
    printf("\n");

    // arr2 : 지역 고정 배열
    printarr("arr2", arr2, 5);
    printf("\n");
    
    // arr3
    arr3 = mkarr("arr3", 3);

    arr3[1] = 7;
    printf("arr3[1] == %d\n", arr3[1]);

    printarr("arr3", arr3, 3);
    printf("\n");

    // arr4
    arr4 = mkarr("arr4", 5);
    printarr("arr4", arr4, 5);
    printf("\n");
    return 0;
}

int *mkarr(char* name, int size)
{
    int temp[size];
    // temp의 주소는 이전 호출과 같다는 보장이 없다. 스택 영역이다.
    // static(데이터 영역)으로 하면 runtime 시점에서 생성되는 것이 아니므로 에러가 뜬다.
    printf("[ MKARR() : INITIALIZED ]\n");    

    for (int i = 0; i < size; i++)
        temp[i] = i+1;

    printarr(name, temp, size);

    printf("[ MKARR() : EXITED ]\n");
    return temp;
    // 스택 영역의 포인터를 반환해서 이용하므로 다른 함수에서 제대로 이용할 수 없다.
    // 즉, 스택 영역에 대한 call by reference는 의미가 없다. 따라서 지역 범위 내의 가변 배열 선언은 다른 곳에서 쓸 수 없다. 
}

void printarr(char *name, int *p, int size)
{
    printf("[ PRINTARR() : INITIALIZED ]\n");

    printf("%s[%d] %p : { ", name, size, p);
    for (int i = 0; i < size; i++)
        printf("%d, ", p[i]);
    printf("\b\b }\n");

    printf("[ PRINTARR() : EXITED ]\n");
}