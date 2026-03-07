# Aide-mémoire C – Référence Rapide

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 fichier.c -o prog
./prog
```

---

## Types de base

| Type       | Format printf | Taille  | Plage                |
|------------|---------------|---------|----------------------|
| `char`     | `%c` / `%d`   | 1 octet | -128 à 127           |
| `int`      | `%d`          | 4 octets| ±2 milliards         |
| `long`     | `%ld`         | 8 octets| très grand           |
| `float`    | `%f`          | 4 octets| ~6 décimales         |
| `double`   | `%lf`         | 8 octets| ~15 décimales        |
| `unsigned` | `%u`          | 4 octets| 0 à 4 milliards      |
| pointeur   | `%p`          | 8 octets| adresse mémoire      |

---

## Opérateurs

```c
/* Arithmétique */
+ - * / %

/* Comparaison */
== != < > <= >=

/* Logique */
&& (ET)   || (OU)   ! (NON)

/* Bit à bit */
&  (ET)   |  (OU)   ^  (XOR)   ~  (NON)   <<  >>

/* Incrémentation */
i++   i--   ++i   --i

/* Affectation combinée */
+= -= *= /= %= &= |= ^= <<= >>=
```

---

## Structures de contrôle

```c
/* if / else */
if (condition)
    instruction;
else if (autre_condition)
    instruction;
else
    instruction;

/* while */
while (condition)
    instruction;

/* for */
for (init; condition; increment)
    instruction;

/* do while */
do {
    instruction;
} while (condition);

/* switch */
switch (valeur)
{
    case 1: instruction; break;
    case 2: instruction; break;
    default: instruction;
}
```

---

## Fonctions

```c
/* Prototype (dans .h) */
type_retour nom_fonction(type param1, type param2);

/* Définition */
int addition(int a, int b)
{
    return (a + b);
}

/* Pas de valeur de retour */
void afficher(char *msg)
{
    printf("%s\n", msg);
}
```

---

## Tableaux

```c
/* Déclaration */
int tab[5];
int tab[5] = {1, 2, 3, 4, 5};
char chaine[] = "Bonjour";    /* '\0' ajouté automatiquement */

/* Accès */
tab[0]   tab[4]

/* Taille */
int taille = sizeof(tab) / sizeof(tab[0]);
```

---

## Pointeurs

```c
int n = 42;
int *p = &n;       /* p = adresse de n */
*p = 98;           /* modifie n via p */

/* Pointeur et tableau */
int tab[3] = {1, 2, 3};
int *ptr = tab;    /* ptr pointe vers tab[0] */
*(ptr + 1)         /* équivaut à tab[1] */

/* Pointeur NULL */
int *p = NULL;     /* Toujours initialiser */
if (p != NULL) *p = 5;  /* Vérifier avant utilisation */
```

---

## Chaînes de caractères

```c
char s[] = "Bonjour";

/* Parcourir */
int i = 0;
while (s[i] != '\0') i++;
/* ou */
char *p = s;
while (*p != '\0') p++;

/* Fonctions standard (#include <string.h>) */
strlen(s)           /* longueur */
strcpy(dest, src)   /* copie */
strcat(dest, src)   /* concaténation */
strcmp(s1, s2)      /* comparaison (0 si égal) */
```

---

## Malloc / Free

```c
#include <stdlib.h>

/* Allouer */
int *p = malloc(sizeof(int) * n);
if (p == NULL) return (1);   /* Vérifier toujours */

/* Utiliser */
p[0] = 42;

/* Libérer */
free(p);
p = NULL;   /* Évite le dangling pointer */
```

---

## Entrée / Sortie

```c
/* Affichage */
printf("Entier : %d\n", n);
printf("Float  : %.2f\n", f);
printf("Chaîne : %s\n", s);
printf("Char   : %c\n", c);
printf("Adresse: %p\n", (void *)ptr);

/* Lecture */
scanf("%d", &n);          /* lire un entier */
scanf("%f", &f);          /* lire un float */
scanf("%s", chaine);      /* lire une chaîne (sans &) */

/* Caractère */
putchar('A');             /* affiche un caractère */
int c = getchar();        /* lit un caractère */
```

---

## Header (.h)

```c
#ifndef MON_HEADER_H
#define MON_HEADER_H

/* Prototypes */
int ma_fonction(int a, int b);
void autre_fonction(char *s);

#endif /* MON_HEADER_H */
```

---

## Codes de retour et erreurs

```c
return (0);     /* Succès */
return (1);     /* Erreur générale */

/* Écrire sur stderr */
fprintf(stderr, "Erreur : %s\n", message);
```
