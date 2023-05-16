#include "cmdcalc.h"

int main(int argc, char *argv[])
{
    double x;
    int rez, column;

    if(argc != 2)
    {
        printf("Использование: ./cmdcalc \"<выражение>\"\n");
        exit(EXIT_FAILURE);
    }

    rez = str_check(argv[1], &column);
    if(rez != 0)
    {
        output_error(argv[1], column, rez);
        return -1;
    }

    x = process(argv[1], 0);
    printf("cmdcalc> %.1lf\n", x);
    
    return 0;
}