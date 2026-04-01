#include "lists.h"
#include <stdlib.h>

/**
 * free_dlistint - frees a dlistint_t list
 * @head: pointer to the head of the list
 *
 * Return: void
 */
void free_dlistint(dlistint_t *head)
{
dlistint_t *current;

while (head != NULL)
{
/* Save the next node before freeing the current one */
current = head->next;
free(head);
head = current;
}
}
