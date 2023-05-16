#include <stdlib.h>

#include "stack_num.h"

stack_num *stack_num_init(stack_num *s, double x)
{
    s = malloc(sizeof(stack_num *));
    s->next = NULL;
    s->x = x;
    return s;
}

int empty_num(stack_num *s)
{
    if(s == NULL)
        return 1;
    else
        return 0;
}

stack_num *push_num(stack_num *s, double x)
{
    if(empty_num(s))
    {
        s = stack_num_init(s, x);
        if(empty_num(s))
            return NULL;

        return s;
    }

    stack_num *node = NULL;
    node = malloc(sizeof(stack_num *));
    
    if(empty_num(node))
        return NULL;
    node->next = s;
    node->x = x;

    return node;
}

stack_num *pop_num(stack_num *s, double *value)
{
    if(empty_num(s))
        return NULL;

    *value = s->x;
    stack_num *node = s;

    s = s->next;
    free(node);

    return s;
}

double top_num(stack_num *s)
{
    if(empty_num(s))
        return -1;
    return s->x;
}