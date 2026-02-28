#include "main.h"

/**
 * print_square - prints a square of '#' characters
 * @size: size of the square
 */
void print_square(int size)
{
	int i, j;

	if (size <= 0)
	{
		_putchar('\n'); /* si size <= 0, juste un retour à la ligne */
		return;
	}

	i = 0;
	while (i < size) /* boucle pour chaque ligne */
	{
		j = 0;
		while (j < size) /* boucle pour chaque caractère '#' sur la ligne */
		{
			_putchar('#');
			j++;
		}
		_putchar('\n'); /* fin de la ligne */
		i++;
	}
}
