#include "main.h"
#include <stdlib.h>

/**
 * alloc_grid - returns a pointer to a 2 dimensional array of integers.
 * Objective: Allocate a true 2D grid dynamically using an array of
 * pointers to rows. First allocate the array of row pointers, then
 * allocate each individual row. Every integer cell is initialised to 0.
 * If any allocation fails, all previously allocated memory is freed
 * before returning NULL to avoid memory leaks.
 * @width: the width of the grid.
 * @height: the height of the grid.
 * Return: a pointer to the 2D array, or NULL on failure or if
 * width or height is 0 or negative.
 */
int **alloc_grid(int width, int height)
{
int **grid; /* pointer to the array of row pointers */
int i; /* row index */
int j; /* column index */

if (width <= 0 || height <= 0) /* invalid dimensions */
return (NULL);

grid = malloc(sizeof(int *) * height); /* allocate array of row pointers */
if (grid == NULL) /* check if malloc failed */
return (NULL);

for (i = 0; i < height; i++) /* allocate each row */
{
grid[i] = malloc(sizeof(int) * width); /* allocate memory for one row */
if (grid[i] == NULL) /* if row allocation fails, free previous rows */
{
while (i--) /* free already allocated rows */
free(grid[i]); /* free row i */
free(grid); /* free the array of pointers */
return (NULL);
}
for (j = 0; j < width; j++) /* initialize all elements to 0 */
grid[i][j] = 0; /* set element to 0 */
}
return (grid); /* return pointer to the 2D grid */
}
