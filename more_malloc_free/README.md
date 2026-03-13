# More Malloc, Free

Ce dossier poursuit le travail sur l'**allocation dynamique** en C avec des fonctions qui doivent rester robustes même en cas d'erreur d'allocation.

## Objectif général

Approfondir l'usage de `malloc` en appliquant deux règles importantes :
- vérifier les échecs d'allocation,
- réagir correctement selon les consignes de l'exercice.

---

## Fichiers présents

| Fichier | Description |
|---|---|
| `0-malloc_checked.c` | Alloue une zone mémoire et termine le programme avec `exit(98)` si `malloc` échoue |
| `main.h` | Fichier d'en-tête contenant les prototypes utilisés dans ce projet |

---

## Point clé de l'exercice `malloc_checked`

La fonction `malloc_checked` est différente d'une allocation classique qui retourne `NULL` en cas d'échec. Ici, la consigne impose :
- d'appeler `malloc`,
- de vérifier si le pointeur retourné vaut `NULL`,
- de terminer immédiatement le programme avec `exit(98)` si l'allocation échoue.

```c
void *ptr;

ptr = malloc(b);
if (ptr == NULL)
    exit(98);
return (ptr);
```

---

## Pourquoi cette approche ?

Cette variante simplifie le code appelant : la fonction garantit qu'elle retourne un pointeur valide, ou bien le programme s'arrête immédiatement. Cela permet de se concentrer sur la logique suivante sans propager la gestion d'erreur dans chaque appel.

---

## À retenir

- `malloc` retourne `NULL` si l'allocation échoue.
- `exit(98)` termine le programme avec le code de sortie `98`.
- Le type de retour `void *` permet de réutiliser la fonction pour différents types de données.