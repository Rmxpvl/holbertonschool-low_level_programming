#include "main.h"

/**
 * main - prints the digits numbers of base 10 starting from 0
 * print_numbers - Show results
 * Return - Always 0
 */

void print_numbers(void)
{
char n = '0';
while (n <= '9')
{
_putchar(n);
n++;
}
_putchar('\n');
}
