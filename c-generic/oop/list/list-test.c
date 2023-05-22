/* 
 * Generic list structure (doubly linked) - test (BOJ 1406)
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2023-05-23
 */


#include		<stdio.h>
#include		<stdlib.h>
#include		"list.c"

char *new__Char(char c) { char *C = malloc(sizeof(char)); *C = c; return C; }

char s[100001];

int main()
{
	int i;
	char *c;

	List *li = new__List();
	
	scanf("%s", s);
	for (i = 0; s[i]; i++) {
		List__insert(li, li->tail, new__Char(s[i]));
	}

	int N;
	scanf("%d", &N);

	ListNode *it = li->tail;
	while (N--) {
		scanf("%s", s);
		switch (s[0]) {
		case 'P':
			scanf("%s", s);
			List__insert(li, it, new__Char(s[0]));
			break;
		case 'L':
			if (it != li->head)		it = it->prev;
			break;
		case 'D':
			if (it != li->tail)		it = it->next;
			break;
		case 'B':
			if (it != li->head)		it = List__erase(li, it->prev, 1);
			break;
		}
	}

	for (it = li->head; it != li->tail; it = it->next)
		printf("%c", *ListNode__item(it, char *));
	
	delete__List(li, 1);
}