# Hash Tables - Cours global et exercices

## 1. C'est quoi une hash table ?

Une hash table (table de hachage) est une structure de donnees qui permet de
stocker des paires `cle -> valeur` avec un acces en moyenne tres rapide.

Objectif:
- inserer une valeur a partir d'une cle
- retrouver une valeur a partir de la meme cle
- supprimer proprement toute la structure

En moyenne, insertion/recherche sont proches de `O(1)`.

## 2. Idee de base

Une table de hachage utilise:
- un tableau de taille fixe `size`
- une fonction de hash qui transforme une chaine en grand entier
- un calcul d'indice: `index = hash(key) % size`

Cet indice indique dans quelle case (bucket) du tableau on doit aller.

## 3. Collisions et chaining

Deux cles differentes peuvent produire le meme indice: c'est une collision.

Ici, on gere les collisions par chaining (liste chainee):
- chaque case du tableau pointe vers une liste de noeuds
- si une collision arrive, on ajoute le nouveau noeud au debut de la liste

## 4. Structures utilisees

Dans [hash_tables.h](hash_tables.h):
- `hash_node_t`: un noeud contenant `key`, `value`, `next`
- `hash_table_t`: la table contenant `size` et `array`

## 5. Fonction de hash choisie

Le projet utilise `djb2`:
- valeur initiale `5381`
- pour chaque caractere `c`: `hash = hash * 33 + c`

Forme C equivalente:

```c
hash = ((hash << 5) + hash) + c;
```

## 6. Parcours detaille des exercices (avec code)

### Exercice 0 - `hash_table_create`
Fichier: [0-hash_table_create.c](0-hash_table_create.c)

Extrait cle:

```c
if (size == 0)
	return (NULL);

ht = malloc(sizeof(hash_table_t));
if (ht == NULL)
	return (NULL);

ht->array = malloc(sizeof(hash_node_t *) * size);
if (ht->array == NULL)
{
	free(ht);
	return (NULL);
}

for (i = 0; i < size; i++)
	ht->array[i] = NULL;
```

Explication etape par etape:
1. `size == 0` est refuse car une table sans bucket ne peut pas fonctionner.
2. `malloc(sizeof(hash_table_t))` reserve la structure principale.
3. Si cette allocation echoue, on retourne `NULL` immediatement.
4. On alloue ensuite le tableau de buckets `array`.
5. Si `array` echoue, on libere `ht` pour eviter une fuite memoire.
6. On initialise chaque case du tableau a `NULL` pour signaler des buckets vides.

### Exercice 1 - `hash_djb2`
Fichier: [1-djb2.c](1-djb2.c)

Extrait cle:

```c
hash = 5381;
while ((c = *str++))
	hash = ((hash << 5) + hash) + c;
```

Explication etape par etape:
1. `hash` demarre a `5381`, constante classique de l'algorithme djb2.
2. `*str++` lit un caractere puis avance le pointeur.
3. La boucle s'arrete sur `\0` (fin de chaine).
4. `((hash << 5) + hash)` equivaut a `hash * 33`.
5. On ajoute `c` pour integrer le caractere courant dans le hash final.

### Exercice 2 - `key_index`
Fichier: [2-key_index.c](2-key_index.c)

Extrait cle:

```c
if (key == 0 || *key == '\0' || size == 0)
	return (0);

return (hash_djb2(key) % size);
```

Explication etape par etape:
1. On filtre les entrees invalides (`key` nulle, vide, ou `size` nulle).
2. `hash_djb2(key)` produit un grand entier pseudo-aleatoire.
3. Le modulo `% size` ramene ce nombre dans l'intervalle valide des indices.
4. Le resultat indique le bucket cible dans `ht->array[index]`.

### Exercice 3 - `hash_table_set`
Fichier: [3-hash_table_set.c](3-hash_table_set.c)

Extrait cle (fonction principale):

```c
index = key_index((const unsigned char *)key, ht->size);
if (update_existing_key(ht->array[index], key, value) == 1)
	return (1);

node = create_node(key, value);
if (node == 0)
	return (0);

node->next = ht->array[index];
ht->array[index] = node;
```

Extrait cle (mise a jour):

```c
if (strcmp(tmp->key, key) == 0)
{
	new_value = strdup(value);
	if (new_value == 0)
		return (0);
	free(tmp->value);
	tmp->value = new_value;
	return (1);
}
```

Explication etape par etape:
1. On calcule le bucket cible avec `key_index`.
2. On parcourt la liste pour voir si la cle existe deja.
3. Si la cle existe, on duplique la nouvelle valeur puis on remplace l'ancienne.
4. Si la cle n'existe pas, on alloue un nouveau noeud.
5. `key` et `value` sont dupliquees (`strdup`) pour que la table possede sa memoire.
6. En collision, insertion en tete: rapide et conforme a la consigne.

### Exercice 4 - `hash_table_get`
Fichier: [4-hash_table_get.c](4-hash_table_get.c)

Extrait cle:

```c
index = key_index((const unsigned char *)key, ht->size);
node = ht->array[index];

while (node)
{
	if (strcmp(node->key, key) == 0)
		return (node->value);
	node = node->next;
}
```

Explication etape par etape:
1. On calcule l'indice theorique de la cle.
2. On va au debut de la liste chainee de ce bucket.
3. On compare les cles une par une avec `strcmp`.
4. A la premiere egalite, on retourne la valeur associee.
5. Si la fin de liste est atteinte sans match, on retourne `NULL`.

### Exercice 5 - `hash_table_print`
Fichier: [5-hash_table_print.c](5-hash_table_print.c)

Extrait cle:

```c
printf("{");
first = 1;
for (i = 0; i < ht->size; i++)
{
	node = ht->array[i];
	while (node)
	{
		if (!first)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		first = 0;
		node = node->next;
	}
}
printf("}\n");
```

Explication etape par etape:
1. On ouvre l'affichage avec `{`.
2. `first` sert a savoir s'il faut afficher une virgule avant un element.
3. On parcourt chaque bucket du tableau dans l'ordre croissant des indices.
4. Dans chaque bucket, on parcourt la liste chainee dans son ordre courant.
5. Format impose respecte: `'<key>': '<value>'`.
6. On ferme avec `}` et un retour a la ligne.

### Exercice 6 - `hash_table_delete`
Fichier: [6-hash_table_delete.c](6-hash_table_delete.c)

Extrait cle:

```c
for (i = 0; i < ht->size; i++)
{
	node = ht->array[i];
	while (node)
	{
		tmp = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = tmp;
	}
}

free(ht->array);
free(ht);
```

Explication etape par etape:
1. On parcourt tous les buckets de la table.
2. Dans chaque bucket, on parcourt tous les noeuds de la liste.
3. On sauvegarde `next` avant `free(node)` pour ne pas perdre la chaine.
4. On libere dans l'ordre: `key`, `value`, puis le noeud.
5. Une fois toutes les listes liberees, on libere le tableau, puis la table.

## 7. Complexite

- recherche moyenne: `O(1)`
- insertion moyenne: `O(1)`
- pire cas (beaucoup de collisions): `O(n)`

La qualite de la fonction de hash et une bonne taille de table reduisent les
collisions.

## 8. Bonnes pratiques memoire

- toujours verifier les retours de `malloc`/`strdup`
- en cas d'echec, liberer ce qui a deja ete alloue
- dupliquer `key` et `value` pour posseder ses propres donnees
- ne jamais oublier la fonction de destruction complete

## 9. Comment tester rapidement

Style:

```bash
betty-style *.c hash_tables.h
```

Compilation stricte:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -c
```

## 10. Resume

Ce dossier construit pas a pas une vraie table de hachage en C:
- creation
- hachage
- calcul d'indice
- insertion/mise a jour
- recherche
- affichage
- destruction

Le fil conducteur principal est toujours le meme:
`key -> hash -> index -> bucket -> liste`.
