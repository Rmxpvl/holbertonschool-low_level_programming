#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - prints numbers of base 16 in lowercase
 *
 * Return: Always 0
 */

int main(void)
{
int i = 0;
char c = 'a';

while (i <= 9)
{
putchar(i + '0');
i++;
}
while (c <= 'f')
{
putchar(c);
c++;
}

putchar('\n');
return (0);
}
