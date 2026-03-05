#include "main.h"
#include <stddef.h>

/**
 * _strstr - locates a substring
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: pointer to the beginning of the located substring,
 *         or NULL if not found
 */
char *_strstr(char *haystack, char *needle)
{
int i, j;

if (needle[0] == '\0')
return haystack;

for (i = 0; haystack[i] != '\0'; i++)
{
for (j = 0; needle[j] != '\0'; j++)
{
if (haystack[i + j] != needle[j])
break;
}
if (needle[j] == '\0') /* entire needle matched */
return haystack + i;
}

return (NULL);
}
