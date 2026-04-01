# Listes Doublement Chaînées (Doubly Linked Lists)

## 📚 Objectifs d'Apprentissage

- Comprendre la structure d'une liste doublement chaînée
- Implémenter les opérations fondamentales (création, insertion, suppression, recherche)
- Gérer les pointeurs `prev` et `next` correctement
- Manipuler une liste entière via son pointeur de tête
- Gérer la mémoire dynamique avec `malloc` et `free`

---

## 🎯 Concepts Clés

### Qu'est-ce qu'une Liste Doublement Chaînée ?

Une **liste doublement chaînée (doubly linked list)** est une structure de données où chaque nœud contient :
- Une **valeur de donnée** (`n`)
- Un **pointeur vers le nœud suivant** (`next`)
- Un **pointeur vers le nœud précédent** (`prev`)

**Visualisation :**
```
NULL ← [prev|n|next] ↔ [prev|n|next] ↔ [prev|n|next] → NULL
```

### Structure de Données

```c
typedef struct dlistint_s
{
    int n;                      /* La donnée */
    struct dlistint_s *prev;    /* Pointeur vers le nœud précédent */
    struct dlistint_s *next;    /* Pointeur vers le nœud suivant */
} dlistint_t;
```

### Avantages vs Liste Simple

| Opération | Liste Simple | Liste Doublement Chaînée |
|-----------|--------------|-------------------------|
| Traversal avant | O(n) | O(n) |
| Traversal arrière | Impossible | O(n) |
| Obtenir le prédécesseur | Impossible | O(1) |
| Insertion/suppression (avec pointeur) | O(1) | O(1) |

---

## 📋 Fichiers et Exercices

### 0. `0-print_dlistint.c` — Afficher une Liste

**Objectif** : Afficher tous les éléments d'une liste doublement chaînée.

**Concept** : Traverser la liste et imprimer chaque valeur.

**Exemple de code** :
```c
size_t print_dlistint(const dlistint_t *h)
{
    size_t count = 0;

    while (h != NULL)
    {
        printf("%d\n", h->n);
        h = h->next;
        count++;
    }

    return (count);
}
```

**Utilisation** :
```c
// Créer une liste : 0 → 1 → 2 → 3 → 4
print_dlistint(head);
// Affiche :
// 0
// 1
// 2
// 3
// 4
```

**Points Clés** :
- Traverser via le pointeur `next`
- Compter les nœuds
- Continuer jusqu'à `NULL`

---

### 1. `1-dlistint_len.c` — Obtenir la Longueur

**Objectif** : Retourner le nombre de nœuds dans une liste.

**Concept** : Compter chaque nœud en parcourant la liste.

**Exemple de code** :
```c
size_t dlistint_len(const dlistint_t *h)
{
    size_t count = 0;

    while (h != NULL)
    {
        count++;
        h = h->next;
    }

    return (count);
}
```

**Utilisation** :
```c
head = NULL;
add_dnodeint_end(&head, 0);  // 1 nœud
add_dnodeint_end(&head, 1);  // 2 nœuds
add_dnodeint_end(&head, 2);  // 3 nœuds

size_t length = dlistint_len(head);  // 3
```

---

### 2. `2-add_dnodeint.c` — Ajouter au Début

**Objectif** : Ajouter un nouveau nœud au **début** de la liste.

**Concept** :
- Créer un nouveau nœud
- Le relier au nœud actuel (qui devient le deuxième)
- Mettre à jour le pointeur de tête

**Exemple de code** :
```c
dlistint_t *add_dnodeint(dlistint_t **head, const int n)
{
    dlistint_t *new_node = malloc(sizeof(dlistint_t));
    if (new_node == NULL)
        return (NULL);

    new_node->n = n;
    new_node->next = *head;
    new_node->prev = NULL;

    if (*head != NULL)
        (*head)->prev = new_node;

    *head = new_node;

    return (new_node);
}
```

**Utilisation** :
```c
head = NULL;
add_dnodeint(&head, 5);  // List: 5
add_dnodeint(&head, 3);  // List: 3 ↔ 5
add_dnodeint(&head, 1);  // List: 1 ↔ 3 ↔ 5
```

**Points Clés** :
- Le nouveau nœud devient la **tête**
- L'ancien head devient son `next`
- Le nouveau nœud's `prev` est toujours NULL (c'est le début)

---

### 3. `3-add_dnodeint_end.c` — Ajouter à la Fin

**Objectif** : Ajouter un nouveau nœud à la **fin** de la liste.

**Concept** :
- Traverser jusqu'au dernier nœud (celui où `next == NULL`)
- Ajouter le nouveau nœud après lui

**Exemple de code** :
```c
dlistint_t *add_dnodeint_end(dlistint_t **head, const int n)
{
    dlistint_t *new_node = malloc(sizeof(dlistint_t));
    dlistint_t *current;

    if (new_node == NULL)
        return (NULL);

    new_node->n = n;
    new_node->next = NULL;
    new_node->prev = NULL;

    /* Si la liste est vide, le nouveau nœud est la tête */
    if (*head == NULL)
    {
        *head = new_node;
        return (new_node);
    }

    /* Traverser jusqu'à la fin */
    current = *head;
    while (current->next != NULL)
        current = current->next;

    /* Ajouter à la fin */
    current->next = new_node;
    new_node->prev = current;

    return (new_node);
}
```

**Utilisation** :
```c
head = NULL;
add_dnodeint_end(&head, 0);  // List: 0
add_dnodeint_end(&head, 1);  // List: 0 ↔ 1
add_dnodeint_end(&head, 2);  // List: 0 ↔ 1 ↔ 2
add_dnodeint_end(&head, 3);  // List: 0 ↔ 1 ↔ 2 ↔ 3
```

**Points Clés** :
- Gérer le cas d'une liste vide
- Bidirectionnel : `prev` et `next` doivent être corrects
- Le nouveau nœud's `next` est toujours NULL (c'est la fin)

---

### 4. `4-free_dlistint.c` — Libérer la Liste

**Objectif** : Libérer toute la mémoire allouée pour la liste.

**Concept** :
- Sauvegarder le pointeur `next` **avant** de libérer
- Libérer chaque nœud progressivement
- Éviter les fuites mémoire

**Exemple de code** :
```c
void free_dlistint(dlistint_t *head)
{
    dlistint_t *current;

    while (head != NULL)
    {
        current = head->next;  /* Sauvegarder AVANT de libérer */
        free(head);
        head = current;
    }
}
```

**Utilisation** :
```c
head = NULL;
add_dnodeint_end(&head, 0);
add_dnodeint_end(&head, 1);
add_dnodeint_end(&head, 2);
// ... utiliser la liste ...
free_dlistint(head);  /* Libère tous les nœuds */
head = NULL;
```

**Points Clés** :
- **Crucial** : sauvegarder `head->next` avant `free(head)`
- Sinon, on accède à la mémoire libérée → undefined behavior
- Valgrind affichera "0 errors" après correct free

---

### 5. `5-get_dnodeint.c` — Obtenir le Nœud à un Index

**Objectif** : Retourner le nœud à une position donnée.

**Concept** :
- Parcourir avec un compteur
- Retourner le nœud quand on atteint l'index demandé

**Exemple de code** :
```c
dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index)
{
    unsigned int count = 0;

    while (head != NULL)
    {
        if (count == index)
            return (head);
        head = head->next;
        count++;
    }

    return (NULL);  /* Index n'existe pas */
}
```

**Utilisation** :
```c
head_after_add: 0 ↔ 1 ↔ 2 ↔ 3 ↔ 4 ↔ 98 ↔ 402 ↔ 1024

dlistint_t *node = get_dnodeint_at_index(head, 5);
printf("%d\n", node->n);  // 98

node = get_dnodeint_at_index(head, 100);  // NULL (index n'existe pas)
```

**Points Clés** :
- Index commence à 0
- Retourne NULL si l'index dépasse la longueur de la liste

---

### 6. `6-sum_dlistint.c` — Additionner les Valeurs

**Objectif** : Retourner la somme de toutes les valeurs de la liste.

**Concept** : Parcourir et accumuler chaque valeur.

**Exemple de code** :
```c
int sum_dlistint(dlistint_t *head)
{
    int sum = 0;

    while (head != NULL)
    {
        sum += head->n;
        head = head->next;
    }

    return (sum);
}
```

**Utilisation** :
```c
head: 0 ↔ 1 ↔ 2 ↔ 3 ↔ 4 ↔ 98 ↔ 402 ↔ 1024

int total = sum_dlistint(head);
printf("sum = %d\n", total);  // 1534
// (0 + 1 + 2 + 3 + 4 + 98 + 402 + 1024 = 1534)
```

**Points Clés** :
- Retourne 0 automatiquement pour une liste vide (boucle ne s'exécute pas)

---

### 7. `7-insert_dnodeint.c` — Insérer à un Index

**Objectif** : Insérer un nouveau nœud à une position spécifique.

**Concept** :
- Index 0 → utiliser `add_dnodeint` (insérer au début)
- Autres indices → traverser, puis insérer après le nœud à `index-1`

**Exemple de code** :
```c
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
    dlistint_t *new_node;
    dlistint_t *current;
    unsigned int count;

    if (h == NULL)
        return (NULL);

    /* Cas spécial : insérer au début */
    if (idx == 0)
        return (add_dnodeint(h, n));

    current = *h;
    count = 0;

    /* Traverser jusqu'au nœud à (idx - 1) */
    while (current != NULL)
    {
        if (count == idx - 1)
        {
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

    return (NULL);  /* Index hors limites */
}
```

**Utilisation** :
```c
head: 0 ↔ 1 ↔ 2 ↔ 3 ↔ 4 ↔ 98 ↔ 402 ↔ 1024

insert_dnodeint_at_index(&head, 5, 4096);

head: 0 ↔ 1 ↔ 2 ↔ 3 ↔ 4 ↔ 4096 ↔ 98 ↔ 402 ↔ 1024
```

**Points Clés** :
- Mettre à jour `prev` et `next` correctement (c'est une liste **double**)
- Retourner NULL si l'index dépasse la liste

---

### 8. `8-delete_dnodeint.c` — Supprimer à un Index

**Objectif** : Supprimer le nœud à une position donnée et libérer sa mémoire.

**Concept** :
- Index 0 → supprimer la tête
- Autres indices → traverser, puis supprimer
- Réajuster les pointeurs `prev` et `next`

**Exemple de code** :
```c
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
    dlistint_t *current;
    dlistint_t *temp;
    unsigned int count;

    if (head == NULL || *head == NULL)
        return (-1);

    current = *head;
    count = 0;

    /* Supprimer le premier nœud */
    if (index == 0)
    {
        *head = current->next;
        if (*head != NULL)
            (*head)->prev = NULL;
        free(current);
        return (1);
    }

    /* Traverser au nœud à supprimer */
    while (current != NULL)
    {
        if (count == index - 1)
        {
            if (current->next == NULL)
                return (-1);  /* Nœud n'existe pas */

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

    return (-1);  /* Index hors limites */
}
```

**Utilisation** :
```c
head: 0 ↔ 1 ↔ 2 ↔ 3 ↔ 4 ↔ 98 ↔ 402 ↔ 1024

delete_dnodeint_at_index(&head, 5);  /* Supprimer index 5 (98) */

head: 0 ↔ 1 ↔ 2 ↔ 3 ↔ 4 ↔ 402 ↔ 1024

delete_dnodeint_at_index(&head, 0);  /* Supprimer le premier (0) */

head: 1 ↔ 2 ↔ 3 ↔ 4 ↔ 402 ↔ 1024
```

**Points Clés** :
- **Retourne 1** si succès, **-1** si échec
- Libérer le nœud supprimé avec `free()`
- Réajuster les pointeurs `prev` et `next` du nœud suivant/précédent

---

## 🔑 Points Clés à Retenir

| Concept | Explication |
|---------|------------|
| Bidirectionnel | Chaque nœud a `prev` et `next` |
| `prev` de tête | Toujours NULL |
| `next` de queue | Toujours NULL |
| Insertion/Suppression | O(1) avec pointeur au nœud |
| Traversal arrière | Possible via `prev` |
| Allocation | `malloc(sizeof(dlistint_t))` |
| Libération | Sauvegarder `next` avant `free()` |

---

## ⚠️ Erreurs Courantes

1. **Oublier de mettre à jour `prev`**
   ```c
   // FAUX : ne mets pas à jour le prev du nœud suivant
   current->next = new_node;
   // Oublie: new_node->prev = current;

   // BON :
   current->next = new_node;
   new_node->prev = current;
   ```

2. **Accéder à `head->next` après `free(head)`**
   ```c
   // FAUX : head est libéré, on ne peut plus l'utiliser
   free(head);
   head = head->next;  // Undefined behavior!

   // BON :
   dlistint_t *next = head->next;
   free(head);
   head = next;
   ```

3. **Oublier le cas d'une liste vide lors de l'ajout**
   ```c
   // FAUX : si *head est NULL, impossible d'ajouter à la fin
   current = *head;
   while (current->next != NULL)  // Segfault si head == NULL!

   // BON :
   if (*head == NULL)
   {
       *head = new_node;
       return (new_node);
   }
   ```

4. **Ne pas vérifier les limites de l'index**
   ```c
   // FAUX : pas de vérification
   dlistint_t *node = get_dnodeint_at_index(head, 1000);  // NULL
   printf("%d\n", node->n);  // Segfault!

   // BON :
   dlistint_t *node = get_dnodeint_at_index(head, 5);
   if (node != NULL)
       printf("%d\n", node->n);
   ```

---

## 📝 Exemple Complet d'Utilisation

```c
#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

int main(void)
{
    dlistint_t *head = NULL;

    /* Créer une liste : 0 ↔ 1 ↔ 2 ↔ 3 ↔ 4 ↔ 98 ↔ 402 ↔ 1024 */
    add_dnodeint_end(&head, 0);
    add_dnodeint_end(&head, 1);
    add_dnodeint_end(&head, 2);
    add_dnodeint_end(&head, 3);
    add_dnodeint_end(&head, 4);
    add_dnodeint_end(&head, 98);
    add_dnodeint_end(&head, 402);
    add_dnodeint_end(&head, 1024);

    /* Afficher la liste */
    print_dlistint(head);  // Affiche 0 1 2 3 4 98 402 1024

    /* Obtenir la longueur */
    printf("Length: %zu\n", dlistint_len(head));  // 8

    /* Obtenir un nœud à un index */
    dlistint_t *node = get_dnodeint_at_index(head, 5);
    printf("Node at index 5: %d\n", node->n);  // 98

    /* Additionner les valeurs */
    printf("Sum: %d\n", sum_dlistint(head));  // 1534

    /* Insérer un nœud à un index */
    insert_dnodeint_at_index(&head, 5, 4096);
    print_dlistint(head);  // 0 1 2 3 4 4096 98 402 1024

    /* Supprimer un nœud */
    delete_dnodeint_at_index(&head, 5);
    print_dlistint(head);  // 0 1 2 3 4 98 402 1024

    /* Libérer la mémoire */
    free_dlistint(head);
    head = NULL;

    return (0);
}
```

---

## 🎓 Progression d'Apprentissage

1. **`0-print_dlistint`** : Apprendre à traverser
2. **`1-dlistint_len`** : Compter les nœuds
3. **`2-add_dnodeint`** & **`3-add_dnodeint_end`** : Insertion
4. **`4-free_dlistint`** : Gestion mémoire
5. **`5-get_dnodeint`** : Recherche
6. **`6-sum_dlistint`** : Agrégation
7. **`7-insert_dnodeint`** : Insertion avancée
8. **`8-delete_dnodeint`** : Suppression complète
