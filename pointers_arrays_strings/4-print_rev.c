#include "main.h"
#include <stdio.h>

/**
 * print_rev - Prints a string in reverse followed by a new line
 * @s: pointer to the string to be printed in reverse
 * Description: This function takes a pointer to a string and
 * prints the string in reverse to the standard output, followed by a new line.
 * Return: Nothing
 */

void print_rev(char *s)
{
int len = 0;

while (s[len] != '\0')
len++;

while (len > 0)
{
len--;
_putchar(s[len]);
}

_putchar('\n');
}
