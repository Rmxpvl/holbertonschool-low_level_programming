#include "lists.h"
#include <stdlib.h>

/**
 * insert_dnodeint_at_index - inserts a new node at a given position
 * @h: double pointer to the head of the list
 * @idx: index where the new node should be added
 * @n: data to insert
 *
 * Return: address of the new node, or NULL if it failed
 */
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
	dlistint_t *new_node;
	dlistint_t *current;
	unsigned int count;

	if (h == NULL)
		return (NULL);

	/* Insert at beginning (index 0) */
	if (idx == 0)
		return (add_dnodeint(h, n));

	/* Traverse to find the node at idx - 1 */
	current = *h;
	count = 0;

	while (current != NULL)
	{
		if (count == idx - 1)
		{
			/* Insert after current node */
			new_node = malloc(sizeof(dlistint_t));
			if (new_node == NULL)
				return (NULL);

			new_node->n = n;
			new_node->next = current->next;
			new_node->prev = current;

			if (current->next != NULL)
				current->next->prev = new_node;

			current->next = new_node;

			return (new_node);
		}
		current = current->next;
		count++;
	}

	/* Index out of bounds or list is empty and idx > 0 */
	return (NULL);
}
