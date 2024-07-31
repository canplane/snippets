typedef int element;

struct node {
    element item;
    struct node *link;
};

/* stack */
void push(struct node **stack, element e)
{
    struct node *node = (struct node *)malloc(sizeof(*node));
    node->item = e;
    node->link = *stack;
    *stack = node;
}

void pop(struct node **stack)
{
    struct node *node = *stack;
    *stack = *stack->link;
    free(node);
}

element top(struct node **stack)
{
    return *stack;
}

bool empty(struct node **stack)
{
    return *stack != NULL;
}