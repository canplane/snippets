/* 
 * Generic dictionary structure
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2023-05-11
 */


#ifndef			__DICT__H
#define			__DICT__H




#include		<stdlib.h>
#include		<string.h>
#include		"list.c"




#define			__DICT__LISTS_SZ 						47

typedef struct DictItem { char *key; void *val; } DictItem;
typedef struct Dict { List *lists[__DICT__LISTS_SZ]; int size; } Dict;

#define			DictItem__key(item)						((item)->key)
#define			DictItem__val(item, T)					(*(T *)((item)->val))




Dict *new__Dict()
{
	Dict *d;
	d = malloc(sizeof(Dict));
	for (int i = 0; i < __DICT__LISTS_SZ; i++)
		d->lists[i] = new__List();
	return d;
}




int __Dict__key_to_idx(char *s)
{
	int ret = 0;
	for (int i = 0; s[i]; i++)		ret += s[i];
	return ret % __DICT__LISTS_SZ;
}

#define Dict__get(d, key, T) (*(T *)__Dict__get(d, key, sizeof(T)))
void *__Dict__get(Dict *d, char *key, int T_sz)
{
	int idx = __Dict__key_to_idx(key);

	List *li = d->lists[idx];
	ListNode *node;
	DictItem *item;
	for (node = li->head; node; node = node->next)
		if (!strcmp(key, (item = node->item)->key))		break;
	if (!node) {
		d->size++;
		item = malloc(sizeof(DictItem));
		item->key = strdup(key);
		item->val = malloc(T_sz), memset(item->val, 0, T_sz);
		List__push(li, item);
	}

	return item->val;
}

DictItem **Dict__items(Dict *d)
{
	DictItem **arr = malloc(d->size * sizeof(void *)), **p;
	p = arr;
	for (int i = 0; i < __DICT__LISTS_SZ; i++)
		for (ListNode *node = d->lists[i]->head; node; node = node->next)
			*p++ = (DictItem *)node->item;
	return arr;
}




#endif