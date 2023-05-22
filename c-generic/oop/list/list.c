/* 
 * Generic list structure (doubly linked)
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2023-05-23
 */


#ifndef			__LIST__H
#define			__LIST__H



#include		<stdio.h>
#include		<stdlib.h>




typedef struct ListNode { void *item; struct ListNode *prev, *next; } ListNode;
typedef struct List { int size; ListNode *head, *tail; } List;

#define			ListNode__item(node, T)					((T)((node)->item))




ListNode *__new__ListNode(ListNode *prev, ListNode *next, void *item)
{
	ListNode *node = malloc(sizeof(ListNode));
	node->item = item;
	node->prev = prev, node->next = next;
	return node;
}




List *new__List()
{
	ListNode *node = __new__ListNode(NULL, NULL, NULL);
	
	List *li = malloc(sizeof(List));
	li->size = 0;
	li->head = li->tail = node;

	return li;
}
void delete__List(List *li, int _free_item)
{
	ListNode *node, *tmp;
	for (node = li->head; node != li->tail; node = tmp) {
		tmp = node->next;
		if (_free_item)		free(node->item);
		free(node);
	}
	free(li->tail);
	free(li);
}




#define			List__insert(li, next, item)			__List__insert((li), (next), (void *)(item))
ListNode *__List__insert(List *li, ListNode *next, void *item)
{
	ListNode *prev = next->prev;

	li->size++;
	ListNode *node = __new__ListNode(prev, next, item);

	if (prev)
		prev->next = node;
	else
		li->head = node;
	next->prev = node;
	return node;
}
ListNode *List__erase(List *li, ListNode *node, int _free_item)
{
	if (node == li->tail) {
		fprintf(stderr, "Error: list index out of range\n");
		exit(1);
	}

	ListNode *prev = node->prev, *next = node->next;

	li->size--;
	if (_free_item)		free(node->item);
	free(node);

	if (prev)
		prev->next = next;
	else
		li->head = next;
	next->prev = prev;
	return next;
}




#endif