#include <stdlib.h>


#include "stack/stack_num.h"
#include "stack/stack_oper.h"

extern int skip_space(char *str, int i);

int skip(char *str, int i)
{
    while(str[i] != ')')
    {
        if(str[i] == '(')
            i = skip(str, ++i);
        else
            i++;
    }
    i++;
    i = skip_space(str, i);
    return i;
}

int char_number(char x)
{
    if(atof(&x) == 0 && x != '.' && x != '0')               
        return -1;
    return 0;
}

int char_oper(char x)
{
    if(x == '*' || x == '/')
        return 2;
    else if(x == '-')
        return 1;
    else if(x == '+')
        return 0;
    else if(x == '(')
        return -1;
    else if(x == ')')
        return -2;
    return -3;
}

stack_num *get_number(stack_num *s, char *str, int *i)
{
    *i = skip_space(str, *i);

    if(str[*i] == '.')
        return NULL;
    char buf[16];
    double res;
    int d = 0;
    while(char_number(str[*i]) == 0)
    {
        buf[d] = str[*i];
        *i += 1;
        d++;
    }
    buf[d] = '\0';

    if((res = atof(buf)) == 0 && buf[0] != '0')
        return NULL;
    if((s = push_num(s, res)) == NULL)
        return NULL;

    *i = skip_space(str, *i);
    return s;
}

stack_oper *get_oper(stack_oper *s, char *str, int *i)
{   
    *i = skip_space(str, *i);

    if((s = push_oper(s, str[*i])) == NULL)
        return NULL;
    *i += 1;
    *i = skip_space(str, *i);

    return s;
}

stack_num *calculate(stack_num *num, stack_oper *oper, char oper_now)
{
    double first, second, res;
    char oper_next = 0;
    if(empty_oper(oper) == 0)
        oper_next = top_oper(oper);
    
    num = pop_num(num, &second);
    num = pop_num(num, &first);
    if(oper_now == '*')
        res = first * second;
    else if(oper_now == '/')
        res = first / second;
    else if(oper_now == '-')
    {
        if(oper_next == oper_now)
            res = first + second;
        else
            res = first - second;
    }
    else
    {
        if(oper_next == oper_now || oper_next == 0)
            res = first + second;
        else
            res = first - second;
    }
    
    num = push_num(num, res);

    return num;
}

stack_num *calculate_all(stack_num *num, stack_oper *oper)
{
    char x;
    while(empty_oper(oper) != 1 && num->next != NULL)
    {
        oper = pop_oper(oper, &x);
        num = calculate(num, oper, x);
    }
    if(top_oper(oper) == '-')
        num->x *= -1;
    return num;
}

double process(char *str, int i)
{
    stack_num *num = NULL;
    stack_oper *oper = NULL;
    char x;
    double res;
    int num_it = 0;
    int check;

    i = skip_space(str, i);
    while(str[i] != '\0')
    {
        if(char_number(str[i]) == 0)
        {
            num = get_number(num, str, &i);
            num_it = 1;
        }
        else if((check = char_oper(str[i])) >= 0)
        {
            oper = get_oper(oper, str, &i);
            num_it = 0;
        }
    
        if(check == 2  && num_it == 1)
        {
            oper = pop_oper(oper, &x);
            num = calculate(num, oper, x);
            num_it = 0;
        }
        else if(check == -1)
        {
            i++;
            res = process(str, i);
            num = push_num(num, res);
            i = skip(str, i);
            num_it = 1;
        }
        else if(check == -2)
            break;
    }
    num = calculate_all(num, oper);

    return num->x;
}