#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *
 *
 */

char *_strdup(char *str)
{
char * dupli;
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