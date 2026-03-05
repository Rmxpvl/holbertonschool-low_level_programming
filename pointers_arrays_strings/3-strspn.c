#include "main.h"

/**
 * _strspn - gets the length of a prefix substring
 * @s: string to be scanned
 * @accept: string containing the bytes to match
 *
 * Return: number of bytes in the initial segment of s
 *         which consist only of bytes from accept
 */
unsigned int _strspn(char *s, char *accept)
{
unsigned int count = 0;
int j;
int matched;

while (s[count] != '\0')
{
matched = 0;
for (j = 0; accept[j] != '\0'; j++)
{
if (s[count] == accept[j])
{
matched = 1;
break;
}
}
if (!matched)
break;
count++;
}

return (count);
}
