#include <stdlib.h>

#include "stack_oper.h"

stack_oper *stack_oper_init(stack_oper *s, char x)
{
    s = malloc(sizeof(stack_oper *));
    s->next = NULL;
    s->x = x;
    return s;
}

int empty_oper(stack_oper *s)
{
    if(s == NULL)
        return 1;
    else
        return 0;
}

stack_oper *push_oper(stack_oper *s, char x)
{
    if(empty_oper(s))
    {
        s = stack_oper_init(s, x);
        if(empty_oper(s))
            return NULL;

        return s;
    }

    stack_oper *node = NULL;
    node = malloc(sizeof(stack_oper *));
    
    if(empty_oper(node))
        return NULL;
    node->next = s;
    node->x = x;

    return node;
}

stack_oper *pop_oper(stack_oper *s, char *sim)
{
    if(empty_oper(s))
        return NULL;

    *sim = s->x;
    stack_oper *node = s;

    s = s->next;
    free(node);

    return s;
}

char top_oper(stack_oper *s)
{
    if(empty_oper(s))
        return -1;
    return s->x;
}