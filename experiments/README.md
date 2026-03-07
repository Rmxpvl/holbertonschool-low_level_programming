# Expérimentations en C

Ce dossier contient de petits programmes C utilisés pour tester et expérimenter des concepts. Chaque programme est autonome et peut être compilé et exécuté indépendamment.

---

## Table des matières

1. [Calculatrice interactive](#1-calculatrice-interactive)
2. [Expériences suggérées](#2-expériences-suggérées)
3. [Comment compiler et exécuter](#3-comment-compiler-et-exécuter)

---

## 1. Calculatrice interactive

Une calculatrice simple en C qui illustre :
- La lecture d'entrée utilisateur avec `scanf`
- Les structures conditionnelles `if / else if / else`
- La gestion d'erreurs (division par zéro)
- Le cast de type pour la division flottante

**Fichier :** [`../simple-calculator/calculator.c`](../simple-calculator/calculator.c)

```bash
cd ../simple-calculator
gcc -Wall -Wextra -pedantic calculator.c -o calculator
./calculator
```

**Fonctionnalités :**
- Addition, soustraction, multiplication, division
- Gestion de la division par zéro
- Affichage entier ou décimal selon le résultat

---

## 2. Expériences suggérées

Voici des idées de petits programmes à écrire pour tester des concepts :

### Tester les types de données

```c
#include <stdio.h>

int main(void)
{
    char c = 255;
    unsigned char uc = 255;

    printf("char 255    : %d\n", c);     /* -1 (débordement) */
    printf("uchar 255   : %d\n", uc);    /* 255 (correct) */

    /* Débordement d'entier */
    int max = 2147483647;
    printf("max + 1     : %d\n", max + 1);  /* Négatif ! */

    return (0);
}
```

### Tester l'arithmétique des pointeurs

```c
#include <stdio.h>

int main(void)
{
    int tab[] = {10, 20, 30, 40, 50};
    int *p = tab;
    int i;

    printf("Adresses et valeurs :\n");
    for (i = 0; i < 5; i++)
        printf("tab[%d] = %d  |  adresse = %p\n", i, *(p + i), (void *)(p + i));

    /* Différence entre deux pointeurs */
    int *debut = &tab[0];
    int *fin   = &tab[4];
    printf("\nDifférence fin - debut = %ld\n", fin - debut);  /* 4 */

    return (0);
}
```

### Tester la récursion

```c
#include <stdio.h>

int factorielle(int n)
{
    if (n <= 1)
        return (1);
    return (n * factorielle(n - 1));
}

int main(void)
{
    int i;

    for (i = 0; i <= 10; i++)
        printf("%d! = %d\n", i, factorielle(i));
    return (0);
}
```

### Tester les chaînes de caractères

```c
#include <stdio.h>

int main(void)
{
    char msg[] = "Holberton";
    char *p = msg;
    int longueur = 0;

    /* Calculer la longueur sans strlen */
    while (*p != '\0')
    {
        longueur++;
        p++;
    }
    printf("Longueur de '%s' = %d\n", msg, longueur);

    /* Inverser la chaîne */
    int debut = 0;
    int fin = longueur - 1;
    char temp;

    while (debut < fin)
    {
        temp = msg[debut];
        msg[debut] = msg[fin];
        msg[fin] = temp;
        debut++;
        fin--;
    }
    printf("Inversée : '%s'\n", msg);

    return (0);
}
```

### Mesurer le temps d'exécution

```c
#include <stdio.h>
#include <time.h>

int main(void)
{
    clock_t debut = clock();
    volatile long long compteur = 0;
    long i;

    for (i = 0; i < 50000000L; i++)
        compteur++;

    clock_t fin = clock();
    double temps = (double)(fin - debut) / CLOCKS_PER_SEC;

    printf("Compteur  : %lld\n", compteur);
    printf("Temps CPU : %.6f secondes\n", temps);

    return (0);
}
```

---

## 3. Comment compiler et exécuter

```bash
# Compiler un fichier d'expérimentation
gcc -Wall -Wextra -pedantic -std=gnu89 mon_experience.c -o mon_experience

# Exécuter
./mon_experience

# Avec vérification mémoire
valgrind --leak-check=full ./mon_experience

# Avec débogage
gcc -g mon_experience.c -o mon_experience_debug
gdb ./mon_experience_debug
```

### Modèle de programme d'expérimentation

```c
#include <stdio.h>
#include <stdlib.h>

/**
 * main - Expérimentation : [décrire ce qu'on teste]
 * Return: 0 si succès
 */
int main(void)
{
    /* === SETUP === */

    /* === EXPÉRIENCE === */

    /* === RÉSULTATS === */
    printf("Résultat : ...\n");

    return (0);
}
```

---

## Fichiers de référence

- [`../simple-calculator/calculator.c`](../simple-calculator/calculator.c) – Calculatrice interactive
- [`../benchmarking/baseline_loop.c`](../benchmarking/baseline_loop.c) – Mesure de performance
- [`../benchmarking/instrumentation_lab.c`](../benchmarking/instrumentation_lab.c) – Instrumentation multi-phases
