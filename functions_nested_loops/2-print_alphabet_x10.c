#include "main.h"

/**
 * print_alphabet - Program print alphabet lowercase x10
 */

void print_alphabet(void)
{
char c;
int i;
for (i = 0; i < 10; i++)
	for (c = 'a'; c <= 'z'; c++)
	{
		_putchar(c);
	}
	_putchar('\n');
}
