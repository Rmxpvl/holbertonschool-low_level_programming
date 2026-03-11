# Malloc & Free

Ce dossier introduit l'**allocation dynamique de mémoire** en C avec `malloc` et `free`.

---

## Table des matières

1. [malloc et free](#1-malloc-et-free)
2. [Pourquoi utiliser malloc ?](#2-pourquoi-utiliser-malloc-)
3. [Explication des fichiers](#3-explication-des-fichiers)
4. [Points clés](#4-points-clés)
5. [Erreurs courantes](#5-erreurs-courantes)

---

## 1. malloc et free

`malloc` (**memory allocation**) alloue un bloc de mémoire sur le **tas (heap)** et retourne un pointeur vers ce bloc.

```c
#include <stdlib.h>

char *str = malloc(sizeof(char) * 10);
if (str == NULL)
    return (NULL);   /* toujours vérifier l'échec */

free(str);           /* libérer la mémoire quand elle n'est plus utilisée */
```

- `malloc` retourne `NULL` si l'allocation échoue.
- `free` libère la mémoire allouée par `malloc`.
- Toute mémoire allouée doit être libérée pour éviter les **fuites mémoire**.

---

## 2. Pourquoi utiliser malloc ?

| Allocation statique | Allocation dynamique |
|---|---|
| Taille connue à la compilation | Taille connue seulement à l'exécution |
| Stockée sur la pile (stack) | Stockée sur le tas (heap) |
| Libérée automatiquement | Doit être libérée avec `free` |

---

## 3. Explication des fichiers

| Fichier | Description |
|---|---|
| `0-create_array.c` | Crée un tableau de `char` initialisé avec un caractère donné |
| `1-strdup.c` | Duplique une chaîne de caractères en mémoire |
| `2-str_concat.c` | Concatène deux chaînes dans une nouvelle zone mémoire allouée |
| `main.h` | Fichier d'en-tête avec les prototypes des fonctions |

---

## 4. Points clés

- Toujours vérifier que `malloc` ne retourne pas `NULL` avant d'utiliser le pointeur.
- Ne jamais utiliser un pointeur après l'avoir libéré avec `free` (**use-after-free**).
- Ne pas appeler `free` deux fois sur le même pointeur (**double-free**).
- Penser à ajouter `'\0'` à la fin des chaînes allouées manuellement.

---

## 5. Erreurs courantes

- **Oublier `free`** → fuite mémoire.
- **Ne pas vérifier `NULL`** → crash si malloc échoue.
- **Écrire hors des limites** → comportement indéfini.
- **Confondre `sizeof(char *)` et `sizeof(char)`** → mauvaise taille allouée.

