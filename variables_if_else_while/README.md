# Variables, if/else, while – Structures de base en C

Ce dossier couvre les fondamentaux du langage C : déclaration de variables, structures conditionnelles et boucles `while`.

---

## Table des matières

1. [Les variables en C](#1-les-variables-en-c)
2. [Les structures conditionnelles if/else](#2-les-structures-conditionnelles-ifelse)
3. [La boucle while](#3-la-boucle-while)
4. [Nombres aléatoires : rand et srand](#4-nombres-aléatoires--rand-et-srand)
5. [Explication des fichiers](#5-explication-des-fichiers)
6. [Points clés](#6-points-clés)
7. [Erreurs courantes](#7-erreurs-courantes)

---

## 1. Les variables en C

Une variable est un espace mémoire nommé qui stocke une valeur. En C, elle doit être **déclarée** avant d'être utilisée.

```c
int n;          /* entier */
char c = 'a';   /* caractère (code ASCII) */
float f = 3.14; /* nombre à virgule flottante */
```

Les types les plus courants :

| Type | Taille | Valeurs |
|------|--------|---------|
| `char` | 1 octet | 0 à 255 (ou -128 à 127) |
| `int` | 4 octets | -2 147 483 648 à 2 147 483 647 |
| `float` | 4 octets | nombres décimaux |

---

## 2. Les structures conditionnelles if/else

La structure `if/else if/else` permet d'exécuter du code selon une condition.

```c
if (n > 0)
{
    printf("%d is positive\n", n);
}
else if (n == 0)
{
    printf("%d is zero\n", n);
}
else
{
    printf("%d is negative\n", n);
}
```

**Règle :** La condition s'évalue à `vrai` (non-nul) ou `faux` (0). On peut combiner des conditions avec `&&` (ET) et `||` (OU).

Exemple — exclure des caractères :

```c
if (c != 'q' && c != 'e')
    putchar(c);    /* affiche c seulement si ce n'est pas 'q' ni 'e' */
```

---

## 3. La boucle while

La boucle `while` répète un bloc d'instructions tant qu'une condition est vraie.

```c
char c = 'a';

while (c <= 'z')
{
    putchar(c);
    c++;    /* incrémentation — sans cela, boucle infinie ! */
}
putchar('\n');
```

**Astuce :** Les caractères (`char`) ont des valeurs numériques ASCII. `'a'` vaut 97, `'z'` vaut 122. On peut donc les incrémenter comme des entiers.

Tableau ASCII utile :

| Caractère | Valeur ASCII |
|-----------|-------------|
| `'0'` | 48 |
| `'9'` | 57 |
| `'A'` | 65 |
| `'Z'` | 90 |
| `'a'` | 97 |
| `'z'` | 122 |

---

## 4. Nombres aléatoires : rand et srand

```c
#include <stdlib.h>
#include <time.h>

srand(time(0));          /* initialise le générateur avec l'heure actuelle */
n = rand() - RAND_MAX / 2;  /* nombre entre -RAND_MAX/2 et +RAND_MAX/2 */
```

- `srand()` initialise la **graine** (seed) du générateur. Utiliser `time(0)` garantit un résultat différent à chaque exécution.
- `rand()` retourne un entier pseudo-aléatoire entre 0 et `RAND_MAX`.

---

## 5. Explication des fichiers

### 0-positive_or_negative.c — Nombre positif, négatif ou zéro

Génère un nombre aléatoire et détermine son signe avec `if/else if/else`.

### 1-last_digit.c — Dernier chiffre d'un nombre

Utilise le **modulo** `%` pour obtenir le dernier chiffre : `last_digit = n % 10`.

### 2-print_alphabet.c — Alphabet minuscule

```c
char c = 'a';
while (c <= 'z')
{
    putchar(c);
    c++;
}
```

Parcourt les codes ASCII de `'a'` à `'z'` et affiche chaque lettre avec `putchar`.

### 3-print_alphabets.c — Minuscules puis majuscules

Deux boucles `while` successives : l'une pour `'a'` → `'z'`, l'autre pour `'A'` → `'Z'`.

### 4-print_alphabt.c — Alphabet sans 'e' et 'q'

Utilise un `if` à l'intérieur de la boucle pour sauter les lettres `'e'` et `'q'`.

### 5-print_numbers.c — Chiffres 0 à 9

```c
char n = '0';
while (n <= '9')
{
    putchar(n);
    n++;
}
```

Utilise les codes ASCII des chiffres (`'0'` à `'9'`).

### 6-print_numberz.c — Chiffres sans variable char

```c
int i = 0;
while (i <= 9)
{
    putchar(i + '0');  /* convertit l'entier en code ASCII du chiffre */
    i++;
}
```

`i + '0'` transforme un entier (0-9) en le caractère correspondant (`'0'`-`'9'`).

### 7-print_tebahpla.c — Alphabet à l'envers

```c
char c = 'z';
while (c >= 'a')
{
    putchar(c);
    c--;    /* décrémentation */
}
```

### 8-print_base16.c — Base hexadécimale (0-9, a-f)

Deux boucles : une pour `0` à `9` (numériques), une pour `'a'` à `'f'` (lettres).

### 9-print_comb.c — Combinaisons 0-9 avec séparateurs

```c
for (i = 0; i <= 9; i++)
{
    putchar(i + '0');
    if (i != 9)
    {
        putchar(',');
        putchar(' ');
    }
}
```

---

## 6. Points clés

- Les variables `char` sont des entiers de 1 octet — on peut faire de l'arithmétique dessus.
- `putchar(c)` affiche un seul caractère (plus rapide que `printf` pour les caractères).
- `'0' + i` convertit l'entier `i` en son caractère chiffre correspondant.
- Le modulo `%` donne le **reste** de la division entière : `7 % 10 = 7`, `17 % 10 = 7`.
- Toujours initialiser le générateur aléatoire avec `srand(time(0))` **avant** d'appeler `rand()`.
- `!=` et `&&` permettent d'exclure plusieurs cas dans un `if`.

---

## 7. Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Boucle infinie | Oubli de l'incrémentation (`c++` ou `i++`) | Vérifier que la variable de boucle évolue |
| Confondre `=` et `==` | `if (n = 0)` affecte 0, ne compare pas | Utiliser `==` pour les comparaisons |
| Oublier `putchar('\n')` | Pas de retour à la ligne en fin d'affichage | Ajouter `putchar('\n')` après la boucle |
| `rand()` sans `srand()` | Même séquence à chaque exécution | Appeler `srand(time(0))` au début de `main` |
| Afficher un entier avec `%c` | Affiche le caractère ASCII, pas le chiffre | Utiliser `%d` pour les entiers, `%c` pour les chars |
