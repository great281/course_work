typedef struct Stack_oper
{
    char x;
    struct Stack_oper *next;
}stack_oper;

int empty_oper(stack_oper *s);

stack_oper *push_oper(stack_oper *s, char x);

stack_oper *pop_oper(stack_oper *s, char *sim);

char top_oper(stack_oper *s);