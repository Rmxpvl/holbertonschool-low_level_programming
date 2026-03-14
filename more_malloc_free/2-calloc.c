#include "main.h"
#include <stdlib.h>
/**
 * _calloc - allocates memory for an array, using malloc
 * @nmemb: number of elements in the array
 * @size: size of each element
 * Return: pointer to the allocated memory, or NULL if it fails
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	/* Store the address of allocated memory. */
	void *ptr;
	/* Track loop index and total number of bytes. */
	unsigned int i, total_size;

	/* Return NULL when allocation size is invalid. */
	if (nmemb == 0 || size == 0)
		return (NULL);

	/* Compute total bytes needed for the array. */
	total_size = nmemb * size;
	/* Allocate the requested number of bytes. */
	ptr = malloc(total_size);
	/* Return NULL if allocation fails. */
	if (ptr == NULL)
		return (NULL);

	/* Initialize each allocated byte to zero. */
	for (i = 0; i < total_size; i++)
		((char *)ptr)[i] = 0;

	/* Return the initialized memory block. */
	return (ptr);
}
