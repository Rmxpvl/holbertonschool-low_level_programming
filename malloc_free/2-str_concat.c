#include "main.h"
#include <stdlib.h>

/**
 * str_concat - concatenates two strings into a new string allocated with
 * malloc.
 * @s1: the first string. If NULL, treated as an empty string.
 * @s2: the second string. If NULL, treated as an empty string.
 * Return: a pointer to the new concatenated string, or NULL if malloc fails.
 */

char *str_concat(char *s1, char *s2)
{
int len1 = 0;
int len2 = 0;
char *concat;

if (s1 == NULL)
s1 = "";
if (s2 == NULL)
s2 = "";

while (s1[len1] != '\0')
len1++;

while (s2[len2] != '\0')
len2++;

concat = malloc(sizeof(char) * (len1 + len2 + 1));

if (concat == NULL)
return (NULL);

int i, j;
for (i = 0; i < len1; i++)
{
concat[i] = s1[i];
}
for (j = 0; j < len2; j++)
{
concat[i + j] = s2[j];
}
concat[i + j] = '\0';
return (concat);
}
