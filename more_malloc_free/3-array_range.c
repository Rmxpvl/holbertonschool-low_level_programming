/* Include function prototypes used in this project. */
#include "main.h"
/* Include malloc and NULL definitions. */
#include <stdlib.h>
/**
 * array_range - creates an array of integers
 * @min: minimum value (included)
 * @max: maximum value (included)
 *
 * Return: pointer to the new array, or NULL on failure
 */
int *array_range(int min, int max)
{
/* Pointer that will store the address of the new array. */
int *array;
/* Number of integers we need to allocate. */
unsigned int size;
/* Loop index used to fill the array. */
unsigned int i;

/* If range is invalid, there is no array to create. */
if (min > max)
return (NULL);

/* Compute how many values exist from min to max included. */
size = (unsigned int)(max - min + 1);
/* Allocate memory for "size" integers. */
array = malloc(sizeof(int) * size);
/* Return NULL if memory allocation failed. */
if (array == NULL)
return (NULL);

/* Visit each position of the allocated array. */
for (i = 0; i < size; i++)
/* Store consecutive values starting at min. */
array[i] = min + i;

/* Return the pointer to the filled array. */
return (array);
}
