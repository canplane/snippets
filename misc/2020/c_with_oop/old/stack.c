/* 
 * OOP study
 * ---------------- 
 * Sanghoon Lee (canplane@gmail.com)
 * 2020-12-09
 */


#include    <stdio.h>
#include    <stdlib.h>
#include    <stdbool.h>


#define     new(typename, args...)      (__new_##typename(args))


/* stack */

typedef int StackItemType;
typedef struct __Stack Stack;

bool __Stack_empty(Stack *);
bool __Stack_push(Stack *, StackItemType);
StackItemType __Stack_pop(Stack *);

struct __Stack {
    /* members */
    StackItemType *data;
    unsigned int top, length;

    /* methods */
    bool (*empty)(Stack *);                     // bool (*empty)(void) ?
    bool (*push)(Stack *, StackItemType);       // bool (*push)(StackItemType) ? 
    StackItemType (*pop)(Stack *);              // StackItemType (*pop)(void) ?
};

Stack *__new_Stack(unsigned int length)
{
    Stack *stack;
    stack = malloc(sizeof(Stack));
    stack->data = malloc(length * sizeof(StackItemType));
    stack->length = length;
    stack->top = -1;

    stack->empty = __Stack_empty;
    stack->push = __Stack_push;
    stack->pop = __Stack_pop;
    return stack;
}
bool __Stack_empty(Stack *stack)
{
    return stack->top == -1;
}
bool __Stack_push(Stack *stack, StackItemType e)
{
    if (stack->top == stack->length - 1)
        return false;
    stack->data[++stack->top] = e;
    return true;
}
StackItemType __Stack_pop(Stack *stack)
{
    if (stack->top == -1)
        return -1;
    return stack->data[stack->top--];
}


/* main */

int main()
{
    Stack *stack;
    stack = new(Stack, 5);

    stack->push(stack, 7);                      // stack->push(7) ?
    stack->push(stack, 5);                      // stack->push(5) ?
    stack->push(stack, 3);                      // stack->push(3) ?
    stack->push(stack, 9);                      // stack->push(9) ?
    stack->push(stack, 1);
    
    while (!stack->empty(stack)) {              // stack->empty() ?
        printf("%d\n", stack->pop(stack));      // stack->pop() ?
    }

    return 0;
}