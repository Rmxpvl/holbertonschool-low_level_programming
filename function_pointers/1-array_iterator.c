#include "function_pointers.h"

/**
 * array_iterator - execute une fonction sur chaque element d'un tableau
 * @array: tableau d'entiers a parcourir
 * @size: nombre d'elements dans le tableau
 * @action: fonction a appliquer sur chaque valeur
 *
 * Return: rien
 */
void array_iterator(int *array, size_t size, void (*action)(int))
{
	/* Variable d'iteration pour parcourir le tableau. */
	size_t i;

	/* On sort si le tableau ou la fonction est invalide. */
	if (array == NULL || action == NULL)
		return;

	/* On parcourt chaque case du tableau. */
	for (i = 0; i < size; i++)
		/* On applique la fonction a la valeur courante. */
		action(array[i]);
}
