# Gestion de la Mémoire en C

Ce dossier couvre les pointeurs, les tableaux, les chaînes de caractères et l'allocation dynamique de mémoire en C.

---

## Table des matières

1. [Les pointeurs](#1-les-pointeurs)
2. [Relation pointeurs et tableaux](#2-relation-pointeurs-et-tableaux)
3. [Chaînes de caractères](#3-chaînes-de-caractères)
4. [Fonctions de manipulation de chaînes](#4-fonctions-de-manipulation-de-chaînes)
5. [Allocation dynamique – malloc et free](#5-allocation-dynamique--malloc-et-free)
6. [Points clés](#points-clés)
7. [Erreurs courantes](#erreurs-courantes)

---

## 1. Les pointeurs

Un **pointeur** est une variable qui stocke l'**adresse mémoire** d'une autre variable.

```
Variable n :  [ 42 ]  → adresse en mémoire : 0x7ffd1234
Pointeur p :  [ 0x7ffd1234 ]  → pointe vers n
```

### Déclarer et utiliser un pointeur

```c
#include <stdio.h>

int main(void)
{
    int n = 42;
    int *p;          /* Déclaration d'un pointeur vers int */

    p = &n;          /* p reçoit l'adresse de n */

    printf("Valeur de n      : %d\n", n);     /* 42 */
    printf("Adresse de n     : %p\n", &n);    /* 0x7ffd... */
    printf("Valeur de p      : %p\n", p);     /* 0x7ffd... (même adresse) */
    printf("Valeur pointée   : %d\n", *p);    /* 42  – déréférencement */

    *p = 98;         /* Modifie n via le pointeur */
    printf("n après *p = 98 : %d\n", n);      /* 98 */

    return (0);
}
```

### Passer un pointeur à une fonction (passage par référence)

```c
void reinitialiser(int *nb)
{
    *nb = 98;        /* Modifie la variable originale */
}

int main(void)
{
    int x = 5;

    reinitialiser(&x);
    printf("x = %d\n", x);   /* 98 */
    return (0);
}
```

### Échanger deux variables

```c
void echanger(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

---

## 2. Relation pointeurs et tableaux

En C, le nom d'un tableau est un **pointeur vers son premier élément**.

```c
int tab[5] = {10, 20, 30, 40, 50};
int *p = tab;        /* Équivaut à : p = &tab[0] */

/* Accès équivalents */
printf("%d\n", tab[2]);    /* 30 */
printf("%d\n", *(p + 2));  /* 30 – arithmétique de pointeurs */
printf("%d\n", p[2]);      /* 30 – notation tableau sur pointeur */
```

### Inverser un tableau

```c
void inverser_tableau(int *tableau, int taille)
{
    int debut = 0;
    int fin = taille - 1;
    int temp;

    while (debut < fin)
    {
        temp = tableau[debut];
        tableau[debut] = tableau[fin];
        tableau[fin] = temp;
        debut++;
        fin--;
    }
}
```

---

## 3. Chaînes de caractères

En C, une chaîne est un **tableau de `char`** terminé par le caractère nul `'\0'`.

```c
char bonjour[] = "Bonjour";
/*  b  o  n  j  o  u  r  \0  */
/*  [0][1][2][3][4][5][6][ 7] */
```

```c
#include <stdio.h>

int main(void)
{
    char msg[] = "Holberton";
    char *p = msg;

    /* Parcourir une chaîne avec un pointeur */
    while (*p != '\0')
    {
        printf("%c", *p);
        p++;
    }
    printf("\n");
    return (0);
}
```

---

## 4. Fonctions de manipulation de chaînes

### Longueur d'une chaîne (strlen)

```c
int _strlen(char *s)
{
    int longueur = 0;

    while (*s != '\0')
    {
        longueur++;
        s++;
    }
    return (longueur);
}
```

### Copier une chaîne (strcpy)

```c
char *_strcpy(char *dest, char *src)
{
    char *debut = dest;

    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';    /* Terminer avec le caractère nul */
    return (debut);
}
```

### Convertir en entier (atoi)

```c
int _atoi(char *s)
{
    int resultat = 0;
    int signe = 1;

    while (*s == '-' || *s == '+')
    {
        if (*s == '-')
            signe *= -1;
        s++;
    }
    while (*s >= '0' && *s <= '9')
    {
        resultat = resultat * 10 + (*s - '0');
        s++;
    }
    return (resultat * signe);
}
```

---

## 5. Allocation dynamique – malloc et free

L'allocation **statique** (tableaux, variables locales) est réservée sur la **pile (stack)**.
L'allocation **dynamique** (`malloc`) est réservée sur le **tas (heap)** et persiste jusqu'à `free`.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *tableau;
    int taille = 5;
    int i;

    /* Allouer de la mémoire pour 5 entiers */
    tableau = malloc(sizeof(int) * taille);
    if (tableau == NULL)   /* TOUJOURS vérifier le retour de malloc */
    {
        fprintf(stderr, "Erreur : malloc a échoué\n");
        return (1);
    }

    /* Utiliser le tableau */
    for (i = 0; i < taille; i++)
        tableau[i] = i * 10;

    for (i = 0; i < taille; i++)
        printf("%d ", tableau[i]);
    printf("\n");

    /* TOUJOURS libérer la mémoire allouée */
    free(tableau);
    tableau = NULL;    /* Bonne pratique : évite les dangling pointers */

    return (0);
}
```

### Règles malloc/free

| Règle | Explication |
|-------|-------------|
| Vérifier `NULL` | `malloc` peut échouer et retourner `NULL` |
| Un `free` par `malloc` | Chaque allocation doit être libérée exactement une fois |
| Ne pas `free` deux fois | Provoque un comportement indéfini |
| Ne pas utiliser après `free` | Dangling pointer – comportement indéfini |
| `calloc` initialise à zéro | `malloc` ne le fait pas |

---

## Points clés

- `*` devant un pointeur **déréférence** (accède à la valeur pointée).
- `&` devant une variable donne son **adresse mémoire**.
- Un tableau est un pointeur constant vers son premier élément.
- Une chaîne en C se termine **toujours** par `'\0'`.
- `malloc` retourne `void *` → le convertir au type voulu (ou laisser faire C).
- Toujours `free` ce qu'on a `malloc` – sinon c'est une **fuite mémoire**.
- Valgrind permet de détecter les fuites mémoire : `valgrind ./programme`.

---

## Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Déréférencer un pointeur NULL | Segfault au runtime | Toujours vérifier `if (p != NULL)` |
| Oublier `'\0'` dans une chaîne | Comportement indéfini lors du parcours | Allouer `strlen + 1` et ajouter `'\0'` |
| Lire hors des limites d'un tableau | Accès mémoire invalide | Vérifier les indices avec la taille |
| Oublier `free` | Fuite mémoire | Toujours `free` après utilisation |
| Double `free` | Corruption du tas | Mettre le pointeur à `NULL` après `free` |
| Retourner un pointeur vers une variable locale | La variable est détruite à la fin de la fonction | Utiliser `malloc` pour allouer sur le tas |

---

## Fichiers de référence

- [`../pointers_arrays_strings/`](../pointers_arrays_strings/) – Exercices sur les pointeurs, tableaux et chaînes
