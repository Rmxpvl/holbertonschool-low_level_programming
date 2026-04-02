#include "hash_tables.h"

/**
 * hash_djb2 - calcule un hash avec l'algorithme djb2
 * @str: chaine a hacher
 *
 * Return: valeur numerique de hash
 */
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	/* Valeur initiale classique de djb2 */
	hash = 5381;

	/* Pour chaque caractere: hash = hash * 33 + c */
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;

	return (hash);
}
