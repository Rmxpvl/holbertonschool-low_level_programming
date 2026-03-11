#include "main.h"
#include <stdlib.h>

/**
 * free_grid - frees a 2 dimensional grid previously created by alloc_grid.
 * Objective: Mirror the allocation done in alloc_grid. Since each row
 * was allocated independently, each one must be freed individually
 * before freeing the outer array of row pointers. This prevents memory
 * leaks and is the correct complement to alloc_grid.
 * @grid: the 2D array to free.
 * @height: the height of the grid.
 */
void free_grid(int **grid, int height)
{
int i; /* row index */

for (i = 0; i < height; i++) /* free each row of the grid */
free(grid[i]); /* free memory allocated for row i */
free(grid); /* free the array of row pointers */
}
