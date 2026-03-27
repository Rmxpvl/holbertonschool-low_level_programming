#include "main.h"

/**
 * _puts_recursion - prints a string followed by a new line
 * @s: string to print
 */
void _puts_recursion(char *s)
{
int i = 0;

while (s[i] != '\0')
i++;

i--; // se placer sur le dernier caractère

while (i >= 0)
{
printf("%c", s[i]);
i--;
}
}

int main(void)
{
_print_rev_recursion("hello");
return 0;
}
