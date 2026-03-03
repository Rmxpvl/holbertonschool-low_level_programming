#include "main.h"
#include <stdio.h>

/**
 * _strlen - Returns the length of a string
 * @s: pointer to the string to be measured
 * Description: This function takes a pointer to a string and
 * Return: The length of the string.
 */

int _strlen(char *s)
{
int length = 0;
while (s[length] != '\0')
{
length++;
}
return (length);
}
