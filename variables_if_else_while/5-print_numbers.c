#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - prints the digits numbers of base 10 starting from 0
 *
 * Return: Always 0
 */

int main(void)
{

char n = '0';

while (n <= '9')
{
putchar(n);
n++;
}
putchar('\n');
return (0);
}
