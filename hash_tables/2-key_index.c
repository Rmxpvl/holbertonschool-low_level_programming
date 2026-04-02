#include "hash_tables.h"

/**
 * key_index - calcule l'indice d'une cle dans le tableau de hash
 * @key: cle a convertir en indice
 * @size: taille du tableau de la table de hash
 *
 * Return: indice ou stocker/rechercher la paire (key, value)
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	/*
	 * Verification defensive:
	 * - pointeur de cle invalide
	 * - chaine vide
	 * - taille nulle (pas de bucket disponible)
	 */
	if (key == 0 || *key == '\0' || size == 0)
		return (0);

	/*
	 * Etape 1: hash_djb2 convertit la cle en entier.
	 * Etape 2: modulo size pour obtenir un indice valide dans le tableau.
	 */
	return (hash_djb2(key) % size);
}
