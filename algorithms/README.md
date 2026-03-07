# Algorithmes et Complexité

Ce dossier couvre la notion de complexité algorithmique, la mesure de performances en C et la comparaison d'approches algorithmiques.

---

## Table des matières

1. [Complexité algorithmique](#1-complexité-algorithmique)
2. [Notation Big O](#2-notation-big-o)
3. [Mesure du temps d'exécution en C](#3-mesure-du-temps-dexécution-en-c)
4. [Comparaison O(n²) vs O(n)](#4-comparaison-on²-vs-on)
5. [Points clés](#points-clés)
6. [Erreurs courantes](#erreurs-courantes)

---

## 1. Complexité algorithmique

La **complexité algorithmique** mesure combien de ressources (temps, mémoire) un algorithme consomme en fonction de la taille de l'entrée `n`.

On distingue :
- **Complexité temporelle** : nombre d'opérations effectuées
- **Complexité spatiale** : quantité de mémoire utilisée

---

## 2. Notation Big O

La notation **O(…)** décrit le comportement dans le **pire des cas** quand `n` tend vers l'infini.

| Complexité | Nom              | Exemple                         |
|------------|------------------|---------------------------------|
| O(1)       | Constante        | Accès à un élément d'un tableau |
| O(log n)   | Logarithmique    | Recherche binaire               |
| O(n)       | Linéaire         | Parcours d'un tableau           |
| O(n log n) | Quasi-linéaire   | Tri fusion (merge sort)         |
| O(n²)      | Quadratique      | Tri à bulles (bubble sort)      |
| O(2ⁿ)      | Exponentielle    | Sous-ensembles d'un ensemble    |

### Règles de simplification

```
O(3n + 5) → O(n)       (on garde le terme dominant)
O(n² + n) → O(n²)      (on garde le terme dominant)
O(1000)   → O(1)       (constante)
```

---

## 3. Mesure du temps d'exécution en C

On utilise `clock()` de `<time.h>` pour mesurer le temps CPU.

```c
#include <stdio.h>
#include <time.h>

int main(void)
{
    clock_t debut, fin;
    double temps_ecoule;

    debut = clock();

    /* --- Code à mesurer --- */
    volatile long long somme = 0;
    long i;
    for (i = 0; i < 100000000L; i++)
        somme += i;
    /* ---------------------- */

    fin = clock();
    temps_ecoule = (double)(fin - debut) / (double)CLOCKS_PER_SEC;

    printf("Temps d'exécution : %.6f secondes\n", temps_ecoule);
    return (0);
}
```

> **Note :** `volatile` empêche le compilateur d'optimiser la boucle et de la supprimer.

---

## 4. Comparaison O(n²) vs O(n)

### Algorithme naïf O(n²) – double boucle

```c
#include <stdio.h>
#include <time.h>

#define N 10000

int main(void)
{
    int tableau[N];
    long long somme = 0;
    int i, j;
    clock_t debut, fin;

    /* Remplissage du tableau */
    for (i = 0; i < N; i++)
        tableau[i] = i;

    debut = clock();

    /* Double boucle – O(n²) */
    for (i = 0; i < N; i++)
        for (j = 0; j <= i; j++)
            somme += tableau[j];

    fin = clock();
    printf("O(n²) – Temps : %.6f s – Somme : %lld\n",
           (double)(fin - debut) / CLOCKS_PER_SEC, somme);
    return (0);
}
```

### Algorithme optimisé O(n) – passe unique

```c
#include <stdio.h>
#include <time.h>

#define N 10000

int main(void)
{
    int tableau[N];
    long long somme = 0;
    int i;
    clock_t debut, fin;

    for (i = 0; i < N; i++)
        tableau[i] = i;

    debut = clock();

    /* Passe unique – O(n) */
    for (i = 0; i < N; i++)
        somme += (long long)(i + 1) * tableau[i];

    fin = clock();
    printf("O(n)  – Temps : %.6f s – Somme : %lld\n",
           (double)(fin - debut) / CLOCKS_PER_SEC, somme);
    return (0);
}
```

### Résultats observés (exemple réel avec n = 100 000 000)

| Algorithme | Temps mesuré    | Rapport     |
|------------|-----------------|-------------|
| O(n²)      | ~1.345 secondes | ×24 743     |
| O(n)       | ~0.000054 s     | référence   |

> Un algorithme **24 000× plus lent** consomme également **24 000× plus d'énergie** – pertinent pour l'efficacité énergétique.

---

## Points clés

- La complexité O(n²) devient **inacceptable** pour de grands `n` (> 10 000 éléments).
- Toujours viser la complexité la plus basse possible.
- `clock()` mesure le **temps CPU**, pas le temps réel.
- `CLOCKS_PER_SEC` est une constante définie dans `<time.h>`.
- `volatile` est indispensable lors de benchmarks pour éviter que le compilateur n'optimise le code à mesurer.
- Faire **plusieurs mesures** et calculer une moyenne pour avoir un résultat fiable.
- La **réduction de complexité algorithmique** a un impact plus grand que l'optimisation bas niveau.

---

## Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Comparer des temps sans `volatile` | Le compilateur peut supprimer la boucle → temps = 0 | Ajouter `volatile` à la variable accumulatrice |
| Une seule mesure | Les variations système faussent le résultat | Faire 3+ mesures et calculer la moyenne |
| Confondre O(n) et temps réel | Coefficients constants peuvent être importants | Mesurer, ne pas supposer |
| Division par `CLOCKS_PER_SEC` oubliée | Résultat en ticks, pas en secondes | Toujours diviser par `CLOCKS_PER_SEC` |

---

## Fichiers de référence

- [`../benchmarking/`](../benchmarking/) – Mesures de performances et comparaison d'algorithmes
- [`../benchmarking/baseline_loop.c`](../benchmarking/baseline_loop.c) – Boucle de référence
- [`../benchmarking/green_efficiency_analysis.md`](../benchmarking/green_efficiency_analysis.md) – Analyse efficacité énergétique
