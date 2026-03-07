# Structures de Données

Ce dossier couvre les principales structures de données utilisées en programmation C : listes chaînées, piles, files et arbres binaires.

---

## Table des matières

1. [Listes chaînées simples](#1-listes-chaînées-simples)
2. [Listes doublement chaînées](#2-listes-doublement-chaînées)
3. [Piles (Stack)](#3-piles-stack)
4. [Files (Queue)](#4-files-queue)
5. [Arbres binaires](#5-arbres-binaires)
6. [Points clés](#points-clés)
7. [Erreurs courantes](#erreurs-courantes)

---

## 1. Listes chaînées simples

Une **liste chaînée** est une suite de nœuds, chacun contenant une donnée et un pointeur vers le nœud suivant.

```
[10 | •] → [20 | •] → [30 | NULL]
```

### Définition du nœud

```c
/**
 * struct noeud_s - Nœud d'une liste chaînée
 * @n: valeur entière stockée
 * @suivant: pointeur vers le nœud suivant
 */
typedef struct noeud_s
{
    int n;
    struct noeud_s *suivant;
} noeud_t;
```

### Ajouter en tête de liste

```c
noeud_t *ajouter_en_tete(noeud_t **tete, int valeur)
{
    noeud_t *nouveau;

    nouveau = malloc(sizeof(noeud_t));
    if (nouveau == NULL)
        return (NULL);

    nouveau->n = valeur;
    nouveau->suivant = *tete;
    *tete = nouveau;

    return (nouveau);
}
```

### Afficher la liste

```c
void afficher_liste(noeud_t *tete)
{
    while (tete != NULL)
    {
        printf("%d\n", tete->n);
        tete = tete->suivant;
    }
}
```

### Libérer la liste

```c
void liberer_liste(noeud_t **tete)
{
    noeud_t *courant;
    noeud_t *suivant;

    courant = *tete;
    while (courant != NULL)
    {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
    *tete = NULL;
}
```

### Longueur de la liste

```c
size_t longueur_liste(noeud_t *tete)
{
    size_t count = 0;

    while (tete != NULL)
    {
        count++;
        tete = tete->suivant;
    }
    return (count);
}
```

---

## 2. Listes doublement chaînées

Chaque nœud pointe vers le suivant **et** le précédent.

```
NULL ← [10 | • | •] ↔ [20 | • | •] ↔ [30 | • | NULL]
```

```c
typedef struct noeud_double_s
{
    int n;
    struct noeud_double_s *precedent;
    struct noeud_double_s *suivant;
} noeud_double_t;
```

---

## 3. Piles (Stack)

Une **pile** fonctionne en mode **LIFO** (Last In, First Out) : le dernier élément ajouté est le premier sorti.

Opérations : `push` (empiler), `pop` (dépiler), `peek` (regarder le sommet).

```c
typedef struct pile_s
{
    int donnee;
    struct pile_s *suivant;
} pile_t;

/* Empiler un élément */
void push(pile_t **sommet, int valeur)
{
    pile_t *nouveau = malloc(sizeof(pile_t));

    if (nouveau == NULL)
        return;
    nouveau->donnee = valeur;
    nouveau->suivant = *sommet;
    *sommet = nouveau;
}

/* Dépiler un élément */
int pop(pile_t **sommet)
{
    pile_t *temp;
    int valeur;

    if (*sommet == NULL)
        return (-1);   /* Pile vide */

    temp = *sommet;
    valeur = temp->donnee;
    *sommet = temp->suivant;
    free(temp);
    return (valeur);
}
```

**Cas d'usage :** appels de fonctions (call stack), undo/redo, expressions arithmétiques.

---

## 4. Files (Queue)

Une **file** fonctionne en mode **FIFO** (First In, First Out) : le premier élément ajouté est le premier sorti.

```c
typedef struct file_s
{
    int donnee;
    struct file_s *suivant;
} file_t;

/* Enfiler (enqueue) */
void enfiler(file_t **tete, file_t **queue, int valeur)
{
    file_t *nouveau = malloc(sizeof(file_t));

    if (nouveau == NULL)
        return;
    nouveau->donnee = valeur;
    nouveau->suivant = NULL;

    if (*queue != NULL)
        (*queue)->suivant = nouveau;
    else
        *tete = nouveau;
    *queue = nouveau;
}

/* Défiler (dequeue) */
int defiler(file_t **tete, file_t **queue)
{
    file_t *temp;
    int valeur;

    if (*tete == NULL)
        return (-1);   /* File vide */

    temp = *tete;
    valeur = temp->donnee;
    *tete = temp->suivant;
    if (*tete == NULL)
        *queue = NULL;
    free(temp);
    return (valeur);
}
```

**Cas d'usage :** gestion de tâches, tampons d'entrée/sortie, algorithmes de parcours en largeur.

---

## 5. Arbres binaires

Un **arbre binaire** est une structure où chaque nœud a au plus deux enfants (gauche et droit).

```
        [8]
       /   \
     [3]   [10]
    /   \      \
  [1]   [6]   [14]
```

```c
typedef struct arbre_s
{
    int n;
    struct arbre_s *parent;
    struct arbre_s *gauche;
    struct arbre_s *droite;
} arbre_t;

/* Créer un nouveau nœud */
arbre_t *creer_noeud(arbre_t *parent, int valeur)
{
    arbre_t *nouveau = malloc(sizeof(arbre_t));

    if (nouveau == NULL)
        return (NULL);
    nouveau->n = valeur;
    nouveau->parent = parent;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;
    return (nouveau);
}
```

### Parcours

| Ordre     | Description                          | Séquence (exemple) |
|-----------|--------------------------------------|--------------------|
| Préfixe   | Racine → Gauche → Droite             | 8, 3, 1, 6, 10, 14 |
| Infixe    | Gauche → Racine → Droite (trié)      | 1, 3, 6, 8, 10, 14 |
| Suffixe   | Gauche → Droite → Racine             | 1, 6, 3, 14, 10, 8 |

---

## Points clés

- Toujours vérifier que `malloc` ne retourne pas `NULL` avant d'utiliser un nœud.
- Libérer la mémoire après utilisation pour éviter les fuites.
- La tête d'une liste est souvent passée en `**` pour pouvoir la modifier.
- Les piles s'implémentent facilement avec une liste chaînée (ajout/suppression en tête).
- Les files nécessitent deux pointeurs : tête (défilement) et queue (enfilement).
- Un arbre binaire de recherche (ABR) maintient l'ordre : gauche < racine < droite.

---

## Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Oublier de mettre `NULL` le `suivant` du dernier nœud | Boucle infinie lors du parcours | Initialiser `->suivant = NULL` |
| Perdre la référence à la tête | Impossible de libérer la liste | Sauvegarder la tête dans une variable |
| Ne pas libérer avant de réaffecter | Fuite mémoire | Toujours `free` avant de perdre la référence |
| Accéder à un nœud après `free` | Dangling pointer | Mettre à `NULL` après `free` |
| Pop sur pile vide | Segfault ou comportement indéfini | Vérifier `if (*sommet != NULL)` avant pop |
