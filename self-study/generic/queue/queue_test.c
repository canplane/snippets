#include		<stdio.h>
#include		"queue.c"

#define			MAXNUM				10

int main()
{
	int _q_container[MAXNUM + 1];
	Queue q = Queue__init(_q_container);

	for (int i = 0; i < MAXNUM; i++) {
		Queue__push(&q, i);
	}
	while (!Queue__empty(&q)) {
		printf("%d\n", Queue__front(&q, int));
		Queue__pop(&q);
	}
}