#ifndef HASH_TABLES_H
#define HASH_TABLES_H

/**
 * struct hash_node_s - Noeud d'une table de hachage
 *
 * @key: Cle (chaine) associee a la valeur
 * @value: Valeur stockee pour la cle
 * @next: Noeud suivant dans la liste chainee (gestion des collisions)
 */
typedef struct hash_node_s
{
	char *key;
	char *value;
	struct hash_node_s *next;
} hash_node_t;

/**
 * struct hash_table_s - Structure principale de table de hachage
 *
 * @size: Nombre de cases dans le tableau
 * @array: Tableau de pointeurs vers des listes de noeuds
 * Chaque case pointe vers une liste chainee pour resoudre les collisions.
 */
typedef struct hash_table_s
{
	unsigned long int size;
	hash_node_t **array;
} hash_table_t;

hash_table_t *hash_table_create(unsigned long int size);
unsigned long int hash_djb2(const unsigned char *str);
unsigned long int key_index(const unsigned char *key, unsigned long int size);
int hash_table_set(hash_table_t *ht, const char *key, const char *value);
char *hash_table_get(const hash_table_t *ht, const char *key);
void hash_table_print(const hash_table_t *ht);
void hash_table_delete(hash_table_t *ht);
#endif
