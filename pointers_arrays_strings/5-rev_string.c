#include "main.h"
#include <stdio.h>

/**
 * rev_string - Reverses a string
 * @s: pointer to the string to be reversed
 * Description: This function takes a pointer to a string and
 * reverses the string in place.
 * Return: Nothing
 */

void rev_string(char *s)
{
int i;
int len = 0;
char tmp;

while (s[len] != '\0')
len++;

for (i = 0; i < len / 2; i++)
{
tmp = s[i];
s[i] = s[len - 1 - i];
s[len - 1 - i] = tmp;
}
}
