#include "lists.h"
#include <stdlib.h>

/**
 * add_dnodeint_end - adds a new node at the end of a dlistint_t list
 * @head: double pointer to the head of the list
 * @n: integer value for the new node
 *
 * Return: address of the new element, or NULL if it failed
 */
dlistint_t *add_dnodeint_end(dlistint_t **head, const int n)
{
dlistint_t *new_node;
dlistint_t *current;

if (head == NULL)
return (NULL);

/* Allocate memory for the new node */
new_node = malloc(sizeof(dlistint_t));
if (new_node == NULL)
return (NULL);

/* Initialize the new node */
new_node->n = n;
new_node->next = NULL;
new_node->prev = NULL;

/* If the list is empty, make this the head */
if (*head == NULL)
{
*head = new_node;
return (new_node);
}

/* Traverse to the end of the list */
current = *head;
while (current->next != NULL)
current = current->next;

/* Add the new node at the end */
current->next = new_node;
new_node->prev = current;

return (new_node);
}
