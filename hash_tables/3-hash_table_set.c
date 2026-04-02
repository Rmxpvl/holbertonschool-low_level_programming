#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * hash_table_set - adds an element to the hash table
 * @ht: hash table
 * @key: key (must not be empty)
 * @value: value associated with the key
 *
 * Return: 1 on success, 0 on failure
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
hash_node_t *node;
hash_node_t *tmp;
char *new_value;
unsigned long int index;

if (ht == 0 || key == 0 || *key == '\0' || value == 0)
return (0);

index = key_index((const unsigned char *)key, ht->size);
tmp = ht->array[index];
while (tmp)
{
if (strcmp(tmp->key, key) == 0)
{
new_value = strdup(value);
if (new_value == 0)
return (0);
free(tmp->value);
tmp->value = new_value;
return (1);
}
tmp = tmp->next;
}

node = malloc(sizeof(hash_node_t));
if (node == 0)
return (0);

node->key = strdup(key);
if (node->key == 0)
{
free(node);
return (0);
}

node->value = strdup(value);
if (node->value == 0)
{
free(node->key);
free(node);
return (0);
}

node->next = ht->array[index];
ht->array[index] = node;

return (1);
}
