# Hello, World – Premiers pas en C

Ce dossier couvre les bases absolues du langage C : la compilation, les étapes de transformation du code source, et les premières fonctions d'affichage.

---

## Table des matières

1. [Le processus de compilation](#1-le-processus-de-compilation)
2. [Les étapes de compilation avec gcc](#2-les-étapes-de-compilation-avec-gcc)
3. [Afficher du texte : puts et printf](#3-afficher-du-texte--puts-et-printf)
4. [L'opérateur sizeof](#4-lopérateur-sizeof)
5. [Points clés](#5-points-clés)
6. [Erreurs courantes](#6-erreurs-courantes)

---

## 1. Le processus de compilation

En C, le code source passe par **4 étapes** avant de devenir un programme exécutable :

```
Fichier .c  →  Préprocesseur  →  Compilateur  →  Assembleur  →  Éditeur de liens  →  Exécutable
```

| Étape | Outil/flag | Résultat |
|-------|-----------|---------|
| Préprocessing | `gcc -E` | Fichier `.c` étendu (macros développées) |
| Compilation | `gcc -S` | Fichier assembleur `.s` |
| Assemblage | `gcc -c` | Fichier objet `.o` |
| Édition de liens | `gcc` | Exécutable final |

---

## 2. Les étapes de compilation avec gcc

### 0-preprocessor — Préprocessing uniquement

```bash
#!/bin/bash
gcc -E "$CFILE" -o c
```

Le flag `-E` arrête la compilation après le préprocessing. Il développe les `#include`, `#define`, et macros. Le résultat est un fichier `.c` étendu.

### 1-compiler — Compilation sans édition de liens

```bash
#!/bin/bash
gcc -c "$CFILE" -o "${CFILE%.c}.o"
```

Le flag `-c` compile le fichier `.c` en fichier objet `.o` sans créer d'exécutable.

### 2-assembler — Génération du code assembleur

```bash
#!/bin/bash
gcc -S "$CFILE" -o "${CFILE%.c}.s"
```

Le flag `-S` produit le code assembleur (`.s`), lisible par un humain, avant l'assemblage.

### 3-name — Compilation complète vers un exécutable nommé

```bash
#!/bin/bash
gcc "$CFILE" -o "cisfun"
```

Sans flag spécial, `gcc` effectue toutes les étapes et produit un exécutable. L'option `-o` fixe le nom de sortie.

---

## 3. Afficher du texte : puts et printf

### 4-puts.c — La fonction puts()

```c
#include <stdio.h>

int main(void)
{
    puts("\"Programming is like building a multilingual puzzle");
    return (0);
}
```

**Explication :** `puts()` affiche une chaîne de caractères et ajoute **automatiquement** un saut de ligne (`\n`) à la fin. Elle est plus simple que `printf` pour afficher du texte brut.

### 5-printf.c — La fonction printf()

```c
#include <stdio.h>

int main(void)
{
    printf("with proper grammar, but the outcome is a piece of art,\n");
    return (0);
}
```

**Explication :** `printf()` est plus flexible : elle accepte des **spécificateurs de format** (`%d`, `%s`, `%f`…) et ne rajoute **pas** de saut de ligne automatiquement — il faut l'écrire explicitement avec `\n`.

| Fonction | Saut de ligne auto | Format | Usage |
|---------|-------------------|--------|-------|
| `puts` | Oui | Non | Texte brut simple |
| `printf` | Non | Oui | Affichage formaté |

---

## 4. L'opérateur sizeof

### 6-size.c — Tailles des types de base

```c
#include <stdio.h>

int main(void)
{
    printf("Size of a char: %zu byte(s)\n", sizeof(char));
    printf("Size of an int: %zu byte(s)\n", sizeof(int));
    printf("Size of a long int: %zu byte(s)\n", sizeof(long int));
    printf("Size of a long long int: %zu byte(s)\n", sizeof(long long int));
    printf("Size of a float: %zu byte(s)\n", sizeof(float));
    return (0);
}
```

**Explication :** `sizeof` est un **opérateur** (pas une fonction) qui retourne la taille en octets d'un type ou d'une variable. `%zu` est le spécificateur de format pour les valeurs de type `size_t`.

Résultats typiques sur un système 64 bits :

| Type | Taille |
|------|--------|
| `char` | 1 octet |
| `int` | 4 octets |
| `long int` | 8 octets |
| `long long int` | 8 octets |
| `float` | 4 octets |

---

## 5. Points clés

- Le code C doit toujours être **compilé** avant d'être exécuté.
- `gcc` effectue les 4 étapes automatiquement sauf si on utilise un flag pour s'arrêter plus tôt.
- `puts()` ajoute un `\n` automatiquement, `printf()` ne le fait pas.
- `sizeof` est un **opérateur** évalué à la compilation, pas à l'exécution.
- Le spécificateur `%zu` est correct pour `sizeof` (type `size_t`).
- Toujours inclure `<stdio.h>` pour utiliser `puts`, `printf`.
- Le `return (0)` dans `main` signifie que le programme s'est terminé **sans erreur**.

---

## 6. Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Oublier `#include <stdio.h>` | `printf`/`puts` ne sont pas déclarés → erreur de compilation | Toujours inclure `<stdio.h>` en tête |
| Utiliser `%d` avec `sizeof` | `sizeof` retourne `size_t`, pas `int` → avertissement | Utiliser `%zu` |
| Oublier `\n` avec `printf` | L'affichage ne revient pas à la ligne | Ajouter `\n` à la fin de la chaîne |
| Confondre `-c` et `-S` | `-c` produit un `.o`, `-S` produit un `.s` | Se souvenir : `-S` = **S**ource assembleur, `-c` = **c**ompilé |
| Compiler avec un nom incorrect | `./a.out` au lieu du nom voulu | Utiliser `-o nom_exe` pour nommer l'exécutable |
