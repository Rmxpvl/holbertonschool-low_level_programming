#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * update_existing_key - update value if key already exists
 * @head: first node of bucket list
 * @key: key to match
 * @value: new value to duplicate
 *
 * Return: 1 if updated, 0 if key not found or allocation failure
 */
static int update_existing_key(hash_node_t *head, const char *key,
const char *value)
{
hash_node_t *tmp;
char *new_value;

tmp = head;
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

return (0);
}

/**
 * create_node - create a new hash node with duplicated key and value
 * @key: key to duplicate
 * @value: value to duplicate
 *
 * Return: pointer to new node, or 0 on failure
 */
static hash_node_t *create_node(const char *key, const char *value)
{
hash_node_t *node;

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

node->next = 0;
return (node);
}

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
unsigned long int index;

if (ht == 0 || key == 0 || *key == '\0' || value == 0)
return (0);

index = key_index((const unsigned char *)key, ht->size);
if (update_existing_key(ht->array[index], key, value) == 1)
return (1);

node = create_node(key, value);
if (node == 0)
return (0);

node->next = ht->array[index];
ht->array[index] = node;

return (1);
}
