/* 
 * Generic dictionary structure - test
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2023-05-11
 */


#include <stdio.h>
#include "dict.c"


char strbuf[101];

int static __cmp(const void *_a, const void *_b)
{
    DictItem *a = *((DictItem **)_a), *b = *((DictItem **)_b);
    return strcmp(DictItem__key(a), DictItem__key(b));
}

int main()
{
    int N;
    scanf("%d", &N);

    Dict *d = new__Dict();
    while (N--) {
        scanf("%s", strbuf);
        char *key = strstr(strbuf, ".") + 1;
        Dict__get(d, key, int) += 1;
    }
    DictItem **items = Dict__items(d);
    qsort(items, d->size, sizeof(DictItem *), __cmp);

    for (int i = 0; i < d->size; i++) {
        const DictItem *item = items[i];
        printf("%s %d\n", DictItem__key(item), DictItem__val(item, int));
    }
}