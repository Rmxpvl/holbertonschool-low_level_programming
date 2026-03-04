#include "main.h"
#include <stdio.h>

/**
 * main - check the code
 *
 * Return: Always 0.
 */

void rev_string(char *s)
{
int len = 0; i;
char tmp;

while (s[len] != '\0')
    len++;

    for (i = 0; i < len / 2; i++)
{
    char tmp = s[i];
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = tmp;
}
}
