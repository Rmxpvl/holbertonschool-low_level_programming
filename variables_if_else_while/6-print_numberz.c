#include <stdio.h>
/**
 * main - prints the numbers 0 to 9 without using char
 *
 * Return: Always 0
 */

int main(void)
{
int i = 0;

while (i <= 9)
{
putchar(i + '0');
i++;
}

putchar('\n');
return (0);
}
