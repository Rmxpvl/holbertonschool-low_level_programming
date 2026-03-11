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
int len1 = 0; /* length of first string */
int len2 = 0; /* length of second string */
int i, j; /* loop indices */
char *concat; /* pointer to the new concatenated string */

if (s1 == NULL) /* treat NULL as empty string */
s1 = "";
if (s2 == NULL) /* treat NULL as empty string */
s2 = "";

while (s1[len1] != '\0') /* compute length of s1 */
len1++;

while (s2[len2] != '\0') /* compute length of s2 */
len2++;

concat = malloc(sizeof(char) * (len1 + len2 + 1)); /* allocate space for both strings + '\0' */

if (concat == NULL) /* check if malloc failed */
return (NULL);

for (i = 0; i < len1; i++) /* copy s1 into concat */
{
concat[i] = s1[i]; /* copy character from s1 */
}
for (j = 0; j < len2; j++) /* copy s2 after s1 */
{
concat[i + j] = s2[j]; /* copy character from s2 */
}
concat[i + j] = '\0'; /* null-terminate the result */
return (concat); /* return pointer to the new string */
}
