#include "function_pointers.h"

/**
 * int_index - cherche un entier
 *             avec une fonction de comparaison
 * @array: tableau d'entiers a parcourir
 * @size: nombre d'elements du tableau
 * @cmp: fonction qui compare une valeur et retourne 0 ou non
 *
 * Return: index du premier element valide, ou -1 en cas d'echec
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	/* On valide les entrees avant de parcourir le tableau. */
	if (array == NULL || cmp == NULL || size <= 0)
		return (-1);

	/* On teste chaque element dans l'ordre. */
	for (i = 0; i < size; i++)
	{
		/* Si cmp ne retourne pas 0, on retourne cet index. */
		if (cmp(array[i]) != 0)
			return (i);
	}

	/* Aucun element ne correspond a la condition. */
	return (-1);
}
