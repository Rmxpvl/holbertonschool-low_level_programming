#include <stdlib.h>
#include "hash_tables.h"

/**
 * hash_table_delete - libere completement une table de hachage
 * @ht: table a supprimer
 */
void hash_table_delete(hash_table_t *ht)
{
	hash_node_t *node;
	hash_node_t *tmp;
	unsigned long int i;

	if (ht == 0)
		return;

	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		while (node)
		{
			/* On sauvegarde le suivant avant de liberer le noeud courant */
			tmp = node->next;
			free(node->key);
			free(node->value);
			free(node);
			node = tmp;
		}
	}

	free(ht->array);
	free(ht);
}
