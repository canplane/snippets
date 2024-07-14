#include <stdio.h>
#define SIZE    3

int *mkarr(int size);
void printarr(int *p, int size);

int main(void)
{
    int *arr;
    
    arr = mkarr(SIZE);

    arr[1] = 18;
    printf("arr[%d] %p : { ", SIZE, arr);
    for (int i = 0; i < SIZE; i++)
        printf("%d, ", arr[i]);
    printf("\b\b }\n");

    printarr(arr, 3);

    return 0;
}

int *mkarr(int size)
{
    int temp[size];
    // temp의 주소는 이전 호출과 같다는 보장이 없다. 스택 영역이다.
    // static(데이터 영역)으로 하면 runtime 시점에서 생성되는 것이 아니므로 에러가 뜬다.

    for (int i = 0; i < size; i++)
        temp[i] = i+1;

    printarr(temp, size);
    return temp;
    // 스택 영역의 포인터를 반환해서 이용하므로 다른 함수에서 제대로 이용할 수 없다.
    // 즉, 스택 영역에 대한 call by reference는 의미가 없다. 따라서 지역 범위 내의 가변 배열 선언은 다른 곳에서 쓸 수 없다. 
}

void printarr(int *p, int size)
{
    printf("arr[%d] %p : { ", size, p);
    for (int i = 0; i < size; i++)
        printf("%d, ", p[i]);
    printf("\b\b }\n");
}