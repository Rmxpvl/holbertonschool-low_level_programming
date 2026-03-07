# Pointeurs, Tableaux et Chaînes de Caractères

Ce dossier couvre l'un des sujets les plus importants (et les plus difficiles) du langage C : les **pointeurs**, les **tableaux** et la **manipulation de chaînes**. On y réimplémente des fonctions de la bibliothèque standard.

---

## Table des matières

1. [Les pointeurs en C](#1-les-pointeurs-en-c)
2. [Passer par pointeur (passage par référence)](#2-passer-par-pointeur-passage-par-référence)
3. [Les tableaux](#3-les-tableaux)
4. [Les chaînes de caractères](#4-les-chaînes-de-caractères)
5. [Explication des fichiers](#5-explication-des-fichiers)
6. [Points clés](#6-points-clés)
7. [Erreurs courantes](#7-erreurs-courantes)

---

## 1. Les pointeurs en C

Un **pointeur** est une variable qui stocke une **adresse mémoire**.

```c
int n = 42;
int *p = &n;    /* p contient l'adresse de n */

printf("%d\n", n);   /* 42  — valeur de n */
printf("%p\n", p);   /* 0x7ffd... — adresse de n */
printf("%d\n", *p);  /* 42  — valeur à l'adresse pointée par p */

*p = 100;    /* modifie n via le pointeur */
printf("%d\n", n);   /* 100 */
```

| Opérateur | Nom | Rôle |
|-----------|-----|------|
| `&n` | Adresse de | Retourne l'adresse de `n` |
| `*p` | Déréférencement | Accède à la valeur à l'adresse `p` |

---

## 2. Passer par pointeur (passage par référence)

En C, les paramètres sont passés **par valeur** : la fonction reçoit une copie. Pour modifier la variable originale, on passe son **adresse**.

### Mettre à jour une valeur — 0-reset_to_98.c

```c
void reset_to_98(int *n)
{
    *n = 98;    /* modifie la variable originale */
}

int main(void)
{
    int x = 10;
    reset_to_98(&x);   /* passe l'adresse de x */
    printf("%d\n", x); /* 98 */
    return (0);
}
```

### Échanger deux valeurs — 1-swap.c

```c
void swap_int(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
```

On utilise une variable temporaire `temp` pour ne pas perdre une valeur lors de l'échange.

---

## 3. Les tableaux

Un tableau est une suite d'éléments du même type en mémoire contiguë. Le nom d'un tableau est un pointeur vers son premier élément.

```c
int tab[5] = {10, 20, 30, 40, 50};

/* Accès par index */
printf("%d\n", tab[2]);   /* 30 */

/* Accès par pointeur (équivalent) */
int *p = tab;
printf("%d\n", *(p + 2)); /* 30 */
```

### Inverser un tableau — 4-rev_array.c

```c
void reverse_array(int *a, int n)
{
    int i, temp;
    for (i = 0; i < n / 2; i++)
    {
        temp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = temp;
    }
}
```

---

## 4. Les chaînes de caractères

En C, une chaîne est un **tableau de `char`** terminé par le caractère nul `'\0'`.

```c
char msg[] = "Bonjour";
/* Equivalent à : {'B','o','n','j','o','u','r','\0'} */
```

### Longueur d'une chaîne — 2-strlen.c

```c
int _strlen(char *s)
{
    int length = 0;
    while (s[length] != '\0')
        length++;
    return (length);
}
```

### Afficher une chaîne — 3-puts.c

```c
void _puts(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
    _putchar('\n');
}
```

### Afficher en sens inverse — 4-print_rev.c

```c
void print_rev(char *s)
{
    int len = 0;
    while (s[len] != '\0')
        len++;
    while (len > 0)
    {
        len--;
        _putchar(s[len]);
    }
    _putchar('\n');
}
```

### Inverser une chaîne en place — 5-rev_string.c

```c
void rev_string(char *s)
{
    int i, len = 0;
    char tmp;
    while (s[len] != '\0')
        len++;
    for (i = 0; i < len / 2; i++)
    {
        tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}
```

### Copier une chaîne — 9-strcpy.c

```c
char *_strcpy(char *dest, char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';    /* ne pas oublier le caractère nul final */
    return (dest);
}
```

### Convertir une chaîne en entier — 100-atoi.c

```c
int _atoi(char *s)
{
    int result = 0, sign = 1, i = 0, started = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '-')          sign *= -1;
        else if (s[i] >= '0' && s[i] <= '9')
        {
            result = result * 10 + s[i] - '0';
            started = 1;
        }
        else if (started)          break;
        i++;
    }
    return (result * sign);
}
```

`s[i] - '0'` transforme le caractère chiffre en entier (ex : `'7' - '0' = 7`).

---

## 5. Explication des fichiers

| Fichier | Concept | Description |
|---------|---------|-------------|
| `0-reset_to_98.c` | Pointeur en paramètre | Met la valeur pointée à 98 |
| `1-swap.c` | Échange par pointeurs | Échange les valeurs de deux entiers |
| `2-strlen.c` | Parcours de chaîne | Compte les caractères jusqu'à `\0` |
| `3-puts.c` | Affichage caractère par caractère | Réimplémente `puts` |
| `4-print_rev.c` | Parcours inverse | Affiche une chaîne à l'envers |
| `5-rev_string.c` | Modification en place | Inverse une chaîne dans son tampon |
| `6-puts2.c` | Affichage conditionnel | Affiche 1 caractère sur 2 |
| `7-puts_half.c` | Calcul d'index | Affiche la seconde moitié d'une chaîne |
| `8-print_array.c` | Tableau d'entiers | Affiche les `n` premiers éléments |
| `9-strcpy.c` | Copie de chaîne | Réimplémente `strcpy` |
| `0-strcat.c` | Concaténation | Réimplémente `strcat` |
| `1-strncat.c` | Concaténation limitée | Réimplémente `strncat` (max n chars) |
| `2-strncpy.c` | Copie limitée | Réimplémente `strncpy` |
| `3-strcmp.c` | Comparaison | Réimplémente `strcmp` |
| `0-memset.c` | Remplissage mémoire | Réimplémente `memset` |
| `1-memcpy.c` | Copie mémoire | Réimplémente `memcpy` |
| `100-atoi.c` | Conversion | Convertit une chaîne en entier |

---

## 6. Points clés

- Un pointeur stocke une **adresse**, pas une valeur. `*p` accède à la valeur à cette adresse.
- `&variable` donne l'adresse de la variable.
- Pour modifier une variable depuis une fonction, passer son adresse avec `&` et recevoir un pointeur `*`.
- Une chaîne C se termine **toujours** par `'\0'` — oublier ce caractère cause des comportements indéfinis.
- `tab[i]` est équivalent à `*(tab + i)` — un tableau est un pointeur vers son premier élément.
- Pour inverser une chaîne, échanger les éléments symétriques : `s[0]` ↔ `s[n-1]`, `s[1]` ↔ `s[n-2]`, etc.
- `s[i] - '0'` convertit un caractère chiffre en entier (valable pour `'0'` à `'9'`).

---

## 7. Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Oublier `'\0'` dans `_strcpy` | La chaîne copiée n'est pas terminée → comportement indéfini | Ajouter `dest[i] = '\0'` après la boucle |
| Déréférencer `NULL` | `*p` quand `p == NULL` → segfault | Vérifier que le pointeur n'est pas `NULL` avant |
| Passer une valeur au lieu d'un pointeur | `reset_to_98(n)` au lieu de `reset_to_98(&n)` | Utiliser `&` pour passer l'adresse |
| Ne pas mettre `\0` dans un tableau de chars | Affichage aléatoire au-delà de la chaîne | Toujours terminer les chaînes avec `'\0'` |
| Confondre `tab` et `&tab` | `tab` est l'adresse du premier élément, `&tab` est l'adresse du tableau entier | Utiliser `tab` (sans `&`) pour passer un tableau |
| Off-by-one dans `rev_string` | `len / 2` arrondi vers le bas — correct pour les longueurs impaires | Ne pas échanger l'élément central dans les longueurs impaires |
