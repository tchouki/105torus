/*
** EPITECH PROJECT, 2018
** 105torus
** File description:
** main.c
*/

#include "include/my.h"

int print_help(void)
{
    printf("USAGE\n");
    printf("\t./105torus opt a0 a1 a2 a3 a4 n\n\n");
    printf("DESCRIPTION\n");
    printf("\topt\tmethod option:\n");
    printf("\t\t\t1 for the bisection method\n");
    printf("\t\t\t2 for Newton’s mehod\n");
    printf("\t\t\t3 for the secant method\n");
    printf("\ta[0-4]\tcoefficients of the equation\n");
    printf("\tn\tprecision (the application of the polynomial to the solution should\n");
    printf("\t\tbe smaller than 10ˆ-n)\n");
    return (0);
}

int check_number(char **argv)
{
    if ((argv[1][0] < '0' || argv[1][0] > '9') && argv[1][0] != '-')
        return (0);
    if ((argv[2][0] < '0' || argv[2][0] > '9') && argv[2][0] != '-')
        return (0);
    if ((argv[3][0] < '0' || argv[3][0] > '9') && argv[3][0] != '-')
        return (0);
    if ((argv[4][0] < '0' || argv[4][0] > '9') && argv[4][0] != '-')
        return (0);
    if ((argv[5][0] < '0' || argv[5][0] > '9') && argv[5][0] != '-')
        return (0);
    if ((argv[6][0] < '0' || argv[6][0] > '9') && argv[6][0] != '-')
        return (0);
    if ((argv[7][0] < '0' || argv[7][0] > '9') && argv[7][0] != '-')
        return (0);
    return (1);
}

int get_digit(double nb, int digit)
{
    nb *= pow(10, digit);
    for (int n = 0; nb > 9 && n < digit; n++)
        nb = fmod(nb, pow(10, digit - n));
    return (nb);
}

int check_pres(double nb, int max)
{
    int size = 15;

    for (; get_digit(nb, size) == 0; size--);
    return (size > max ? max : size);
}

int bisection(char **argv)
{
    double left = 0;
    double right = 1;
    double result = (left + right) / 2;
    double a = (atof(argv[6]) * pow(left, 4)) + (atof(argv[5]) * pow(left, 3)) + (atof(argv[4]) * pow(left, 2)) + (atof(argv[3]) * left) + atof(argv[2]);
    double b = (atof(argv[6]) * pow(right, 4)) + (atof(argv[5]) * pow(right, 3)) + (atof(argv[4]) * pow(right, 2)) + (atof(argv[3]) * right) + atof(argv[2]);
    double c = (atof(argv[6]) * pow(result, 4)) + (atof(argv[5]) * pow(result, 3)) + (atof(argv[4]) * pow(result, 2)) + (atof(argv[3]) * result) + atof(argv[2]);
    double n = pow(10, -(atof(argv[7])));
    int i = -1;

    if (fabs(c) < n)
      printf("x = %.*f\n", check_pres(result, atoi(argv[7])), result);
    while (fabs(c) > n && ++i < 50)
      {
        result = (left + right) / 2;
        a = (atof(argv[6]) * pow(left, 4)) + (atof(argv[5]) * pow(left, 3)) + (atof(argv[4]) * pow(left, 2)) + (atof(argv[3]) * left) + atof(argv[2]);
        b = (atof(argv[6]) * pow(right, 4)) + (atof(argv[5]) * pow(right, 3)) + (atof(argv[4]) * pow(right, 2)) + (atof(argv[3]) * right) + atof(argv[2]);
        c = (atof(argv[6]) * pow(result, 4)) + (atof(argv[5]) * pow(result, 3)) + (atof(argv[4]) * pow(result, 2)) + (atof(argv[3]) * result) + atof(argv[2]);
        if ((a * c) < 0)
          right = result;
        else
          left = result;
        printf("x = %.*f\n", check_pres(result, atoi(argv[7])), result);
    }
    return (0);
}

int newton(char **argv)
{
    double result = 0.5;
    double n = pow(10, -(atoi(argv[7])));
    int i = -1;
    double a = (atof(argv[6]) * pow(result, 4)) + (atof(argv[5]) * pow(result, 3)) + (atof(argv[4]) * pow(result, 2)) + (atof(argv[3]) * result) + atof(argv[2]);
    double b = (4 * atof(argv[6]) * pow(result, 3)) + (3 * atof(argv[5]) * pow(result, 2)) + (2 * atof(argv[4]) * result) + (atof(argv[3]) * result);
    double c = result - (a / b);
    double d = (atof(argv[6]) * pow(c, 4)) + (atof(argv[5]) * pow(c, 3)) + (atof(argv[4]) * pow(c, 2)) + (atof(argv[3]) * c) + atof(argv[2]);

    if (fabs(a) < n)
        printf("x = %.*f\n", check_pres(result, atoi(argv[7])), result);
    while (fabs(d) > n && i <= 250) {
        a = (atof(argv[6]) * pow(result, 4)) + (atof(argv[5]) * pow(result, 3)) + (atof(argv[4]) * pow(result, 2)) + (atof(argv[3]) * result) + atof(argv[2]);
        b = (4 * atof(argv[6]) * pow(result, 3)) + (3 * atof(argv[5]) * pow(result, 2)) + (2 * atof(argv[4]) * result) + (atof(argv[3]) * result);
        d = (atof(argv[6]) * pow(c, 4)) + (atof(argv[5]) * pow(c, 3)) + (atof(argv[4]) * pow(c, 2)) + (atof(argv[3]) * c) + atof(argv[2]);
        if (b == 0)
            return (84);
        printf("x = %.*f\n", check_pres(result, atoi(argv[7])), result);
        c = result - (a / b);
        result = c;
        i++;
    }
    return (0);
}

int secant(char **argv)
{
    double left = 0;
    double right = 1;
    double a = (atof(argv[6]) * pow(left, 4)) + (atof(argv[5]) * pow(left, 3)) + (atof(argv[4]) * pow(left, 2)) + (atof(argv[3]) * left) + atof(argv[2]);
    double b = (atof(argv[6]) * pow(right, 4)) + (atof(argv[5]) * pow(right, 3)) + (atof(argv[4]) * pow(right, 2)) + (atof(argv[3]) * right) + atof(argv[2]);
    double result = right - (b * (right - left) / (b - a));
    double c = (atof(argv[6]) * pow(result, 4)) + (atof(argv[5]) * pow(result, 3)) + (atof(argv[4]) * pow(result, 2)) + (atof(argv[3]) * result) + atof(argv[2]);
    double n = pow(10, -atof(argv[7]));
    int i = -1;

    if (fabs(c) < n)
        printf("x = %.*f\n", check_pres(result, atoi(argv[7])), result);
    if (i >= 250)
        return (84);
    while (fabs(c) > n) {
        a = (atof(argv[6]) * pow(left, 4)) + (atof(argv[5]) * pow(left, 3)) + (atof(argv[4]) * pow(left, 2)) + (atof(argv[3]) * left) + atof(argv[2]);
        b = (atof(argv[6]) * pow(right, 4)) + (atof(argv[5]) * pow(right, 3)) + (atof(argv[4]) * pow(right, 2)) + (atof(argv[3]) * right) + atof(argv[2]);
        if (b - a == 0)
            return (84);
        result = right - (b * (right - left) / (b - a));
        c = (atof(argv[6]) * pow(result, 4)) + (atof(argv[5]) * pow(result, 3)) + (atof(argv[4]) * pow(result, 2)) + (atof(argv[3]) * result) + atof(argv[2]);
        left = right;
        right =result;
        printf("x = %.*f\n", check_pres(result, atoi(argv[7])), result);
    }
    return (0);
}

int main(int argc, char **argv)
{
    /* PRINT HELP IF ARGV = -h */
    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h')
        return (print_help());
    /* BAD ARGUMENTS */
    if (argc != 8)
        return (84);
    /* CHECK IF ONLY NUMBER */
    if (!check_number(argv))
        return (84);
    /* CALCUL */
    if (atoi(argv[1]) == 1)
        return (bisection(argv));
    if (atoi(argv[1]) == 2)
        return (newton(argv));
    if (atoi(argv[1]) == 3)
        return (secant(argv));
    return (84);
}
