#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * create_array - creates an array of chars and initializes it with a
 * specific char.
 * Objective: Allocate a block of memory of 'size' bytes using malloc,
 * then fill every byte with the character 'c'. This demonstrates the
 * basic use of malloc to create a dynamically-sized buffer at runtime.
 * @size: the size of the array to create.
 * @c: the char to initialize the array with.
 * Return: a pointer to the array, or NULL if size is 0 or malloc fails.
 */
char *create_array(unsigned int size, char c)
{
char *array; /* pointer to the new array */
unsigned int i; /* loop index */

if (size == 0) /* cannot create an array of size 0 */
return (NULL);

array = malloc(sizeof(char) * size); /* allocate memory for the array */

if (array == NULL) /* check if malloc failed */
return (NULL);
for (i = 0; i < size; i++) /* fill each element with the given char */
{
array[i] = c; /* set current element to c */
}
return (array); /* return pointer to the filled array */
}
