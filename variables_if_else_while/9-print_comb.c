#include <stdio.h>

/**
 * main - prints numbers 1 to 9 and space them with (, space)
 *
 * Return: Always 0
 */

int main(void)
{
int i;

for (i = 0; i <= 9; i++)
{
	putchar(i + '0');
		if (i != 9)
		{
			putchar(',');
			putchar(' ');
		}
}

	putchar('\n');
	return (0);
}
