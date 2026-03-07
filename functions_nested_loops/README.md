# Fonctions et Boucles Imbriquées

Ce dossier introduit la notion de **fonction** en C : comment en déclarer, en définir et en appeler. Il couvre aussi les boucles imbriquées et les fichiers d'en-tête.

---

## Table des matières

1. [Les fonctions en C](#1-les-fonctions-en-c)
2. [Les fichiers d'en-tête (header files)](#2-les-fichiers-den-tête-header-files)
3. [Les boucles imbriquées](#3-les-boucles-imbriquées)
4. [La fonction _putchar](#4-la-fonction-_putchar)
5. [Explication des fichiers](#5-explication-des-fichiers)
6. [Points clés](#6-points-clés)
7. [Erreurs courantes](#7-erreurs-courantes)

---

## 1. Les fonctions en C

Une fonction est un **bloc de code réutilisable** qui effectue une tâche précise. Elle évite la répétition et rend le code plus lisible.

### Anatomie d'une fonction

```c
/* Déclaration (prototype) — généralement dans main.h */
int add(int a, int b);

/* Définition — dans le fichier .c */
int add(int a, int b)
{
    return (a + b);
}

/* Appel */
int resultat = add(3, 5);   /* resultat vaut 8 */
```

### Fonctions sans valeur de retour

```c
void print_alphabet(void)
{
    char c;

    for (c = 'a'; c <= 'z'; c++)
        _putchar(c);
    _putchar('\n');
}
```

`void` indique que la fonction ne retourne rien.

---

## 2. Les fichiers d'en-tête (header files)

Le fichier `main.h` contient les **prototypes** (déclarations) de toutes les fonctions.

```c
/* main.h */
#ifndef MAIN_H
#define MAIN_H

int _putchar(char c);
void print_alphabet(void);
int _islower(int c);
int _isalpha(int c);
int print_sign(int n);
int _abs(int n);
int add(int a, int b);

#endif
```

- `#ifndef MAIN_H` / `#define MAIN_H` / `#endif` : **include guard** — empêche l'inclusion multiple du même fichier.
- Chaque fichier `.c` qui utilise ces fonctions doit inclure `"main.h"`.

---

## 3. Les boucles imbriquées

Une boucle imbriquée est une boucle à l'intérieur d'une autre boucle. Utile pour les tableaux à 2 dimensions, les tables de multiplication, les affichages en grille.

```c
/* Imprimer l'alphabet 10 fois */
void print_alphabet_x10(void)
{
    char c;
    int i;

    for (i = 0; i < 10; i++)        /* boucle externe : 10 répétitions */
    {
        for (c = 'a'; c <= 'z'; c++) /* boucle interne : l'alphabet */
            _putchar(c);
        _putchar('\n');
    }
}
```

```c
/* Table de multiplication 9 × 9 */
void times_table(void)
{
    int i, j, result;

    for (i = 0; i <= 9; i++)
    {
        for (j = 0; j <= 9; j++)
        {
            result = i * j;
            /* affichage formaté avec _putchar */
        }
        _putchar('\n');
    }
}
```

---

## 4. La fonction _putchar

`_putchar` est une version simplifiée de `putchar` utilisée pour afficher **un seul caractère**. Elle est déclarée dans `main.h` et fournie par le système.

```c
_putchar('H');   /* affiche H */
_putchar('\n');  /* retour à la ligne */
```

---

## 5. Explication des fichiers

### 0-putchar.c — Démonstration de _putchar

Affiche `_putchar` lettre par lettre en appelant `_putchar` pour chaque caractère. Montre le fonctionnement de base.

### 1-alphabet.c — Afficher l'alphabet

```c
void print_alphabet(void)
{
    char c;
    for (c = 'a'; c <= 'z'; c++)
        _putchar(c);
    _putchar('\n');
}
```

### 2-print_alphabet_x10.c — Alphabet 10 fois

Double boucle : externe compte de 0 à 9, interne parcourt l'alphabet.

### 3-islower.c — Vérifier si minuscule

```c
int _islower(int c)
{
    if (c >= 'a' && c <= 'z')
        return (1);
    return (0);
}
```

Retourne 1 si le caractère est entre `'a'` et `'z'`, 0 sinon.

### 4-isalpha.c — Vérifier si alphabétique

```c
int _isalpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}
```

Vérifie les minuscules ET les majuscules.

### 5-sign.c — Signe d'un nombre

```c
int print_sign(int n)
{
    if (n > 0)      { _putchar('+'); return (1); }
    else if (n == 0){ _putchar('0'); return (0); }
    else            { _putchar('-'); return (-1); }
}
```

### 6-abs.c — Valeur absolue

```c
int _abs(int n)
{
    if (n < 0)
        return (-n);
    return (n);
}
```

Si `n` est négatif, on retourne `-n` (qui devient positif).

### 7-print_last_digit.c — Dernier chiffre

```c
int print_last_digit(int n)
{
    int last = n % 10;
    if (last < 0)
        last = -last;   /* pour les nombres négatifs */
    _putchar(last + '0');
    return (last);
}
```

### 8-24_hours.c — Toutes les minutes de la journée

Double boucle : heures (0-23) × minutes (0-59). Affiche au format `HH:MM`.

### 9-times_table.c — Table de multiplication 9×9

Double boucle imbriquée, avec formatage soigné (espaces pour aligner).

### 10-add.c — Addition

```c
int add(int a, int b)
{
    return (a + b);
}
```

Fonction simple qui retourne la somme de deux entiers.

### 11-print_to_98.c — De n jusqu'à 98

```c
void print_to_98(int n)
{
    if (n <= 98)
    {
        while (n < 98) { printf("%d, ", n); n++; }
    }
    else
    {
        while (n > 98) { printf("%d, ", n); n--; }
    }
    printf("98\n");
}
```

Gère les deux cas : `n` plus petit ou plus grand que 98.

---

## 6. Points clés

- Une fonction doit être **déclarée** (prototype) avant d'être **appelée**.
- Le type de retour `void` signifie que la fonction ne retourne **aucune valeur**.
- Les fichiers d'en-tête avec `#ifndef`/`#define`/`#endif` évitent les inclusions multiples.
- `_putchar(c + '0')` convertit un chiffre entier (0-9) en son caractère ASCII.
- Pour les nombres négatifs, le modulo peut retourner un résultat négatif — penser à prendre la valeur absolue.
- Les boucles imbriquées s'exécutent de l'intérieur vers l'extérieur : pour chaque itération de la boucle externe, la boucle interne s'exécute entièrement.

---

## 7. Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Oublier d'inclure `"main.h"` | Les fonctions semblent inconnues du compilateur | Ajouter `#include "main.h"` en tête de chaque `.c` |
| Pas de prototype dans `main.h` | Erreur de compilation lors de l'appel | Ajouter le prototype dans `main.h` |
| Boucle externe/interne inversée | L'alphabet s'affiche une fois au lieu de 10 | Vérifier l'ordre : boucle externe = répétitions |
| Modulo négatif ignoré | `print_last_digit(-15)` retourne -5 au lieu de 5 | Appliquer `-last` si `last < 0` |
| Oublier `_putchar('\n')` à la fin | Pas de retour à la ligne | Toujours terminer l'affichage par `\n` |
