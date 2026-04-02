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

## 6. Parcours des exercices du dossier

### Exercice 0 - `hash_table_create`
Fichier: [0-hash_table_create.c](0-hash_table_create.c)

Ce qui se passe:
1. verifier `size` (interdire 0)
2. allouer la structure `hash_table_t`
3. allouer le tableau de buckets (`hash_node_t *`)
4. initialiser chaque bucket a `NULL`

But: partir d'une table vide et sure.

### Exercice 1 - `hash_djb2`
Fichier: [1-djb2.c](1-djb2.c)

Ce qui se passe:
1. initialiser le hash a `5381`
2. parcourir la chaine caractere par caractere
3. mettre a jour le hash avec la formule djb2

But: convertir une cle texte en nombre deterministe.

### Exercice 2 - `key_index`
Fichier: [2-key_index.c](2-key_index.c)

Ce qui se passe:
1. verifier les cas invalides (`key` nulle/vide, `size == 0`)
2. calculer `hash_djb2(key)`
3. appliquer `% size` pour obtenir un indice valide du tableau

But: savoir exactement dans quel bucket chercher/ajouter.

### Exercice 3 - `hash_table_set`
Fichier: [3-hash_table_set.c](3-hash_table_set.c)

Ce qui se passe:
1. verifier les arguments (`ht`, `key`, `value`)
2. calculer l'indice avec `key_index`
3. parcourir la liste du bucket:
	- si la cle existe: dupliquer la nouvelle valeur et remplacer l'ancienne
4. sinon creer un nouveau noeud (duplication de `key` et `value`)
5. inserer le noeud en tete de liste (collision handling)

But: ajouter ou mettre a jour une paire cle/valeur en securite memoire.

### Exercice 4 - `hash_table_get`
Fichier: [4-hash_table_get.c](4-hash_table_get.c)

Ce qui se passe:
1. verifier les entrees
2. calculer le bucket cible avec `key_index`
3. parcourir la liste chainee et comparer les cles (`strcmp`)
4. retourner la valeur si trouvee, sinon `NULL`

But: recuperer rapidement une valeur depuis une cle.

### Exercice 5 - `hash_table_print`
Fichier: [5-hash_table_print.c](5-hash_table_print.c)

Ce qui se passe:
1. ne rien afficher si `ht == NULL`
2. afficher `{` puis parcourir les buckets dans l'ordre du tableau
3. dans chaque bucket, parcourir la liste et afficher `'<key>': '<value>'`
4. gerer proprement les virgules entre elements
5. fermer avec `}`

But: visualiser l'etat logique de la table.

### Exercice 6 - `hash_table_delete`
Fichier: [6-hash_table_delete.c](6-hash_table_delete.c)

Ce qui se passe:
1. verifier `ht`
2. pour chaque bucket, parcourir la liste
3. liberer dans le bon ordre: `key`, `value`, puis noeud
4. liberer le tableau `array`
5. liberer la structure `ht`

But: eviter toute fuite memoire.

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
