# Variadic Functions

Ce dossier contient des exercices sur les fonctions variadiques en C.

## Objectif

Comprendre comment une fonction peut recevoir un nombre variable d'arguments
avec les macros de `<stdarg.h>`:

- `va_list`
- `va_start`
- `va_arg`
- `va_end`

## Fichiers

| Fichier | Description |
|---|---|
| `0-sum_them_all.c` | Retourne la somme de tous les parametres recus. Si `n == 0`, retourne `0`. |

## Rappel rapide

Une fonction variadique declare un dernier parametre fixe avant `...`.

Exemple:

```c
int sum_them_all(const unsigned int n, ...);
```

Pour lire les arguments supplementaires:

1. Initialiser la liste avec `va_start(args, n)`
2. Lire chaque argument avec `va_arg(args, int)`
3. Nettoyer avec `va_end(args)`

## Compilation (exemple)

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 0-main.c 0-sum_them_all.c -o a
```
