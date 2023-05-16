#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int skip_space(char *str, int i)
{
    while(str[i] == ' ')
        i++;
    return i;
}

void error_locate(char *str, int column)
{
    printf("%s\n", str);
    for(int i = 0; i < column; i++)
        printf(" ");
    printf("^\n");
}

int error(char *str, int column, char *error_str)
{
    error_locate(str, column);
    fprintf(stderr, "In column %d: %s\n", column, error_str);
    return -1;
}

int check_sim(char sim)
{
    if(isdigit(sim) != 0 || sim == '.')
        return 4;
    else if(sim == '*' || sim == '/' || sim == '-' || sim == '+')
        return 3;
    else if(sim == '(')
        return 2;
    else if(sim == ')')
        return 1;
    
    return 0;
}

int num_check(char *str, int *i)
{
    int d = 0;
    char buf[16];
    while(check_sim(str[(*i)]) == 4)
    {
        buf[d] = str[(*i)];
        d++;
        (*i)++;
    }
    if(str[(*i - d)] == '0')
        return 1;
    return atof(buf);
}

void output_error(char *str, int column, int mode)
{
    if(mode == -1)
        error(str, column, "uncorrect number");
    else if(mode == -2)
        error(str, column, "expected oper");
    else if(mode == -3)
        error(str, column, "expected number");
    else if(mode == -4)
        error(str, column, "unexpected token");
    else if(mode == -5)
        error(str, column, "expected ')'");
}

int str_check(char *str, int *column)
{
    int i = 0, res, bracket = 0;
    int oper = 0, num = 0;

    while(str[i] != '\0')
    {
        i = skip_space(str, i);
        res = check_sim(str[i]);
        if(res == 4)
        {
            if(num_check(str, &i) == 0)
            {
                *column = i;
                return -1;
            }
            if(oper == 0 && num == 1)
            {
                *column = i;
                return -2;
            }
            num = 1;
            oper = 0;
            continue;
        }

        if(res == 3)
        {
            if(oper == 1 && num == 0)
            {
                *column = i;
                return -3;
            }
            if(oper == 0 && num == 0 && (str[i] == '*' || str[i] == '/'))
            {
                *column = i;
                return -4;
            }
            oper = 1;
            num = 0;
        }

        if(res == 2)
        {
            if(num == 1)
            {
                *column = i;
                return -4;
            }
            bracket++;
            num = 0;
            oper = 0;
        }

        if(res == 1)
        {
            if(oper == 1)
            {
                *column = i;
                return -3;
            }
            if(num == 0)
            {
                *column = i;
                return -3;
            }
            if(bracket == 0)
            {
                *column = i;
                return -4;
            }
            bracket--;
        }

        if(res == 0)
        {
            *column = i;
            return -4;
        }

        i++;
    }
    if(bracket != 0)
    {
        *column = i;
        return -5;
    }
    if(oper == 1)
    {
        *column = i;
        return -3;
    }

    return 0;
}