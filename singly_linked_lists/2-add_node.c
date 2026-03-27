#include <stdlib.h>
#include <string.h>
#include "lists.h"

/**
 * add_node - adds a new node at the beginning of a list_t list
 * @head: pointer to the pointer of the first node
 * @str: string to duplicate and store in the new node
 *
 * Return: address of the new element, or NULL if it failed
 */
list_t *add_node(list_t **head, const char *str)
{
list_t *new_node;
char *dup;
size_t len;

if (head == NULL || str == NULL)
return (NULL);

new_node = malloc(sizeof(list_t));
if (new_node == NULL)
return (NULL);

dup = strdup(str);
if (dup == NULL)
{
free(new_node);
return (NULL);
}

len = 0;
while (str[len] != '\0')
len++;
new_node->str = dup;
new_node->len = (unsigned int)len;
new_node->next = *head;
*head = new_node;

return (new_node);
}
