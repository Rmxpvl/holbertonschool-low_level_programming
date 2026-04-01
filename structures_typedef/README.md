# Structures et Typedef en C

## 📚 Objectifs d'Apprentissage

- Définir et utiliser les structures (`struct`)
- Accéder aux membres d'une structure
- Passer des structures par pointeur
- Utiliser `typedef` pour créer des alias de types
- Allouer dynamiquement de la mémoire pour les structures
- Libérer la mémoire correctement

---

## 🎯 Concepts Clés

### Qu'est-ce qu'une Structure ?

Une **structure** est un type de données composite qui regroupe plusieurs variables de types différents sous un même nom. C'est une façon d'organiser les données liées.

**Syntaxe** :
```c
struct dog {
    char *name;      // Pointeur vers le nom
    float age;       // Âge du chien
    char *owner;     // Pointeur vers le propriétaire
};
```

### Pourquoi les Structures ?

Sans structures, il faudrait gérer trois variables séparées pour chaque chien :
```c
char *dog1_name = "Buddy";
float dog1_age = 3.5;
char *dog1_owner = "Alice";

char *dog2_name = "Luna";
float dog2_age = 2.0;
char *dog2_owner = "Bob";
```

**Avec structures** :
```c
struct dog dog1 = {"Buddy", 3.5, "Alice"};
struct dog dog2 = {"Luna", 2.0, "Bob"};
```

**Beaucoup plus lisible et maintainable !**

### Typedef pour Simplifier

***Typedef** crée un alias pour un type :

```c
// Définir et créer un alias en même temps
typedef struct dog
{
    char *name;
    float age;
    char *owner;
} dog_t;
```

Maintenant on peut utiliser `dog_t` au lieu de `struct dog` :
```c
dog_t my_dog = {"Rex", 5.0, "Charlie"};
```

### Accès aux Membres

**Avec une variable** (valeur) :
```c
struct dog my_dog = {"Buddy", 3.5, "Alice"};
printf("%s\n", my_dog.name);      // Buddy
printf("%.1f\n", my_dog.age);     // 3.5
```

**Avec un pointeur** (très commun) :
```c
struct dog *my_dog_ptr = &my_dog;
printf("%s\n", my_dog_ptr->name);  // Buddy (opérateur ->)
```

> **Note** : Avec un pointeur, on utilise `->` au lieu de `.`

---

## 📋 Fichiers et Exercices

### 1. `1-init_dog.c` — Initialiser une Structure

**Objectif** : Créer une fonction qui initialise les membres d'une structure `dog`.

**Concept** : Passer une structure par pointeur pour la modifier.

**Exemple de code** :
```c
#include "dog.h"

void init_dog(struct dog *d, char *name, float age, char *owner)
{
    if (d == NULL)              // Validation du pointeur
        return;

    d->name = name;             // Initialiser via pointeur
    d->age = age;
    d->owner = owner;
}
```

**Utilisation** :
```c
struct dog my_dog;
init_dog(&my_dog, "Buddy", 3.5, "Alice");

printf("%s\n", my_dog.name);    // Buddy
printf("%.1f\n", my_dog.age);   // 3.5
printf("%s\n", my_dog.owner);   // Alice
```

**Points Clés** :
- On passe un **pointeur** (`&my_dog`) pour modifier la structure
- On utilise `->` pour accéder aux membres via un pointeur
- On vérifie que le pointeur n'est pas NULL

---

### 2. `2-print_dog.c` — Afficher une Structure

**Objectif** : Créer une fonction qui affiche les informations d'un chien.

**Concept** : Gérer les valeurs NULL avec des vérifications et affichages alternatifs.

**Exemple de code** :
```c
#include <stdio.h>
#include "dog.h"

void print_dog(struct dog *d)
{
    if (d == NULL)
        return;

    // Utilise l'opérateur ternaire pour gérer les NULL
    printf("Name: %s\n", d->name ? d->name : "(nil)");
    printf("Age: %.6f\n", d->age);
    printf("Owner: %s\n", d->owner ? d->owner : "(nil)");
}
```

**Utilisation** :
```c
struct dog dog1 = {"Rex", 2.5, "Charlie"};
struct dog dog2 = {NULL, 1.0, "Diana"};

print_dog(&dog1);
// Output:
// Name: Rex
// Age: 2.500000
// Owner: Charlie

print_dog(&dog2);
// Output:
// Name: (nil)
// Age: 1.000000
// Owner: Diana
```

**Points Clés** :
- Gérer les pointeurs NULL avec des vérifications
- Utiliser l'opérateur ternaire (`condition ? valeur_true : valeur_false`)
- Formatter l'affichage des floats avec `%.6f`

---

### 4. `4-new_dog.c` — Créer une Structure Dynamiquement

**Objectif** : Créer une nouvelle structure `dog` en allouant la mémoire dynamiquement.

**Concept** :
- Utiliser `malloc()` pour allouer la mémoire de la structure
- Copier les chaînes de caractères (ne pas juste les pointer)
- Retourner un pointeur vers la nouvelle structure

**Exemple de code** :
```c
#include <stdlib.h>
#include "dog.h"

// Fonction helper pour copier une chaîne
char *_strcpy(char *dest, char *src)
{
    int i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

// Fonction helper pour la longueur d'une chaîne
int _strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}

// Créer un nouveau chien
dog_t *new_dog(char *name, float age, char *owner)
{
    dog_t *d;

    d = malloc(sizeof(dog_t));
    if (d == NULL)
        return (NULL);

    // Allouer et copier le nom
    d->name = malloc(_strlen(name) + 1);
    if (d->name == NULL)
    {
        free(d);
        return (NULL);
    }
    _strcpy(d->name, name);

    d->age = age;

    // Allouer et copier le propriétaire
    d->owner = malloc(_strlen(owner) + 1);
    if (d->owner == NULL)
    {
        free(d->name);
        free(d);
        return (NULL);
    }
    _strcpy(d->owner, owner);

    return (d);
}
```

**Utilisation** :
```c
dog_t *my_dog = new_dog("Buddy", 3.5, "Alice");
if (my_dog != NULL)
{
    printf("%s belongs to %s\n", my_dog->name, my_dog->owner);
    // Buddy belongs to Alice

    free(my_dog->name);
    free(my_dog->owner);
    free(my_dog);
}
```

**Points Clés** :
- `malloc()` alloue la mémoire, **il faut la libérer après**
- Toujours vérifier que `malloc()` a réussi (retour != NULL)
- Copier les chaînes au lieu de les pointer directement
- Libération : d'abord les membres, puis la structure

---

### 5. `5-free_dog.c` — Libérer une Structure

**Objectif** : Créer une fonction qui libère la mémoire allouée pour une structure dog.

**Concept** : Libérer correctement la mémoire dynamique.

**Exemple de code** :
```c
#include <stdlib.h>
#include "dog.h"

void free_dog(dog_t *d)
{
    if (d == NULL)
        return;

    free(d->name);    // Libérer le nom
    free(d->owner);   // Libérer le propriétaire
    free(d);          // Libérer la structure elle-même
}
```

**Utilisation** :
```c
dog_t *my_dog = new_dog("Luna", 2.0, "Bob");

// ... utiliser my_dog ...

free_dog(my_dog);  // Libère tous les allocations
```

**Points Clés** :
- Vérifier NULL avant de libérer
- Libérer les membres pointés d'abord
- Puis libérer la structure elle-même
- Évite les **memory leaks**

---

## 📚 Fichier Header Typique

```c
#ifndef DOG_H
#define DOG_H

#include <stdlib.h>

typedef struct dog
{
    char *name;
    float age;
    char *owner;
} dog_t;

void init_dog(struct dog *d, char *name, float age, char *owner);
void print_dog(struct dog *d);
dog_t *new_dog(char *name, float age, char *owner);
void free_dog(dog_t *d);

#endif
```

---

## 🔑 Points Clés à Retenir

| Concept | Explication |
|---------|------------|
| `struct` | Grouper plusieurs variables liées |
| `.` (point) | Accéder aux membres avec une variable |
| `->` (flèche) | Accéder aux membres avec un pointeur |
| `typedef` | Créer un alias court pour un type |
| `malloc()` | Allouer de la mémoire dynamiquement |
| `free()` | Libérer la mémoire allouée |
| Copier chaînes | Ne pas juste pointer, allouer et copier |

---

## ⚠️ Erreurs Courantes

1. **Oublier l'allocation mémoire pour les pointeurs internes**
   ```c
   // FAUX : on pointe vers une chaîne locale qui disparaît
   d->name = name;  // Risqué si name est local

   // BON : allouer et copier
   d->name = malloc(_strlen(name) + 1);
   _strcpy(d->name, name);
   ```

2. **Mélanger `.` et `->`**
   ```c
   struct dog d = {"Buddy", 3.5, "Alice"};
   struct dog *d_ptr = &d;

   // BON :
   d.name        // variable directe
   d_ptr->name   // pointeur
   ```

3. **Oublier de libérer la mémoire**
   ```c
   // FAUX : memory leak
   dog_t *dog = new_dog("Rex", 5.0, "Charlie");
   // ... fin du programme sans free

   // BON :
   free_dog(dog);
   ```

4. **Ne pas vérifier NULL après malloc**
   ```c
   // FAUX : crash potentiel
   d = malloc(sizeof(dog_t));
   d->name = malloc(...);  // Could be NULL!

   // BON :
   d = malloc(sizeof(dog_t));
   if (d == NULL)
       return (NULL);
   d->name = malloc(...);
   if (d->name == NULL)
   {
       free(d);
       return (NULL);
   }
   ```

---

## 📝 Flux Complet d'Utilisation

```c
// 1. Déclarer une structure
struct dog my_dog;

// 2. Initialiser
init_dog(&my_dog, "Buddy", 3.5, "Alice");

// 3. Afficher
print_dog(&my_dog);

// 4. Créer dynamiquement
dog_t *new_buddy = new_dog("Luna", 2.0, "Bob");

// 5. Afficher le nouveau
print_dog((struct dog *)new_buddy);

// 6. Libérer
free_dog(new_buddy);
```
