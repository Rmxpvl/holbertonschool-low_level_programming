#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * create_array - creates an array of chars and initializes it with a
 * specific char.
 * @size: the size of the array to create.
 * @c: the char to initialize the array with.
 * Return: a pointer to the array, or NULL if size is 0 or malloc fails.
 */
char *create_array(unsigned int size, char c)
{
char *array;
unsigned int i;
if (size == 0)
return (NULL);


array = malloc(sizeof(char) * size);

if (array == NULL)
return (NULL);
for (i = 0; i < size; i++)
{
array[i] = c;
}
return (array);
}
