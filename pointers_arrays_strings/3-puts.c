#include "main.h"
#include <stdio.h>

/**
 * _puts - Prints a string followed by a new line
 * @str: pointer to the string to be printed
 * Description: This function takes a pointer to a string and
 * prints the string to the standard output, followed by a new line.
 */

void _puts(char *str)
{
int i = 0;

while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}

_putchar('\n');
}
