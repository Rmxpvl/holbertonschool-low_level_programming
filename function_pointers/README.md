# Pointeurs de Fonction

Ce dossier introduit les **pointeurs de fonction** en C : comment passer une fonction comme argument à une autre fonction (callback), ce qui permet une grande flexibilité et réutilisabilité du code.

---

## Table des matières

1. [Qu'est-ce qu'un pointeur de fonction ?](#1-quest-ce-quun-pointeur-de-fonction-)
2. [Déclarer un pointeur de fonction](#2-déclarer-un-pointeur-de-fonction)
3. [Appeler une fonction via un pointeur](#3-appeler-une-fonction-via-un-pointeur)
4. [Passer une fonction comme argument](#4-passer-une-fonction-comme-argument)
5. [Cas d'usage pratiques](#5-cas-dusage-pratiques)
6. [Explication des fichiers](#6-explication-des-fichiers)
7. [Points clés](#7-points-clés)
8. [Erreurs courantes](#8-erreurs-courantes)

---

## 1. Qu'est-ce qu'un pointeur de fonction ?

Un **pointeur de fonction** est une variable qui stocke l'adresse mémoire d'une fonction. Au lieu d'appeler une fonction directement par son nom, on peut l'appeler via ce pointeur, ce qui donne une grande flexibilité.

### Sans pointeur de fonction (rigide)

```c
void say_hello(void)
{
    printf("Hello\n");
}

int main(void)
{
    say_hello();  /* On appelle say_hello directement */
    return (0);
}
```

Le programme est **rigide** : il appelle toujours la même fonction.

### Avec pointeur de fonction (flexible)

```c
void say_hello(void)
{
    printf("Hello\n");
}

void say_goodbye(void)
{
    printf("Goodbye\n");
}

int main(void)
{
    void (*f)(void);  /* Pointeur vers une fonction qui ne prend rien et retourne void */
    
    f = say_hello;
    f();              /* Appelle say_hello via le pointeur */
    
    f = say_goodbye;
    f();              /* Appelle say_goodbye via le pointeur */
    
    return (0);
}
```

Sortie :
```
Hello
Goodbye
```

Le même code peut maintenant appeler **différentes fonctions**.

---

## 2. Déclarer un pointeur de fonction

### Syntaxe générale

```c
return_type (*pointer_name)(parameter_types);
```

### Exemples

```c
/* Pointeur vers une fonction qui prend un char* et retourne void */
void (*f)(char *);

/* Pointeur vers une fonction qui prend deux ints et retourne un int */
int (*cmp)(int, int);

/* Pointeur vers une fonction qui prend un int et retourne un int */
int (*compare)(int);
```

### Utilisation

```c
void print_name(char *name)
{
    printf("%s\n", name);
}

int main(void)
{
    void (*f)(char *);  /* Déclarer le pointeur */
    
    f = print_name;     /* Lui assigner l'adresse d'une fonction */
    f("Alice");         /* L'appeler via le pointeur */
    
    return (0);
}
```

Sortie : `Alice`

---

## 3. Appeler une fonction via un pointeur

Une fois qu'un pointeur de fonction a été assigné, on peut l'appeler de deux façons :

### Forme explicite

```c
(*f)(argument);  /* Déréférencer puis appeler */
```

### Forme implicite (plus courante)

```c
f(argument);  /* C traite automatiquement f comme un pointeur */
```

Les deux sont équivalentes. La forme implicite est plus lisible.

---

## 4. Passer une fonction comme argument

L'avantage principal des pointeurs de fonction est de pouvoir **passer une fonction comme argument** à une autre fonction. Cela crée des **callbacks** très flexibles.

### Exemple 1 : print_name

```c
/**
 * print_name - prints a name using a function pointer
 * @name: name string to print
 * @f: pointer to function used to print the name
 *
 * Return: nothing
 */
void print_name(char *name, void (*f)(char *))
{
    if (name != NULL && f != NULL)
        f(name);
}
```

**Utilisation :**

```c
void print_upper(char *s)
{
    while (*s)
        printf("%c", toupper(*s++));
    printf("\n");
}

void print_lower(char *s)
{
    while (*s)
        printf("%c", tolower(*s++));
    printf("\n");
}

int main(void)
{
    print_name("Alice", print_upper);   /* Affiche: ALICE */
    print_name("Alice", print_lower);   /* Affiche: alice */
    return (0);
}
```

### Exemple 2 : array_iterator (appliquer une fonction à chaque élément)

```c
/**
 * array_iterator - execute une fonction sur chaque element d'un tableau
 * @array: tableau d'entiers a parcourir
 * @size: nombre d'elements dans le tableau
 * @action: fonction a appliquer sur chaque valeur
 */
void array_iterator(int *array, size_t size, void (*action)(int))
{
    size_t i;

    if (array == NULL || action == NULL)
        return;

    for (i = 0; i < size; i++)
        action(array[i]);  /* Appeller la fonction pour chaque élément */
}
```

**Utilisation :**

```c
void print_int(int x)
{
    printf("%d\n", x);
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    array_iterator(arr, 5, print_int);  /* Affiche chaque élément */
    return (0);
}
```

Sortie :
```
1
2
3
4
5
```

### Exemple 3 : int_index (chercher un élément avec une condition)

```c
/**
 * int_index - cherche un entier avec une fonction de comparaison
 * @array: tableau d'entiers a parcourir
 * @size: nombre d'elements du tableau
 * @cmp: fonction qui compare une valeur et retourne 0 ou non
 *
 * Return: index du premier element valide, ou -1 en cas d'echec
 */
int int_index(int *array, int size, int (*cmp)(int))
{
    int i;

    if (array == NULL || cmp == NULL || size <= 0)
        return (-1);

    for (i = 0; i < size; i++)
    {
        if (cmp(array[i]) != 0)  /* Si la fonction retourne non-zéro */
            return (i);           /* Retourner l'index */
    }

    return (-1);
}
```

**Utilisation :**

```c
int is_negative(int x)
{
    return (x < 0);  /* Retourne 1 (true) si x < 0 */
}

int main(void)
{
    int arr[] = {1, 2, -3, 4};
    int idx = int_index(arr, 4, is_negative);
    printf("Index: %d\n", idx);  /* Affiche: Index: 2 */
    return (0);
}
```

---

## 5. Cas d'usage pratiques

### 1. Fonctions de tri (qsort)

La fonction `qsort` de la stdlib prend un pointeur de fonction pour définir la comparaison :

```c
#include <stdlib.h>

int compare_ints(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main(void)
{
    int arr[] = {3, 1, 4, 1, 5};
    qsort(arr, 5, sizeof(int), compare_ints);  /* Trier avec la fonction compare_ints */
    return (0);
}
```

### 2. Listeners et Event Handlers

```c
void on_button_click(void (*callback)(void))
{
    /* ... quand l'utilisateur clique ... */
    callback();  /* Appeler la fonction fournie */
}
```

---

## 6. Explication des fichiers

| Fichier | Description |
|---|---|
| `0-print_name.c` | Affiche un nom en utilisant une fonction pointeur pour choisir comment afficher |
| `1-array_iterator.c` | Applique une fonction sur chaque élément d'un tableau |
| `2-int_index.c` | Cherche le premier élément du tableau qui satisfait une condition |
| `3-calc.h` | Définit les opérateurs mathématiques et les fonctions de calcul |
| `3-main.c` | Calculatrice interactif utilisant les pointeurs de fonction |
| `3-op_functions.c` | Implémentation des opérateurs (+, -, *, /, %) |
| `3-get_op_func.c` | Sélectionne la fonction d'opération selon l'opérateur fourni |
| `function_pointers.h` | Fichier d'en-tête avec tous les prototypes |

---

## 7. Points clés

- Un pointeur de fonction stocke l'adresse d'une fonction.
- La syntaxe `void (*f)(char *)` signifie : `f` est un pointeur vers une fonction qui prend un `char *` et retourne `void`.
- Passer une fonction comme argument rend le code très flexible.
- Toujours **vérifier que le pointeur n'est pas NULL** avant de l'appeler.
- Les pointeurs de fonction sont essentiels pour les callbacks, les comparateurs (qsort), et les event handlers.

---

## 8. Erreurs courantes

- **Confondre la déclaration et l'assignation** → `f = func` (pas `f = &func`), bien que les deux fonctionnent.
- **Oublier de vérifier NULL** → Appeler un pointeur NULL → crash.
- **Mauvaise syntaxe** → `(*f)(arg)` vs `f(arg)` - Les deux fonctionnent mais la seconde est plus lisible.
- **Types incompatibles** → Assigner une fonction au mauvais pointeur → comportement indéfini.
- **Oublier que les noms de fonction sont déjà des adresses** → `func` est l'adresse, `&func` aussi (en C, les deux marchent).
