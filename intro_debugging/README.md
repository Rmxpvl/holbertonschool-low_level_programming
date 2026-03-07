# Introduction au Débogage

Ce dossier introduit les techniques de base pour identifier et corriger des **bugs logiques** dans du code C existant. Les programmes couvrent des fonctions mathématiques et des boucles.

---

## Table des matières

1. [Qu'est-ce que le débogage ?](#1-quest-ce-que-le-débogage-)
2. [Types d'erreurs en C](#2-types-derreurs-en-c)
3. [Techniques de débogage](#3-techniques-de-débogage)
4. [Explication des fichiers](#4-explication-des-fichiers)
5. [Points clés](#5-points-clés)
6. [Erreurs courantes](#6-erreurs-courantes)

---

## 1. Qu'est-ce que le débogage ?

Le **débogage** (debugging) est le processus de trouver et corriger les erreurs dans un programme. En C, les bugs peuvent être :

- Des **erreurs de compilation** (syntaxe incorrecte)
- Des **erreurs d'exécution** (segfault, division par zéro)
- Des **erreurs logiques** (le programme tourne mais donne un résultat incorrect)

Ce dossier se concentre sur les **erreurs logiques** — les plus difficiles à trouver car le compilateur ne les signale pas.

---

## 2. Types d'erreurs en C

| Type | Exemple | Détecté quand |
|------|---------|--------------|
| Syntaxe | `int x = ;` | Compilation |
| Lien | `undefined reference to foo` | Compilation/Lien |
| Exécution | Déréférencement de NULL | À l'exécution |
| Logique | Résultat incorrect | Seulement par test |

---

## 3. Techniques de débogage

### 3.1 Printf debugging — Ajouter des affichages temporaires

La méthode la plus simple : insérer des `printf` pour afficher l'état des variables.

```c
int total_sum(int rows, int cols)
{
    int r, total = 0, current = 0;

    for (r = 1; r <= rows; r++)
    {
        current += row_sum(r, cols);
        printf("DEBUG: r=%d, current=%d, total=%d\n", r, current, total); /* temporaire */
        total = current;
    }
    return total;
}
```

### 3.2 Tracer l'exécution à la main

Suivre le code ligne par ligne avec un exemple concret, en notant la valeur de chaque variable à chaque étape.

Exemple pour `sum_to_n(3)` :

```
i=1 : sum = 0 + 1 = 1
i=2 : sum = 1 + 2 = 3
i=3 : sum = 3 + 3 = 6
Résultat : 6  ✓
```

### 3.3 Vérifier les conditions de boucle

Les erreurs **off-by-one** (décalage d'un) sont très fréquentes :

```c
/* Multiplication table — boucle correcte */
for (col = 1; col <= size; col++)   /* de 1 à size inclus */
    printf("%d ", row * col);
```

```c
/* Boucle incorrecte — manque la dernière colonne */
for (col = 1; col < size; col++)    /* de 1 à size-1 seulement */
    printf("%d ", row * col);
```

---

## 4. Explication des fichiers

### multiplication_table.c — Table de multiplication

```c
void print_table(int size)
{
    int row, col;

    for (row = 1; row <= size; row++)
    {
        for (col = 1; col <= size; col++)
        {
            printf("%d ", row * col);
        }
        printf("\n");
    }
}
```

Affiche une table de multiplication `size × size`. La boucle interne va de 1 à `size` **inclus** (condition `col <= size`).

### row_sums.c — Sommes par ligne

```c
int row_sum(int row, int cols)
{
    int c, sum = 0;
    for (c = 1; c <= cols; c++)
        sum += row * c;
    return sum;
}

int total_sum(int rows, int cols)
{
    int r, total = 0, current = 0;
    for (r = 1; r <= rows; r++)
    {
        current += row_sum(r, cols);
        total = current;
    }
    return total;
}
```

`row_sum` calcule la somme des éléments d'une ligne. `total_sum` accumule les sommes de toutes les lignes.

**Point d'attention :** `total = current` à l'intérieur de la boucle met `total` à jour à chaque itération — c'est volontaire pour que `total` reflète la somme cumulée.

### sum_to_n.c — Somme de 1 à n

```c
int sum_to_n(int n)
{
    int i, sum = 0;
    for (i = 1; i <= n; i++)
        sum += i;
    return sum;
}
```

Additionne tous les entiers de 1 à `n`. Pour `n = 10`, le résultat est 55.

**Formule mathématique équivalente :** `n × (n + 1) / 2`

---

## 5. Points clés

- Lire le code **lentement** et ligne par ligne — les bugs sont souvent à un endroit évident mais peu visible.
- Tracer l'exécution à la main avec un exemple petit (n=3 ou n=4) pour vérifier la logique.
- Les erreurs **off-by-one** (décalage de 1) sont la cause n°1 de bugs dans les boucles — vérifier `<` vs `<=`.
- Ajouter des `printf` temporaires de débogage, puis les supprimer une fois le bug trouvé.
- Vérifier que les **accumulateurs** (`sum = 0`, `total = 0`) sont initialisés **avant** la boucle.
- Compiler avec `-Wall -Wextra` pour détecter les avertissements qui indiquent souvent des bugs.

---

## 6. Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Condition `< size` au lieu de `<= size` | Manque la dernière itération | Vérifier si la borne est incluse ou exclue |
| Accumulateur non initialisé | `sum` a une valeur aléatoire au départ | Toujours écrire `int sum = 0;` |
| Variable de boucle mal choisie | `i = 0` au lieu de `i = 1` pour une somme | Adapter l'initialisation au domaine mathématique |
| `total = current` vs `total += current` | `total = current` remplace, `total += current` accumule | Choisir selon si on veut cumuler ou remplacer |
| Boucle qui s'arrête trop tôt | `while (i < n)` au lieu de `while (i <= n)` | Tracer manuellement la dernière itération pour vérifier |
