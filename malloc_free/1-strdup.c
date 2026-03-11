#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _strdup - duplicates a string in memory (using malloc).
 * @str: the string to duplicate.
 * Return: a pointer to the duplicated string, or NULL if str is NULL
 * or malloc fails.
 */

char *_strdup(char *str)
{
char *dupli;
int len = 0;
int i;
if (str == NULL)
return (NULL);

while (str[len] != '\0')
len++;

dupli = malloc(sizeof(char) * (len + 1));

if (dupli == NULL)
return (NULL);

for (i = 0; i <= len; i++)
dupli[i] = str[i];
return (dupli);
}
