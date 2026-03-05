#include "main.h"
#include <stddef.h>

/**
 * _strchr - locates the first occurrence of a character in a string
 * @s: string to search
 * @c: character to find
 *
 * Return: pointer to the first occurrence of c in s, or NULL if not found
 */
char *_strchr(char *s, char c)
{
int i = 0;

while (s[i] != '\0')
{
if (s[i] == c)
return (s + i);
i++;
}

/* Check if c is the null terminator */
if (c == '\0')
return (s + i);

return (NULL);
}
