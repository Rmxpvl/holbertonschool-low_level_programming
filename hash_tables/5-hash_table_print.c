#include <stdio.h>
#include "hash_tables.h"

/**
 * hash_table_print - affiche la table de hachage
 * @ht: table a afficher
 */
void hash_table_print(const hash_table_t *ht)
{
	hash_node_t *node;
	unsigned long int i;
	int first;

	if (ht == 0)
		return;

	printf("{");
	first = 1;

	/* Ordre impose: d'abord les buckets du tableau, puis les listes */
	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		while (node)
		{
			if (!first)
				printf(", ");
			printf("'%s': '%s'", node->key, node->value);
			first = 0;
			node = node->next;
		}
	}
	printf("}\n");
}
