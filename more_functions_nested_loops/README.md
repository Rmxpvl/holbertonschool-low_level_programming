# Plus de Fonctions et Boucles Imbriquées

Ce dossier approfondit les fonctions et boucles imbriquées avec des exercices plus complexes : classification de caractères, dessin de formes géométriques, et l'algorithme FizzBuzz.

---

## Table des matières

1. [Classification de caractères](#1-classification-de-caractères)
2. [Dessin de formes avec des boucles imbriquées](#2-dessin-de-formes-avec-des-boucles-imbriquées)
3. [L'algorithme FizzBuzz](#3-lalgorithme-fizzbuzz)
4. [Explication des fichiers](#4-explication-des-fichiers)
5. [Points clés](#5-points-clés)
6. [Erreurs courantes](#6-erreurs-courantes)

---

## 1. Classification de caractères

Les fonctions de classification vérifient si un caractère appartient à une catégorie. On utilise les valeurs ASCII pour les comparaisons.

### Vérifier une majuscule

```c
int _isupper(int c)
{
    if (c >= 'A' && c <= 'Z')
        return (1);
    return (0);
}
```

`'A'` vaut 65 et `'Z'` vaut 90 en ASCII. Tout caractère entre ces valeurs est une majuscule.

### Vérifier un chiffre

```c
int _isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}
```

`'0'` vaut 48 et `'9'` vaut 57 en ASCII.

---

## 2. Dessin de formes avec des boucles imbriquées

Les boucles imbriquées permettent de dessiner des formes dans le terminal. La boucle **externe** gère les lignes, la boucle **interne** gère les colonnes.

### Ligne droite (print_line)

```c
void print_line(int n)
{
    int i;
    if (n <= 0) { _putchar('\n'); return; }
    for (i = 0; i < n; i++)
        _putchar('_');
    _putchar('\n');
}
```

### Diagonale (print_diagonal)

```c
void print_diagonal(int n)
{
    int i, j;
    if (n <= 0) { _putchar('\n'); return; }
    i = 0;
    while (i < n)
    {
        for (j = 0; j < i; j++)    /* espaces avant '\' */
            _putchar(' ');
        _putchar('\\');
        _putchar('\n');
        i++;
    }
}
```

Chaque ligne a `i` espaces suivis d'un `\`. La ligne 0 a 0 espace, la ligne 1 a 1 espace, etc.

### Carré (print_square)

```c
void print_square(int size)
{
    int i, j;
    if (size <= 0) { _putchar('\n'); return; }
    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            _putchar('#');
            j++;
        }
        _putchar('\n');
        i++;
    }
}
```

`size` lignes de `size` caractères `#`.

### Triangle aligné à droite (print_triangle)

```c
void print_triangle(int size)
{
    int i, j;
    if (size <= 0) { _putchar('\n'); return; }
    for (i = 1; i <= size; i++)
    {
        for (j = 1; j <= size - i; j++)   /* espaces */
            _putchar(' ');
        for (j = 1; j <= i; j++)          /* # */
            _putchar('#');
        _putchar('\n');
    }
}
```

La ligne `i` a `(size - i)` espaces puis `i` symboles `#`.

---

## 3. L'algorithme FizzBuzz

FizzBuzz est un exercice classique d'algorithmique :

- Nombre multiple de 3 → afficher `Fizz`
- Nombre multiple de 5 → afficher `Buzz`
- Multiple de 3 ET 5 → afficher `FizzBuzz`
- Sinon → afficher le nombre

**Ordre des conditions important :** tester `% 15` en premier (multiple des deux), sinon les cas `%3` et `%5` prendraient le dessus.

```c
for (i = 1; i <= 100; i++)
{
    if (i % 15 == 0)       printf("FizzBuzz");
    else if (i % 3 == 0)   printf("Fizz");
    else if (i % 5 == 0)   printf("Buzz");
    else                   printf("%d", i);

    if (i < 100)
        printf(" ");
}
printf("\n");
```

---

## 4. Explication des fichiers

### 0-isupper.c — Vérifier majuscule

Retourne 1 si `c` est entre `'A'` et `'Z'`, 0 sinon.

### 1-isdigit.c — Vérifier chiffre

Retourne 1 si `c` est entre `'0'` et `'9'`, 0 sinon.

### 2-mul.c — Multiplication

```c
int mul(int a, int b)
{
    return (a * b);
}
```

### 3-print_numbers.c — Chiffres 0 à 9

Parcourt les caractères `'0'` à `'9'` et les affiche avec `_putchar`.

### 4-print_most_numbers.c — 0 à 9 sauf 2 et 4

```c
void print_most_numbers(void)
{
    char n = '0';
    while (n <= '9')
    {
        if (n != '2' && n != '4')
            _putchar(n);
        n++;
    }
    _putchar('\n');
}
```

### 5-more_numbers.c — 0 à 14, dix fois

Double boucle : 10 répétitions × affichage de 0 à 14. Gère les nombres à deux chiffres (>= 10) avec `_putchar('1')` et `_putchar('0' + j % 10)`.

### 6-print_line.c — Ligne de `_`

Affiche `n` underscores. Si `n <= 0`, affiche juste un `\n`.

### 7-print_diagonal.c — Diagonale de `\`

Ligne `i` : `i` espaces + `\`. Si `n <= 0`, affiche juste un `\n`.

### 8-print_square.c — Carré de `#`

`size × size` caractères `#`. Si `size <= 0`, affiche juste un `\n`.

### 9-fizz_buzz.c — FizzBuzz 1 à 100

Conditions multiples avec l'opérateur modulo `%`.

### 10-print_triangle.c — Triangle aligné à droite

La ligne `i` contient `(size - i)` espaces puis `i` caractères `#`.

---

## 5. Points clés

- Tester le cas `size <= 0` au début de chaque fonction de dessin pour éviter des boucles indésirables.
- Dans FizzBuzz, tester `% 15` avant `% 3` et `% 5` — l'ordre des conditions est **crucial**.
- Pour dessiner des formes, penser en termes de "combien d'espaces" et "combien de symboles" par ligne.
- `\\` dans une chaîne de caractères ou `_putchar('\\')` affiche un seul `\`.
- La fonction de dessin ne doit **jamais** afficher de lignes pour `n <= 0` (sauf le `\n` obligatoire).
- `_putchar(n)` affiche le caractère, `_putchar('0' + n)` affiche le chiffre correspondant à l'entier `n`.

---

## 6. Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Ne pas vérifier `n <= 0` | La boucle `while (i < n)` ne s'exécute pas mais `_putchar('\n')` est quand même requis | Ajouter `if (n <= 0) { _putchar('\n'); return; }` |
| Ordre FizzBuzz inversé | Tester `%3` avant `%15` → les multiples de 15 affichent `Fizz` | Toujours tester `%15` en premier |
| Mauvais nombre d'espaces dans le triangle | La ligne calcule `size - i` mais `i` commence à 0 ou 1 | Aligner l'indexation avec la logique de dessin |
| Afficher `\` au lieu de `\\` | `\` seul est un caractère d'échappement → erreur de compilation | Écrire `'\\'` pour le caractère backslash |
| Plus de lignes qu'attendu | Condition `i <= size` au lieu de `i < size` | Vérifier la condition de sortie de boucle |
