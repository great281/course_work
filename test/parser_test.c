#include <math.h>

#include "ctest.h"
#include "cmdclc/cmdcalc.h"

CTEST(correct_data, test_process_bracket)
{
    char *str = "3 + (5 - 2) * 3";
    int i = 0;
    const double answer = process(str, i);
    ASSERT_DBL_NEAR_TOL(12.0, answer, 1e-1);
}

CTEST(correct_data, test_process_negative_meaning)
{
    char *str = "-4 + (-3 + 2) * 2";
    int i = 0;
    const double answer = process(str, i);
    ASSERT_DBL_NEAR_TOL(-6.0, answer, 1e-1);
}

CTEST(correct_data, test_process_division_by_zero)
{
    char *str = "(2 + 5 - 3.5) / 0";
    int i = 0;
    const double answer = process(str, i);
    ASSERT_NOT_EQUAL(0, isinf(answer));
}

CTEST(correct_data, test_process_recursion)
{
    char *str = "( ( ( (1.1 - 2) + 3) * (2.5 * 2) ) + 10)";
    int i = 0;
    const double answer = process(str, i);
    ASSERT_DBL_NEAR_TOL(20.5, answer, 1e-1);
}

CTEST(correct_data, str_check)
{
    char *str = "2 + (-3) * 6";
    int i = 0;
    const int answer = str_check(str, &i);
    ASSERT_EQUAL(0, answer);
}

CTEST(uncorrect_data, str_check_num)
{
    char *str = "3 + .2 * 3";
    int i = 0;
    const int answer = str_check(str, &i);
    ASSERT_EQUAL(-1, answer);
    ASSERT_EQUAL(6, i);
}

CTEST(uncorrect_data, str_check_twice_num)
{
    char *str = "2.5 3.7 + 2.9";
    int i = 0;
    const int answer = str_check(str, &i);
    ASSERT_EQUAL(-2, answer);
    ASSERT_EQUAL(7, i);
}

CTEST(uncorrect_data, str_check_twice_oper)
{
    char *str = "2 +- 2";
    int i = 0;
    const int answer = str_check(str, &i);
    ASSERT_EQUAL(-3, answer);
    ASSERT_EQUAL(3, i);
}

CTEST(uncorrect_data, str_check_oper_main_position)
{
    char *str1 = "* 2 + 6";
    char *str2 = "/ 2 + 6";
    int column1 = 0, column2 = 0;
    const int answer1 = str_check(str1, &column1);
    const int answer2 = str_check(str2, &column2);
    ASSERT_EQUAL(-4, answer1);
    ASSERT_EQUAL(-4, answer2);
    ASSERT_EQUAL(0, column1);
    ASSERT_EQUAL(0, column2);
}

CTEST(uncorrect_data, str_check_opening_bracket)
{
    char *str1 = "2 + 2 (2 - 1)";
    char *str2 = "2 + 2 ?(2 - 1)";
    int column1 = 0, column2 = 0;
    const int answer1 = str_check(str1, &column1);
    const int answer2 = str_check(str2, &column2);
    ASSERT_EQUAL(-4, answer1);
    ASSERT_EQUAL(-4, answer2);
    ASSERT_EQUAL(6, column1);
    ASSERT_EQUAL(6, column2);
}

CTEST(uncorrect_data, str_check_unexpected_token)
{
    char *str = "3 * 6.5 + (10 - c2) * 4.2";
    int i = 0;
    const int answer = str_check(str, &i);
    ASSERT_EQUAL(-4, answer);
    ASSERT_EQUAL(16, i);
}

CTEST(uncorrect_data, str_check_not_found_close_bracket)
{
    char *str = "(2 + ( 3 - 1) * 6";
    int i = 0;
    const int answer = str_check(str, &i);
    ASSERT_EQUAL(-5, answer);
}

CTEST(uncorrect_data, str_check_empty_brackets)
{
    char *str = "2 + 2 - ()";
    int i = 0;
    const int answer = str_check(str, &i);
    ASSERT_EQUAL(-3, answer);
}