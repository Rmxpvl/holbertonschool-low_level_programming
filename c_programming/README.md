# Programmation en C – Bases

Ce dossier couvre les fondamentaux du langage C : compilation, variables, structures de contrôle, fonctions et boucles imbriquées.

---

## Table des matières

1. [Le pipeline de compilation](#1-le-pipeline-de-compilation)
2. [Variables et types de données](#2-variables-et-types-de-données)
3. [Structures de contrôle](#3-structures-de-contrôle)
4. [Fonctions](#4-fonctions)
5. [Boucles et boucles imbriquées](#5-boucles-et-boucles-imbriquées)
6. [Points clés](#points-clés)
7. [Erreurs courantes](#erreurs-courantes)

---

## 1. Le pipeline de compilation

Un programme C passe par **4 étapes** avant de devenir un exécutable :

```
code source (.c) → Préprocesseur → Compilateur → Assembleur → Éditeur de liens → exécutable
```

| Étape           | Commande gcc       | Fichier produit |
|-----------------|--------------------|-----------------|
| Préprocesseur   | `gcc -E fichier.c` | `.i`            |
| Compilation     | `gcc -c fichier.c` | `.o`            |
| Assemblage      | `gcc -S fichier.c` | `.s`            |
| Édition de liens| `gcc fichier.c -o mon_prog` | exécutable |

### Exemple minimal

```c
#include <stdio.h>

int main(void)
{
    printf("Bonjour le monde !\n");
    return (0);
}
```

**Compilation et exécution :**
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 hello.c -o hello
./hello
```

---

## 2. Variables et types de données

### Types principaux

| Type          | Taille (octets) | Plage approximative            |
|---------------|-----------------|--------------------------------|
| `char`        | 1               | -128 à 127                     |
| `int`         | 4               | -2 147 483 648 à 2 147 483 647 |
| `long int`    | 8               | très grand                     |
| `float`       | 4               | précision ~6 chiffres          |
| `double`      | 8               | précision ~15 chiffres         |

### Déclaration et initialisation

```c
int age = 25;
char lettre = 'A';
float temperature = 36.6;
```

### Afficher les tailles

```c
#include <stdio.h>

int main(void)
{
    printf("char       : %lu octets\n", sizeof(char));
    printf("int        : %lu octets\n", sizeof(int));
    printf("long int   : %lu octets\n", sizeof(long int));
    printf("float      : %lu octets\n", sizeof(float));
    printf("double     : %lu octets\n", sizeof(double));
    return (0);
}
```

---

## 3. Structures de contrôle

### if / else if / else

```c
int nombre = -5;

if (nombre > 0)
    printf("positif\n");
else if (nombre == 0)
    printf("zéro\n");
else
    printf("négatif\n");
```

### while

```c
int i = 0;

while (i < 10)
{
    printf("%d\n", i);
    i++;
}
```

### for

```c
int i;

for (i = 0; i < 10; i++)
    printf("%d\n", i);
```

---

## 4. Fonctions

Une fonction en C se compose de :
- Un **prototype** (déclaration dans un fichier `.h`)
- Une **définition** (corps dans un fichier `.c`)

### Exemple de fonction

```c
/* Prototype dans main.h */
int addition(int a, int b);

/* Définition dans 10-add.c */
int addition(int a, int b)
{
    return (a + b);
}

/* Appel dans main */
int resultat = addition(3, 7);
printf("Résultat : %d\n", resultat);  /* Affiche : Résultat : 10 */
```

### Fichier header (.h)

```c
#ifndef MAIN_H
#define MAIN_H

/* Prototypes */
int addition(int a, int b);
int valeur_absolue(int n);

#endif /* MAIN_H */
```

Les gardes `#ifndef / #define / #endif` évitent les inclusions multiples.

---

## 5. Boucles et boucles imbriquées

### Imprimer l'alphabet

```c
#include <stdio.h>

int main(void)
{
    char c = 'a';

    while (c <= 'z')
    {
        printf("%c", c);
        c++;
    }
    printf("\n");
    return (0);
}
```

### Boucle imbriquée – table de multiplication

```c
#include <stdio.h>

int main(void)
{
    int i, j;

    for (i = 0; i <= 9; i++)
    {
        for (j = 0; j <= 9; j++)
            printf("%d ", i * j);
        printf("\n");
    }
    return (0);
}
```

### FizzBuzz

```c
#include <stdio.h>

int main(void)
{
    int i;

    for (i = 1; i <= 100; i++)
    {
        if (i % 15 == 0)
            printf("FizzBuzz\n");
        else if (i % 3 == 0)
            printf("Fizz\n");
        else if (i % 5 == 0)
            printf("Buzz\n");
        else
            printf("%d\n", i);
    }
    return (0);
}
```

---

## Points clés

- Toujours inclure `<stdio.h>` pour utiliser `printf` et `putchar`.
- `main` doit toujours retourner un entier (`return (0)` en cas de succès).
- Les variables doivent être déclarées **en début de bloc** en C89/C90.
- Les gardes `#ifndef` dans les fichiers `.h` évitent les double-inclusions.
- Compiler avec `-Wall -Werror -Wextra -pedantic` pour détecter un maximum d'erreurs.
- `sizeof` retourne un `size_t` (non signé) → utiliser `%lu` pour l'afficher.
- Un `for` se décompose : `for (initialisation ; condition ; incrémentation)`.
- En C, `char` est un entier → on peut faire de l'arithmétique sur les caractères.

---

## Erreurs courantes

| Erreur | Description | Correction |
|--------|-------------|------------|
| Oubli du `\n` | Le texte ne va pas à la ligne | Ajouter `\n` dans `printf` |
| `=` au lieu de `==` | Affectation au lieu de comparaison | Utiliser `==` pour tester l'égalité |
| Variable non initialisée | Valeur imprévisible | Toujours initialiser les variables |
| Oubli de `return` | Comportement indéfini | Ajouter `return (0)` dans `main` |
| Boucle infinie | Condition toujours vraie | Vérifier que la variable évolue bien |
| Débordement d'entier | Résultat incorrect avec de grands nombres | Utiliser `long int` ou `long long` |

---

## Fichiers de référence

- [`../hello_world/`](../hello_world/) – Compilation et affichage de base
- [`../variables_if_else_while/`](../variables_if_else_while/) – Variables, conditions et boucles
- [`../functions_nested_loops/`](../functions_nested_loops/) – Fonctions et boucles imbriquées
- [`../more_functions_nested_loops/`](../more_functions_nested_loops/) – Fonctions avancées et dessins
