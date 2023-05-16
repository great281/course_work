typedef struct Stack_num
{
    double x;
    struct Stack_num *next;
}stack_num;

int empty_num(stack_num *s);

stack_num *push_num(stack_num *s, double x);

stack_num *pop_num(stack_num *s, double *value);

double top_num(stack_num *s);