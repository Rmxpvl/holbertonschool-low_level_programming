# More Malloc, Free

Ce dossier regroupe les exercices sur l'allocation dynamique avances avec `malloc`.
L'objectif est de savoir allouer proprement, verifier les erreurs, puis remplir la
memoire selon le comportement demande.

## Objectifs pedagogiques

- renforcer la gestion des pointeurs et de la memoire dynamique
- distinguer les strategies d'erreur: `return (NULL)` vs `exit(98)`
- manipuler des tableaux dynamiques de `char` et de `int`
- initialiser une zone allouee manuellement

## Fichiers du dossier

| Fichier | Description |
|---|---|
| `0-malloc_checked.c` | Fonction `malloc_checked` qui alloue `b` octets et quitte avec `exit(98)` si l'allocation echoue |
| `1-string_nconcat.c` | Fonction `string_nconcat` qui concatene `s1` avec les `n` premiers caracteres de `s2` |
| `2-calloc.c` | Fonction `_calloc` qui alloue `nmemb * size` octets puis initialise tous les octets a `0` |
| `3-array_range.c` | Fonction `array_range` qui cree un tableau d'entiers de `min` a `max` inclus |
| `main.h` | Prototypes des fonctions du projet |

## Rappels importants

- `malloc` reserve une zone memoire mais ne l'initialise pas.
- `calloc` reserve et initialise a `0`.
- Toujours verifier le retour de `malloc`/`calloc` avant d'utiliser le pointeur.
- `free` doit etre utilise plus tard par le code appelant quand la zone n'est plus utile.

## Comportements attendus

- `malloc_checked`:
retourne un pointeur valide ou arrete immediatement le programme avec `exit(98)`.
- `string_nconcat`:
retourne une nouvelle chaine allouee dynamiquement.
- `_calloc`:
retourne `NULL` si `nmemb == 0`, `size == 0`, ou si l'allocation echoue.
- `array_range`:
retourne `NULL` si `min > max` ou si `malloc` echoue.

## Compilation (exemple)

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o test
```