#include <stdlib.h>
#include "hash_tables.h"

hash_table_t *hash_table_create(unsigned long int size)
{
    hash_table_t *ht;
    unsigned long int i;

    if (size == 0)
        return (NULL);

    /* 1. Allocation de la structure */
    ht = malloc(sizeof(hash_table_t));
    if (ht == NULL)
        return (NULL);

    /* 2. Initialisation de la taille */
    ht->size = size;

    /* 3. Allocation du tableau */
    ht->array = malloc(sizeof(hash_node_t *) * size);
    if (ht->array == NULL)
    {
        free(ht);
        return (NULL);
    }

    /* 4. Initialiser chaque case a NULL */
    for (i = 0; i < size; i++)
        ht->array[i] = NULL;

    return (ht);
}
