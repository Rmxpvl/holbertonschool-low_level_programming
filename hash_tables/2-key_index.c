#include "hash_tables.h"

/**
 * key_index - calcule l'indice d'une cle dans le tableau de hash
 * @key: cle a convertir en indice
 * @size: taille du tableau de la table de hash
 *
 * Return: indice ou stocker la paire (key, value)
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
/*
* Verification defensive:
* - key == 0: pointeur invalide
* - *key == '\0': chaine vide, donc aucune cle exploitable
* - size == 0: modulo impossible et tableau inexistant
*/
if (key == 0 || *key == '\0' || size == 0)
return (0);

/*
* Etape 1: hash_djb2 transforme la chaine en grand entier.
* Etape 2: % size ramene cette valeur dans l'intervalle [0, size - 1].
* Cet indice correspond a la case du tableau ou placer/rechercher la cle.
*/
return (hash_djb2(key) % size);
}
