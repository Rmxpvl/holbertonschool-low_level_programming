#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * update_existing_key - met a jour la valeur si la cle existe deja
 * @head: debut de la liste du bucket
 * @key: cle a rechercher
 * @value: nouvelle valeur a dupliquer
 *
 * Return: 1 si mise a jour, 0 sinon
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
			/* On duplique avant de liberer l'ancienne valeur */
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
 * create_node - cree un nouveau noeud avec copies de key et value
 * @key: cle a dupliquer
 * @value: valeur a dupliquer
 *
 * Return: adresse du noeud, ou 0 en cas d'echec
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
 * hash_table_set - ajoute ou met a jour un element dans la table
 * @ht: table de hachage
 * @key: cle (ne doit pas etre vide)
 * @value: valeur associee a la cle
 *
 * Return: 1 en cas de succes, 0 sinon
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	hash_node_t *node;
	unsigned long int index;

	if (ht == 0 || key == 0 || *key == '\0' || value == 0)
		return (0);

	/* Calcul du bucket cible a partir de la cle */
	index = key_index((const unsigned char *)key, ht->size);

	/* Si la cle existe deja, on remplace seulement sa valeur */
	if (update_existing_key(ht->array[index], key, value) == 1)
		return (1);

	/* Sinon, on cree un nouveau noeud */
	node = create_node(key, value);
	if (node == 0)
		return (0);

	/* Collision: insertion en tete de la liste du bucket */
	node->next = ht->array[index];
	ht->array[index] = node;

	return (1);
}
