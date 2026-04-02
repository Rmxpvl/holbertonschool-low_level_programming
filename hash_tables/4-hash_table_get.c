#include "hash_tables.h"
#include <string.h>

/**
 * hash_table_get - recupere la valeur associee a une cle
 * @ht: table de hachage
 * @key: cle a rechercher
 *
 * Return: valeur associee a key, ou NULL si absente
 */
char *hash_table_get(const hash_table_t *ht, const char *key)
{
	unsigned long int index;
	hash_node_t *node;

	/* Entrees invalides: table absente ou cle vide */
	if (!ht || !key || key[0] == '\0')
		return (NULL);

	/* On calcule le bucket ou la cle devrait se trouver */
	index = key_index((const unsigned char *)key, ht->size);
	node = ht->array[index];

	/* Parcours lineaire de la liste chainee du bucket */
	while (node)
	{
		if (strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}

	return (NULL);
}
