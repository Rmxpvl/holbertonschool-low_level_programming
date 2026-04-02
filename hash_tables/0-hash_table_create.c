#include <stdlib.h>
#include "hash_tables.h"

/**
 * hash_table_create - cree une table de hachage vide
 * @size: nombre de cases du tableau
 *
 * Return: adresse de la table creee, ou NULL en cas d'echec
 */
hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *ht;
	unsigned long int i;

	if (size == 0)
		return (NULL);

	/* Allocation de la structure principale de la table */
	ht = malloc(sizeof(hash_table_t));
	if (ht == NULL)
		return (NULL);

	/* Sauvegarde de la taille demandee */
	ht->size = size;

	/* Allocation du tableau de buckets */
	ht->array = malloc(sizeof(hash_node_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	/* Chaque bucket commence vide: pointeur a NULL */
	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	return (ht);
}
