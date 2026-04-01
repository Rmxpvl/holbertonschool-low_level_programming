#include "lists.h"
#include <stdlib.h>

/**
 * delete_dnodeint_at_index - deletes the node at index of a dlistint_t list
 * @head: double pointer to the head of the list
 * @index: index of the node to delete
 *
 * Return: 1 if succeeded, -1 if it failed
 */
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
	dlistint_t *current;
	dlistint_t *temp;
	unsigned int count;

	if (head == NULL || *head == NULL)
		return (-1);

	current = *head;
	count = 0;

	/* If deleting the first node (index 0) */
	if (index == 0)
	{
		*head = current->next;
		if (*head != NULL)
			(*head)->prev = NULL;
		free(current);
		return (1);
	}

	/* Traverse to the node before the one to delete */
	while (current != NULL)
	{
		if (count == index - 1)
		{
			/* Check if the next node exists */
			if (current->next == NULL)
				return (-1);

			/* Delete the next node */
			temp = current->next;
			current->next = temp->next;
			if (temp->next != NULL)
				temp->next->prev = current;
			free(temp);
			return (1);
		}
		current = current->next;
		count++;
	}

	/* Index out of bounds */
	return (-1);
}
