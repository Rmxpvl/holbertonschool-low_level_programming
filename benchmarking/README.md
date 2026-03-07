# Benchmarking – Mesure de Performance en C

Ce dossier se concentre sur la **mesure des performances** des programmes C en utilisant le temps CPU, et sur la comparaison empirique d'algorithmes de complexités différentes.

---

## Table des matières

1. [Mesure du temps CPU avec clock()](#1-mesure-du-temps-cpu-avec-clock)
2. [Instrumentation multi-phases](#2-instrumentation-multi-phases)
3. [Comparaison O(n²) vs O(n)](#3-comparaison-on²-vs-on)
4. [Explication des fichiers](#4-explication-des-fichiers)
5. [Points clés](#5-points-clés)
6. [Erreurs courantes](#6-erreurs-courantes)

---

## 1. Mesure du temps CPU avec clock()

La fonction `clock()` de `<time.h>` mesure le **temps processeur** utilisé par le programme.

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

- `clock()` retourne des **ticks processeur**
- Diviser par `CLOCKS_PER_SEC` convertit en secondes
- `volatile` empêche le compilateur d'optimiser et de supprimer la boucle

---

## 2. Instrumentation multi-phases

On peut mesurer chaque **phase** d'un programme séparément pour identifier les goulots d'étranglement.

```c
clock_t t1, t2, t3, t4;

t1 = clock();
/* Phase 1 : construction du dataset */
t2 = clock();
/* Phase 2 : traitement */
t3 = clock();
/* Phase 3 : réduction (checksum) */
t4 = clock();

printf("Phase 1 : %.6f s\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
printf("Phase 2 : %.6f s\n", (double)(t3 - t2) / CLOCKS_PER_SEC);
printf("Phase 3 : %.6f s\n", (double)(t4 - t3) / CLOCKS_PER_SEC);
```

---

## 3. Comparaison O(n²) vs O(n)

### Algorithme naïf O(n²) — double boucle

```c
#define N 10000

int main(void)
{
    int tableau[N];
    long long somme = 0;
    int i, j;
    clock_t debut, fin;

    for (i = 0; i < N; i++)
        tableau[i] = i;

    debut = clock();

    for (i = 0; i < N; i++)       /* boucle externe */
        for (j = 0; j <= i; j++)  /* boucle interne → O(n²) */
            somme += tableau[j];

    fin = clock();
    printf("O(n²) : %.6f s\n", (double)(fin - debut) / CLOCKS_PER_SEC);
    return (0);
}
```

### Algorithme optimisé O(n) — passe unique

```c
debut = clock();

for (i = 0; i < N; i++)
    somme += (long long)(i + 1) * tableau[i];  /* passe unique */

fin = clock();
printf("O(n) : %.6f s\n", (double)(fin - debut) / CLOCKS_PER_SEC);
```

### Résultats mesurés (n = 100 000 000)

| Algorithme | Temps mesuré | Rapport |
|------------|-------------|---------|
| O(n²) | ~1.345 secondes | ×24 743 |
| O(n) | ~0.000054 s | référence |

Un algorithme **24 000× plus lent** consomme également **24 000× plus d'énergie**.

---

## 4. Explication des fichiers

### baseline_loop.c — Boucle de référence

Boucle simple sur 100 000 000 itérations pour établir un **temps de base**. Permet de calibrer les mesures.

### instrumentation_lab.c — Instrumentation multi-phases

Mesure séparément le temps de :
1. Construction du dataset
2. Traitement des données
3. Réduction (calcul du checksum)

Identifie quelle phase est la plus coûteuse.

### baseline_loop-metrics.md

Résultats de mesures sur 3 exécutions de la boucle de base. Montre la variabilité des mesures et l'importance de faire plusieurs runs.

### comparison_algorithms-metrics.md

Comparaison empirique de l'algorithme O(n²) vs O(n) avec les temps réels mesurés.

### green_efficiency_analysis.md

Analyse de l'impact énergétique des choix algorithmiques. Montre le lien direct entre complexité algorithmique et consommation d'énergie.

---

## 5. Points clés

- `clock()` mesure le **temps CPU**, pas le temps réel (wall clock time).
- Toujours diviser par `CLOCKS_PER_SEC` pour convertir en secondes.
- `volatile` est indispensable lors de benchmarks pour éviter que le compilateur n'optimise le code à mesurer.
- Faire **plusieurs mesures** (3 minimum) et utiliser la moyenne pour des résultats fiables.
- La complexité algorithmique a un impact bien plus grand que les optimisations bas niveau.
- O(n²) devient **inacceptable** pour n > 10 000 environ.
- Réduire la complexité algorithmique réduit directement la consommation d'énergie.

---

## 6. Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Oublier `volatile` | Le compilateur supprime la boucle → temps = 0 | Ajouter `volatile` à la variable accumulatrice |
| Une seule mesure | Les variations système faussent le résultat | Faire 3+ mesures et calculer la moyenne |
| Ne pas diviser par `CLOCKS_PER_SEC` | Résultat en ticks, pas en secondes | Toujours diviser : `(double)(fin - debut) / CLOCKS_PER_SEC` |
| Confondre O(n) et temps réel | Les coefficients constants peuvent être importants | Mesurer empiriquement, ne pas supposer |
| Mesurer avant/après compilation avec `-O2` | Les optimisations du compilateur changent tout | Compiler sans `-O2` pour des benchmarks équitables |
