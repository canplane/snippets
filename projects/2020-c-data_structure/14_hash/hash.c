/* hash
 * 20200208
 * index = hash(id), ht[index], identifier는 key라고도 함
 * hashing function으로 division(%)을 이용 (대표적으로 mid-square, division, folding, digit analysis이 있음)
 * division 이용 시 M(bucket)을 2의 power에서 너무 가깝지 않은 수로 선택하는 것이 좋다. (M이 짝수면 짝은 짝, 홀은 홀로만 들어가고, M이 2의 power - 1이면 h("abcd") == h("bdac")가 됨)
 * overflow handling으로 open addressing(probing, rehashing) 대신 chaining 이용
 * static hashing
 */

#include <stdio.h>
#include <stdarg.h>
#include "list.h"

typedef struct {
    int key;
    char tag;
} Element;

#define BUCKET 47 // primes : ..., 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, ...
Node *ht[BUCKET];

int hash(void *id, int len)
{
    int idx;
    idx = 0;
    while (len--)
        idx = (idx + *((char *)id++)) % BUCKET;
    return idx;
}

void setData(Element data[], int size, ...)
{
    int i;
    Node *node;
    va_list ap;
    int key, idx;
    char tag;

    va_start(ap, size);
    for (i = 0; i < size; i++) {
        key = va_arg(ap, int);
        idx = hash(&key, sizeof(int));

        tag = 'a';
        for (node = ht[idx]; node; node = node->next)
            if (data[node->item].key == key) {
                tag = data[node->item].tag + 1;
                break;
            }
        data[i].key = key, data[i].tag = tag;

        list_insert(&ht[idx], NULL, i);
    }
    va_end(ap);
}

void printData(Element data[], int size)
{
    while (size--) {
        printf("%d%c ", data->key, data->tag);
        data++;
    }
    printf("\n");
}

/* main */

// 13_sort/data.h 참고
/*
#define DATASZ 16
int main()
{
    Element data[DATASZ];
    setData(data, DATASZ, 5, 5, 3, 4, 5, 1, 0, 4, 1, 3, 0, 2, 4, 2, 3, 0);

    printData(data, DATASZ);
    return 0;
}
*/