/* 
 * Generic dictionary structure - test (BOJ 20291)
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2023-05-22
 */


#include		<stdio.h>
#include		<stdlib.h>
#include		<string.h>
#include		"dict.c"

#define			sort(begin, end, cmp)					qsort((begin), (end) - (begin), sizeof(*(begin)), (cmp))
int static _cmp(const void *a, const void *b) { return strcmp(DictItem__key(*(DictItem **)a), DictItem__key(*(DictItem **)b)); }

char s[101];

int main()
{
	int N;
	scanf("%d", &N);

	Dict *d = new__Dict();
	while (N--) {
		scanf("%s", s);
		char *key = strstr(s, ".") + 1;		// find
		int *val = Dict__get(d, key, int *);
		if (!val)
			*(val = Dict__add(d, key, int *)) = 0;
		*val += 1;
	}

	DictItem **items = Dict__items(d);
	sort(items, items + d->size, _cmp);
	for (int i = 0; i < d->size; i++) {
		const DictItem *item = items[i];
		printf("%s %d\n", DictItem__key(item), *DictItem__val(item, int *));
	}
}