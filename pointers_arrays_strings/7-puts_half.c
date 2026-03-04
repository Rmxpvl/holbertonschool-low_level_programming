#include "main.h"

/**
 * puts_half - prints the second half of a string
 * @str: string to print
 * Description: This function takes a pointer to a string and
 * prints the second half of the string to the standard output, followed by a new line.
*/

void puts_half(char *str)
{
int len = 0;
int start,
int i;

while (str[len] != '\0')
len++;

start = (len + 1) / 2,

for ( i = start; i < len; i++)

_putchar(str[i]);
_putchar('\n');
}
