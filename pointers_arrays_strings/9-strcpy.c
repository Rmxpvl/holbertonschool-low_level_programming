#include "main.h"
#include <stdio.h>

/**
 * _strcpy - Copies the string pointed to by src with null
 * @dest: pointer to the destination
 * @src: pointer to the source string to be copied
 * Description: Takes two pointers to char, dest and src, and copies the string
 */

char *_strcpy(char *dest, char *src)
{
int i = 0;
while (src[i] != '\0')
{dest[i] = src[i];
i++;
}
dest[i] = '\0';
return (dest);
}
