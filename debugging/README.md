# Débogage (Debugging)

Ce dossier explique les techniques de débogage en C : identifier les erreurs, les corriger méthodiquement et utiliser les outils disponibles.

---

## Table des matières

1. [Types d'erreurs en C](#1-types-derreurs-en-c)
2. [Débogage avec printf](#2-débogage-avec-printf)
3. [Erreurs d'exécution courantes](#3-erreurs-dexécution-courantes)
4. [Utiliser GDB](#4-utiliser-gdb)
5. [Utiliser Valgrind](#5-utiliser-valgrind)
6. [Méthode de débogage](#6-méthode-de-débogage)
7. [Points clés](#points-clés)
8. [Erreurs courantes](#erreurs-courantes)

---

## 1. Types d'erreurs en C

| Type d'erreur       | Quand détectée  | Exemple                              |
|---------------------|-----------------|--------------------------------------|
| **Erreur de syntaxe** | Compilation    | Oubli de `;` ou `}`                  |
| **Erreur de liaison**  | Compilation    | Fonction utilisée mais non définie   |
| **Erreur d'exécution** | Runtime        | Division par zéro, segfault          |
| **Erreur logique**    | Résultat faux  | Mauvais algorithme, off-by-one       |

---

## 2. Débogage avec printf

La technique la plus simple : afficher les valeurs intermédiaires pour comprendre le comportement du programme.

```c
#include <stdio.h>

int somme_jusqu_a_n(int n)
{
    int i;
    int somme = 0;

    printf("[DEBUG] n = %d\n", n);   /* Trace d'entrée */

    for (i = 1; i <= n; i++)
    {
        somme += i;
        printf("[DEBUG] i = %d, somme = %d\n", i, somme);  /* Trace dans la boucle */
    }

    printf("[DEBUG] Résultat final = %d\n", somme);
    return (somme);
}
```

### Exemple d'erreur logique détectée

```c
/* BUG : la boucle commence à 0 au lieu de 1 */
for (i = 0; i <= n; i++)    /* Somme de 0 à n → résultat incorrect */
    somme += i;

/* CORRECTION */
for (i = 1; i <= n; i++)    /* Somme de 1 à n → correct */
    somme += i;
```

---

## 3. Erreurs d'exécution courantes

### Segmentation fault (Segfault)

Un **segfault** se produit quand le programme tente d'accéder à une adresse mémoire invalide.

**Causes fréquentes :**

```c
/* 1. Déréférencer un pointeur NULL */
int *p = NULL;
*p = 42;              /* SEGFAULT */

/* 2. Débordement de tableau */
int tab[5];
tab[10] = 0;          /* SEGFAULT possible */

/* 3. Utiliser une variable non initialisée */
int *p;               /* p contient une adresse aléatoire */
*p = 42;              /* SEGFAULT */

/* 4. Pile dépassée (récursion infinie) */
int infini(int n)
{
    return (infini(n)); /* Stack overflow → SEGFAULT */
}
```

### Erreur off-by-one

```c
/* BUG : <= au lieu de < */
int tab[5] = {1, 2, 3, 4, 5};
int i;

for (i = 0; i <= 5; i++)   /* Accède à tab[5] qui n'existe pas */
    printf("%d\n", tab[i]);

/* CORRECTION */
for (i = 0; i < 5; i++)    /* Correct : indices 0 à 4 */
    printf("%d\n", tab[i]);
```

### Division par zéro

```c
int a = 10;
int b = 0;
int resultat = a / b;  /* Comportement indéfini en C */

/* CORRECTION */
if (b == 0)
    printf("Erreur : division par zéro\n");
else
    printf("%d\n", a / b);
```

---

## 4. Utiliser GDB

**GDB** (GNU Debugger) permet d'exécuter le programme pas à pas et d'inspecter la mémoire.

### Compilation avec symboles de débogage

```bash
gcc -g -Wall programme.c -o programme
```

### Commandes GDB essentielles

```bash
gdb ./programme          # Lancer GDB

# Dans GDB :
run                      # Lancer le programme
run arg1 arg2            # Lancer avec des arguments

break main               # Point d'arrêt au début de main
break 25                 # Point d'arrêt à la ligne 25
break ma_fonction        # Point d'arrêt au début d'une fonction

next                     # Exécuter la prochaine ligne (sans entrer dans les fonctions)
step                     # Exécuter la prochaine ligne (entre dans les fonctions)
continue                 # Reprendre jusqu'au prochain point d'arrêt

print variable           # Afficher la valeur d'une variable
print *pointeur          # Afficher la valeur pointée
print tableau[0]         # Afficher un élément de tableau

backtrace                # Afficher la pile d'appels (utile après un segfault)
bt                       # Raccourci pour backtrace

info locals              # Afficher toutes les variables locales
info breakpoints         # Lister les points d'arrêt

quit                     # Quitter GDB
```

### Analyser un segfault avec GDB

```bash
$ gcc -g programme.c -o programme
$ gdb ./programme
(gdb) run
# Le programme plante
(gdb) backtrace
# Affiche la pile d'appels → indique la ligne du crash
```

---

## 5. Utiliser Valgrind

**Valgrind** détecte les erreurs mémoire : accès invalides, fuites mémoire, utilisation de mémoire non initialisée.

```bash
valgrind ./programme
valgrind --leak-check=full ./programme    # Rapport détaillé des fuites
valgrind --track-origins=yes ./programme  # Trouve l'origine des valeurs non initialisées
```

### Exemple de sortie Valgrind

```
==12345== Invalid read of size 4
==12345==    at 0x4005A3: main (programme.c:15)
==12345==  Address 0x5204050 is 0 bytes after a block of size 20 alloc'd
==12345==
==12345== LEAK SUMMARY:
==12345==    definitely lost: 40 bytes in 1 blocks
```

> Signifie : lecture invalide ligne 15 + 40 octets non libérés.

---

## 6. Méthode de débogage

### Approche systématique

1. **Reproduire** le bug de façon fiable.
2. **Isoler** : réduire le code au minimum qui reproduit le bug.
3. **Observer** : utiliser `printf` ou GDB pour inspecter l'état.
4. **Hypothèse** : formuler une théorie sur la cause.
5. **Tester** : vérifier l'hypothèse en modifiant le code.
6. **Corriger** : appliquer la correction.
7. **Valider** : s'assurer que le bug est corrigé et qu'aucune régression n'est introduite.

### Questions utiles pour déboguer

- La valeur attendue correspond-elle à la valeur affichée ?
- La boucle s'exécute-t-elle le bon nombre de fois ?
- Le pointeur est-il `NULL` avant d'être déréférencé ?
- Les indices de tableau restent-ils dans les limites ?
- La mémoire a-t-elle été allouée avant utilisation ?

---

## Points clés

- Compiler toujours avec `-Wall -Werror -Wextra` pour attraper les avertissements.
- Un **segfault** est souvent un pointeur NULL ou un accès hors tableau.
- La technique `printf` est suffisante pour la plupart des bugs simples.
- GDB est indispensable pour les bugs complexes ou les crashes.
- Valgrind est indispensable pour les bugs liés à la mémoire dynamique.
- L'erreur **off-by-one** (`<=` vs `<`) est l'une des plus fréquentes.
- Lire les messages d'erreur **attentivement** : gcc indique la ligne et la nature de l'erreur.

---

## Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| `warning: implicit declaration of function` | Fonction utilisée sans prototype | Inclure le bon header ou déclarer le prototype |
| `undefined reference to 'fonction'` | Fonction non définie ou fichier non compilé | Ajouter le fichier `.c` à la compilation |
| `segmentation fault (core dumped)` | Accès mémoire invalide | Utiliser GDB pour trouver la ligne |
| `double free or corruption` | `free` appelé deux fois sur le même pointeur | Mettre à `NULL` après `free` |
| Résultat incorrect (bug logique) | Algorithme erroné | Tracer avec `printf` ou GDB |

---

## Fichiers de référence

- [`../intro_debugging/`](../intro_debugging/) – Exercices pratiques de débogage
- [`../intro_debugging/sum_to_n.c`](../intro_debugging/sum_to_n.c) – Correction de somme
- [`../intro_debugging/multiplication_table.c`](../intro_debugging/multiplication_table.c) – Correction de table de multiplication
