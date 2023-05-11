/* 
 * Generic dictionary structure - test (BOJ 20291)
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2023-05-11
 */


#include		<stdio.h>
#include		<stdlib.h>
#include		<string.h>
#include		"dict.c"

#define			sort(begin, end, cmp)					qsort((begin), (end) - (begin), sizeof(*(begin)), (cmp))

int static __cmp(const void *_a, const void *_b)
{
	DictItem *a = *((DictItem **)_a), *b = *((DictItem **)_b);
	return strcmp(DictItem__key(a), DictItem__key(b));
}

char strbuf[101];

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
	sort(items, items + d->size, __cmp);
	for (int i = 0; i < d->size; i++) {
		const DictItem *item = items[i];
		printf("%s %d\n", DictItem__key(item), DictItem__val(item, int));
	}
}