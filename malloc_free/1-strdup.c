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
char *dupli; /* pointer to the duplicated string */
int len = 0; /* length of the original string */
int i; /* loop index */

if (str == NULL) /* NULL input: return NULL as per strdup behavior */
return (NULL);

while (str[len] != '\0') /* count characters to get string length */
len++;

dupli = malloc(sizeof(char) * (len + 1)); /* allocate len + 1 for '\0' */

if (dupli == NULL) /* check if malloc failed */
return (NULL);

for (i = 0; i <= len; i++) /* copy each character including '\0' */
dupli[i] = str[i];
return (dupli); /* return pointer to the duplicated string */
}
