# Erreurs Courantes en Programmation C

Ce dossier recense les erreurs fréquentes commises en C, avec l'explication du bug et la version corrigée.

---

## Table des matières

1. [Oubli du caractère nul dans les chaînes](#1-oubli-du-caractère-nul-dans-les-chaînes)
2. [Affectation au lieu de comparaison](#2-affectation-au-lieu-de-comparaison)
3. [Erreur off-by-one dans les boucles](#3-erreur-off-by-one-dans-les-boucles)
4. [Déréférencement d'un pointeur NULL](#4-déréférencement-dun-pointeur-null)
5. [Fuite mémoire avec malloc](#5-fuite-mémoire-avec-malloc)
6. [Variable non initialisée](#6-variable-non-initialisée)
7. [Division entière inattendue](#7-division-entière-inattendue)
8. [Boucle infinie](#8-boucle-infinie)
9. [Retourner une variable locale par pointeur](#9-retourner-une-variable-locale-par-pointeur)
10. [scanf sans l'adresse (&)](#10-scanf-sans-ladresse-)

---

## 1. Oubli du caractère nul dans les chaînes

### Code incorrect

```c
char chaine[5];
chaine[0] = 'H';
chaine[1] = 'i';
/* chaine[2] manque '\0' → comportement indéfini lors de puts/printf */
puts(chaine);
```

### Raison du bug

`puts` et `printf %s` parcourent la mémoire jusqu'à trouver `'\0'`. Sans lui, ils lisent au-delà du tableau (comportement indéfini, données parasites affichées, crash possible).

### Version corrigée

```c
char chaine[6];
chaine[0] = 'H';
chaine[1] = 'e';
chaine[2] = 'l';
chaine[3] = 'l';
chaine[4] = 'o';
chaine[5] = '\0';   /* Terminaison obligatoire */
puts(chaine);
/* Ou simplement : char chaine[] = "Hello"; */
```

---

## 2. Affectation au lieu de comparaison

### Code incorrect

```c
int x = 5;

if (x = 0)             /* Affecte 0 à x, puis évalue 0 → toujours faux */
    printf("zéro\n");
else
    printf("non zéro\n");  /* Toujours exécuté, et x vaut maintenant 0 */
```

### Raison du bug

`=` est l'opérateur d'**affectation** ; `==` est l'opérateur de **comparaison**. Le compilateur accepte `=` dans une condition (il vaut la valeur affectée).

### Version corrigée

```c
int x = 5;

if (x == 0)            /* Comparaison correcte */
    printf("zéro\n");
else
    printf("non zéro\n");
```

> **Astuce :** compiler avec `-Wall` affiche un avertissement `warning: suggest parentheses around assignment used as truth value`.

---

## 3. Erreur off-by-one dans les boucles

### Code incorrect

```c
int tableau[5] = {10, 20, 30, 40, 50};
int i;

for (i = 0; i <= 5; i++)   /* i = 5 → accès hors tableau */
    printf("%d\n", tableau[i]);
```

### Raison du bug

Les indices d'un tableau de taille 5 vont de **0 à 4**. Avec `i <= 5`, la boucle s'exécute pour `i = 5`, ce qui accède à `tableau[5]` (hors limites → comportement indéfini).

### Version corrigée

```c
int tableau[5] = {10, 20, 30, 40, 50};
int i;

for (i = 0; i < 5; i++)    /* i = 0, 1, 2, 3, 4 → correct */
    printf("%d\n", tableau[i]);
```

---

## 4. Déréférencement d'un pointeur NULL

### Code incorrect

```c
int *p = NULL;

*p = 42;    /* Segmentation fault – p ne pointe vers rien */
```

### Raison du bug

`NULL` vaut `0` (adresse invalide). Tenter de lire ou écrire à l'adresse 0 cause un **segfault** immédiat, car le système d'exploitation protège cette zone mémoire.

### Version corrigée

```c
#include <stdlib.h>

int *p = malloc(sizeof(int));

if (p == NULL)          /* TOUJOURS vérifier avant d'utiliser */
{
    fprintf(stderr, "Erreur d'allocation\n");
    return (1);
}

*p = 42;
printf("%d\n", *p);
free(p);
p = NULL;
```

---

## 5. Fuite mémoire avec malloc

### Code incorrect

```c
void ma_fonction(void)
{
    int *tableau = malloc(sizeof(int) * 100);

    tableau[0] = 42;
    /* Fin de la fonction : tableau est perdu, mais la mémoire n'est pas libérée */
}
```

### Raison du bug

Quand la variable `tableau` sort de portée, l'adresse de la mémoire allouée est perdue. Cette mémoire ne peut plus être libérée → **fuite mémoire**. Sur un long programme, cela peut épuiser la RAM.

### Version corrigée

```c
void ma_fonction(void)
{
    int *tableau = malloc(sizeof(int) * 100);

    if (tableau == NULL)
        return;

    tableau[0] = 42;
    /* ... utilisation ... */

    free(tableau);      /* Libération obligatoire */
    tableau = NULL;
}
```

---

## 6. Variable non initialisée

### Code incorrect

```c
int somme;          /* Valeur indéterminée (ce qui était en mémoire) */
int i;

for (i = 0; i < 5; i++)
    somme += i;     /* On accumule à partir d'une valeur aléatoire */

printf("Somme : %d\n", somme);   /* Résultat imprévisible */
```

### Raison du bug

En C, les variables locales ne sont **pas initialisées automatiquement**. Leur valeur initiale est ce qui se trouvait à cet emplacement mémoire (garbage).

### Version corrigée

```c
int somme = 0;      /* Initialisation explicite */
int i;

for (i = 0; i < 5; i++)
    somme += i;

printf("Somme : %d\n", somme);   /* 10 – correct */
```

---

## 7. Division entière inattendue

### Code incorrect

```c
int a = 7;
int b = 2;
float resultat = a / b;

printf("%.2f\n", resultat);   /* Affiche 3.00 au lieu de 3.50 */
```

### Raison du bug

`a / b` est une **division entière** (les deux opérandes sont `int`). Le résultat est `3` (troncature), puis converti en `float` → `3.0`.

### Version corrigée

```c
int a = 7;
int b = 2;
float resultat = (float)a / (float)b;   /* Cast avant la division */

printf("%.2f\n", resultat);   /* 3.50 – correct */
```

---

## 8. Boucle infinie

### Code incorrect

```c
int i = 0;

while (i < 10)
{
    printf("%d\n", i);
    /* Oubli de i++ → i reste à 0, condition toujours vraie */
}
```

### Raison du bug

Sans incrémenter `i`, la condition `i < 10` reste toujours vraie → boucle infinie. Le programme ne se termine jamais et bloque.

### Version corrigée

```c
int i = 0;

while (i < 10)
{
    printf("%d\n", i);
    i++;    /* Incrémentation indispensable */
}
```

---

## 9. Retourner une variable locale par pointeur

### Code incorrect

```c
int *creer_valeur(void)
{
    int valeur = 42;     /* Variable locale – détruite à la fin de la fonction */
    return (&valeur);    /* Retourne l'adresse d'une variable qui n'existe plus */
}

int main(void)
{
    int *p = creer_valeur();
    printf("%d\n", *p);  /* Comportement indéfini – la mémoire a été réutilisée */
    return (0);
}
```

### Raison du bug

Les variables locales sont allouées sur la **pile (stack)** et sont détruites à la fin de la fonction. Retourner leur adresse crée un **dangling pointer**.

### Version corrigée

```c
#include <stdlib.h>

int *creer_valeur(void)
{
    int *valeur = malloc(sizeof(int));   /* Alloué sur le tas – persiste */

    if (valeur == NULL)
        return (NULL);
    *valeur = 42;
    return (valeur);
}

int main(void)
{
    int *p = creer_valeur();

    if (p != NULL)
    {
        printf("%d\n", *p);   /* 42 – correct */
        free(p);
    }
    return (0);
}
```

---

## 10. scanf sans l'adresse (&)

### Code incorrect

```c
int age;

printf("Entrez votre âge : ");
scanf("%d", age);    /* Manque & → passe la valeur de age, pas son adresse */
```

### Raison du bug

`scanf` a besoin de l'**adresse** de la variable pour y écrire. Sans `&`, on passe la valeur non initialisée de `age` comme adresse → comportement indéfini, crash probable.

### Version corrigée

```c
int age;

printf("Entrez votre âge : ");
scanf("%d", &age);   /* & donne l'adresse de age – correct */
printf("Vous avez %d ans\n", age);
```
