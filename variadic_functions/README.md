# Fonctions Variadiques

Ce dossier introduit les **fonctions variadiques** en C : comment écrire une fonction qui peut recevoir un nombre variable d'arguments, comme `printf`, `scanf`, `sum()`, etc.

---

## Table des matières

1. [Fonctions variadiques : concept](#1-fonctions-variadiques--concept)
2. [La library stdarg.h](#2-la-library-stdarguh)
3. [Les macros variadiques](#3-les-macros-variadiques)
4. [Pattern des fonctions variadiques](#4-pattern-des-fonctions-variadiques)
5. [Explication des fichiers](#5-explication-des-fichiers)
6. [Points clés](#6-points-clés)
7. [Erreurs courantes](#7-erreurs-courantes)

---

## 1. Fonctions variadiques : concept

Une **fonction variadique** est une fonction qui accepte un **nombre variable d'arguments**. L'exemple classique est `printf`:

```c
printf("Hello");           /* 1 argument */
printf("Hello %s", "John"); /* 2 arguments */
printf("%d %d %d", 1, 2, 3); /* 4 arguments */
```

Tous les appels fonctionnent parce que `printf` est variadique.

### Déclaration d'une fonction variadique

Pour créer une fonction variadique, utiliser les trois points `...` à la fin de la liste de paramètres :

```c
void print_numbers(const char *separator, const unsigned int n, ...)
{
    /* n indique le nombre d'arguments supplémentaires */
    /* ... signifie : les arguments supplémentaires suivent */
}
```

**Règle importante :** Au moins un paramètre fixe doit être déclaré avant `...`.

---

## 2. La library `<stdarg.h>`

Pour accéder aux arguments variables, utiliser la library `<stdarg.h>` qui fournit :

- `va_list` : type pour stocker les arguments
- `va_start()` : initialiser la liste
- `va_arg()` : lire le prochain argument
- `va_end()` : nettoyer

---

## 3. Les macros variadiques

### va_list

La variable qui stocke l'état de lecture des arguments :

```c
va_list args;  /* args va garder la position dans la liste d'arguments */
```

### va_start(ap, last_fixed_param)

**Initialiser** la liste d'arguments. Le deuxième argument est le **dernier paramètre fixe**.

```c
int sum_them_all(const unsigned int n, ...)
{
    va_list args;
    
    va_start(args, n);  /* n est le dernier paramètre fixe */
    /* Maintenant on peut utiliser args */
    va_end(args);
    
    return (0);
}
```

### va_arg(ap, type)

**Lire** le prochain argument de la liste. Il faut spécifier le **type** attendu.

```c
int sum_them_all(const unsigned int n, ...)
{
    va_list args;
    unsigned int i;
    int sum = 0;

    if (n == 0)
        return (0);

    va_start(args, n);
    for (i = 0; i < n; i++)
        sum += va_arg(args, int);  /* Lire le prochain int */
    va_end(args);

    return (sum);
}
```

### va_end(ap)

**Nettoyer** la liste d'arguments. C'est important pour éviter des comportements imprévisibles.

```c
va_end(args);  /* Toujours appeler après va_start */
```

---

## 4. Pattern des fonctions variadiques

### Pattern 1 : Somme d'arguments variables

```c
/**
 * sum_them_all - returns the sum of all its parameters
 * @n: number of arguments passed after n
 *
 * Return: sum of all parameters, or 0 if n is 0
 */
int sum_them_all(const unsigned int n, ...)
{
    va_list args;
    unsigned int i;
    int sum;

    if (n == 0)
        return (0);

    va_start(args, n);
    sum = 0;
    for (i = 0; i < n; i++)
        sum += va_arg(args, int);
    va_end(args);

    return (sum);
}
```

**Utilisation :**

```c
printf("%d\n", sum_them_all(3, 10, 20, 30));  /* Affiche: 60 */
printf("%d\n", sum_them_all(2, 5, 10));        /* Affiche: 15 */
printf("%d\n", sum_them_all(0));               /* Affiche: 0 */
```

### Pattern 2 : Afficher des nombres avec séparateur

```c
/**
 * print_numbers - prints numbers followed by a new line
 * @separator: string to print between numbers
 * @n: number of integers passed to the function
 *
 * Return: nothing
 */
void print_numbers(const char *separator, const unsigned int n, ...)
{
    va_list args;
    unsigned int i;

    va_start(args, n);
    for (i = 0; i < n; i++)
    {
        printf("%d", va_arg(args, int));
        if (separator != NULL && i < (n - 1))
            printf("%s", separator);
    }
    va_end(args);
    printf("\n");
}
```

**Utilisation :**

```c
print_numbers(", ", 3, 1, 2, 3);      /* Affiche: 1, 2, 3 */
print_numbers(" - ", 2, 10, 20);      /* Affiche: 10 - 20 */
print_numbers(NULL, 4, 5, 10, 15, 20); /* Affiche: 510152030 */
```

### Pattern 3 : Afficher des chaînes avec gestion des NULL

```c
/**
 * print_strings - prints strings followed by a new line
 * @separator: string to print between strings
 * @n: number of strings passed to the function
 *
 * Return: nothing
 */
void print_strings(const char *separator, const unsigned int n, ...)
{
    va_list args;
    unsigned int i;
    char *str;

    va_start(args, n);
    for (i = 0; i < n; i++)
    {
        str = va_arg(args, char *);
        if (str == NULL)
            printf("(nil)");
        else
            printf("%s", str);
        if (separator != NULL && i < (n - 1))
            printf("%s", separator);
    }
    va_end(args);
    printf("\n");
}
```

**Utilisation :**

```c
print_strings(", ", 3, "John", "Jane", "Joe");    /* John, Jane, Joe */
print_strings(" | ", 2, "Hello", NULL);            /* Hello | (nil) */
print_strings("-", 4, "a", "b", NULL, "c");       /* a-b-(nil)-c */
```

---

## 5. Explication des fichiers

| Fichier | Description |
|---|---|
| `0-sum_them_all.c` | Somme tous les entiers passés en argument (argument count fourni) |
| `1-print_numbers.c` | Affiche les nombres avec un séparateur entre chacun |
| `2-print_strings.c` | Affiche les chaînes avec un séparateur (gère les NULL) |
| `3-print_all.c` | Affiche différents types d'arguments selon un format donné |
| `variadic_functions.h` | Fichier d'en-tête avec les prototypes |

---

## 6. Points clés

- Une fonction variadique doit avoir **au moins un paramètre fixe** avant `...`.
- Utiliser `va_start(args, last_fixed_param)` avec le **dernier paramètre fixe**.
- Toujours **connaître le type** d'argument lors de l'appel à `va_arg()`.
- Toujours appeler `va_end()` après `va_start()`.
- Le nombre d'arguments variables doit être **communiqué explicitement** à la fonction (pas de détection automatique).
- Les fonctions variadiques sont **dangereuses** si le nombre ou le type d'arguments ne correspond pas.

---

## 7. Erreurs courantes

- **Oublier d'appeler `va_end()`** → Comportement imprévisible.
- **Ne pas spécifier le type dans `va_arg()`** → Résultat incorrect ou crash.
- **Confondre le nombre d'arguments** → Lire plus d'arguments que fourni → comportement indéfini.
- **Pas de paramètre fixe avant `...`** → Code invalide.
- **Mélanger les types** → Appeler `va_arg(args, int)` pour une chaîne → garbage.
- **Oublier qu'il n'y a pas de "type checking"** → C ne vérifie pas les types, c'est à toi de les gérer.
