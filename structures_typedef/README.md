# Structures & Typedef

Ce dossier introduit les **structures** en C : comment regrouper plusieurs variables de types différents dans une seule entité, et comment utiliser `typedef` pour simplifier la syntaxe.

---

## Table des matières

1. [Les structures en C](#1-les-structures-en-c)
2. [Accéder aux membres d'une structure](#2-accéder-aux-membres-dune-structure)
3. [Pointeurs et structures](#3-pointeurs-et-structures)
4. [Typedef](#4-typedef)
5. [Allocation dynamique avec structures](#5-allocation-dynamique-avec-structures)
6. [Explication des fichiers](#6-explication-des-fichiers)
7. [Points clés](#7-points-clés)
8. [Erreurs courantes](#8-erreurs-courantes)

---

## 1. Les structures en C

Une **structure** est un type de donnée composé qui permet de regrouper plusieurs variables, même de types différents, dans une seule entité.

### Déclaration d'une structure

```c
struct dog
{
    char *name;
    float age;
    char *owner;
};
```

Cela crée un type appelé `struct dog`, qui possède trois membres :
- `name` : un pointeur vers une chaîne de caractères
- `age` : un nombre flottant
- `owner` : un pointeur vers une chaîne de caractères

### Créer une variable de type structure

```c
struct dog my_dog;

my_dog.name = "Buddy";
my_dog.age = 3.5;
my_dog.owner = "John";
```

---

## 2. Accéder aux membres d'une structure

### Avec une variable simple (utiliser le point `.`)

```c
struct dog my_dog;

my_dog.name = "Rex";
my_dog.age = 5.0;

printf("Nom: %s\n", my_dog.name);    /* Affiche: Nom: Rex */
printf("Âge: %.1f\n", my_dog.age);   /* Affiche: Âge: 5.0 */
```

### Avec un pointeur (utiliser la flèche `->`)

```c
struct dog *ptr = &my_dog;

ptr->name = "Buddy";
ptr->age = 2.5;

printf("Nom: %s\n", ptr->name);
printf("Âge: %.1f\n", ptr->age);
```

L'opérateur `->` est équivalent à `(*pointeur).membre`, mais plus lisible.

---

## 3. Pointeurs et structures

Les pointeurs sont essentiels pour passer une structure à une fonction et pouvoir la modifier.

### Passer une structure par référence

```c
/**
 * init_dog - initializes a variable of type struct dog
 * @d: pointer to struct dog to initialize
 * @name: name of the dog
 * @age: age of the dog
 * @owner: owner of the dog
 */
void init_dog(struct dog *d, char *name, float age, char *owner)
{
    if (d == NULL)
        return;

    d->name = name;
    d->age = age;
    d->owner = owner;
}
```

**Utilisation :**
```c
struct dog my_dog;
init_dog(&my_dog, "Buddy", 3.5, "John");
```

Le `&` passe l'adresse de la structure, ce qui permet à la fonction de la modifier.

### Afficher le contenu d'une structure

```c
/**
 * print_dog - prints a struct dog
 * @d: pointer to struct dog to print
 * Description: If an element of d is NULL, print (nil) instead
 */
void print_dog(struct dog *d)
{
    if (d == NULL)
        return;

    printf("Name: %s\n", d->name ? d->name : "(nil)");
    printf("Age: %.6f\n", d->age);
    printf("Owner: %s\n", d->owner ? d->owner : "(nil)");
}
```

**Sortie :**
```
Name: Buddy
Age: 3.500000
Owner: John
```

---

## 4. Typedef

`typedef` permet de créer un **alias** pour un type, rendant le code plus lisible.

### Sans typedef

```c
struct dog my_dog;
struct dog *ptr = &my_dog;
```

### Avec typedef

```c
typedef struct dog dog_t;

dog_t my_dog;
dog_t *ptr = &my_dog;
```

L'alias `dog_t` est plus court que `struct dog`.

### Typedef avec définition implicite

```c
typedef struct dog
{
    char *name;
    float age;
    char *owner;
} dog_t;
```

Cela définit la structure ET crée l'alias `dog_t` en une seule opération.

---

## 5. Allocation dynamique avec structures

Pour créer une structure dynamiquement avec `malloc`, il faut :
1. Allouer la mémoire pour la structure
2. Copier les chaînes dans la mémoire allouée (puisque les pointeurs pointent sur des données temporaires)
3. Libérer la mémoire avec `free`

### Créer une nouvelle structure dynamiquement

```c
#include <stdlib.h>
#include <string.h>

dog_t *new_dog(char *name, float age, char *owner)
{
    dog_t *d;

    if (name == NULL || owner == NULL)
        return (NULL);

    d = malloc(sizeof(dog_t));  /* Allouer la structure */
    if (d == NULL)
        return (NULL);

    d->name = malloc(_strlen(name) + 1);      /* Allouer pour le nom */
    if (d->name == NULL)
        return (NULL);
    d->name = _strcpy(d->name, name);

    d->age = age;

    d->owner = malloc(_strlen(owner) + 1);    /* Allouer pour le propriétaire */
    if (d->owner == NULL)
        return (NULL);
    d->owner = _strcpy(d->owner, owner);

    return (d);
}
```

### Libérer une structure dynamique

```c
void free_dog(dog_t *d)
{
    if (d == NULL)
        return;

    free(d->name);      /* Libérer le nom */
    free(d->owner);     /* Libérer le propriétaire */
    free(d);            /* Libérer la structure elle-même */
}
```

**Important :** Libérer les membres avant de libérer la structure !

---

## 6. Explication des fichiers

| Fichier | Description |
|---|---|
| `dog.h` | Fichier d'en-tête contenant la définition de `struct dog` et les prototypes |
| `1-init_dog.c` | Initialise une structure `dog` donnée |
| `2-print_dog.c` | Affiche le contenu d'une structure `dog` |
| `4-new_dog.c` | Crée dynamiquement une nouvelle structure `dog` avec copies des chaînes |
| `5-free_dog.c` | Libère une structure `dog` créée dynamiquement |

---

## 7. Points clés

- Une structure regroupe des variables de types différents.
- Accéder aux membres d'une structure avec le point (`.`) ou la flèche (`->` pour les pointeurs).
- Passer une structure par pointeur (`&variable`) pour pouvoir la modifier dans une fonction.
- `typedef` crée un alias pour simplifier la syntaxe.
- Avec allocation dynamique, allouer **individuellement** les chaînes dans la structure.
- Toujours libérer les pointeurs **avant** de libérer la structure elle-même.

---

## 8. Erreurs courantes

- **Oublier de vérifier `NULL`** avant d'utiliser un pointeur → crash ou comportement indéfini.
- **Confondre `.` et `->`** → `.` pour les variables, `->` pour les pointeurs.
- **Oublier de copier les chaînes** → Si on assigne des pointeurs temporaires, les données disparaissent.
- **Libérer dans le mauvais ordre** → Libérer la structure avant ses membres conduit à une fuite mémoire.
- **Ne pas initialiser une structure statique** → Les valeurs non initialisées sont indéterminées.