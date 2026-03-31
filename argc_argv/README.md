# Argc & Argv : Arguments de Ligne de Commande

Ce dossier introduit les **arguments de ligne de commande** en C. Lorsqu'un programme est lancé, on peut lui passer des arguments que le programme peut lire et utiliser.

---

## Table des matières

1. [Argc et Argv](#1-argc-et-argv)
2. [Syntaxe et concepts](#2-syntaxe-et-concepts)
3. [Conversion de chaînes](#3-conversion-de-chaînes)
4. [Validation des arguments](#4-validation-des-arguments)
5. [Explication des fichiers](#5-explication-des-fichiers)
6. [Points clés](#6-points-clés)
7. [Erreurs courantes](#7-erreurs-courantes)

---

## 1. Argc et Argv

Chaque programme C a accès aux arguments de la ligne de commande via les paramètres spéciaux de `main()`:

```c
int main(int argc, char *argv[])
{
    /* ... */
}
```

- **`argc`** (argument count) : Le nombre d'arguments passés au programme (incluant le nom du programme lui-même).
- **`argv`** (argument vector) : Un tableau de chaînes de caractères contenant les arguments.

### Exemple d'utilisation

Si tu lances la commande : `./0-whatsmyname hello world`

```
argc = 3
argv[0] = "./0-whatsmyname"   (nom du programme)
argv[1] = "hello"              (1er argument)
argv[2] = "world"              (2e argument)
```

---

## 2. Syntaxe et concepts

### Accéder au nom du programme

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    (void)argc;  /* On n'utilise pas argc ici, donc on le met en silence */
    printf("%s\n", argv[0]);
    return (0);
}
```

**Sortie :** `./0-whatsmyname`

### Compter le nombre d'arguments

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    (void)argv;  /* On n'utilise pas argv ici */
    printf("%d\n", argc);
    return (0);
}
```

**Sortie :**
```
$ ./1-args
1
$ ./1-args hello world
3
```

### Boucler sur les arguments

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++)
        printf("argv[%d]: %s\n", i, argv[i]);
    
    return (0);
}
```

---

## 3. Conversion de chaînes

Quand tu reçois un argument, c'est toujours une **chaîne de caractères**. Pour le convertir en nombre, utilise les fonctions de conversion de la librairie `<stdlib.h>` :

### atoi() : convertir en entier

```c
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);  /* "42" devient 42 */
    int result = num * 2;
    printf("%d\n", result);
    return (0);
}
```

**Exemple :**
```
$ ./3-mul 10 5
50
```

### atof() : convertir en nombre flottant

```c
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    float num = atof(argv[1]);  /* "3.14" devient 3.14 */
    return (0);
}
```

---

## 4. Validation des arguments

Avant d'utiliser les arguments, il faut **vérifier qu'il y en a suffisamment** et qu'ils sont du bon type.

### Vérifier le nombre minimum d'arguments

```c
int main(int argc, char *argv[])
{
    if (argc < 3)  /* Besoin d'au moins 3 (programme + 2 args) */
    {
        printf("Error\n");
        return (1);  /* Retourner 1 pour indiquer une erreur */
    }
    
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int result = num1 * num2;
    
    printf("%d\n", result);
    return (0);
}
```

### Vérifier que les arguments sont des chiffres

```c
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int i, j;
    
    for (i = 1; i < argc; i++)           /* Pour chaque argument */
    {
        for (j = 0; argv[i][j] != '\0'; j++)  /* Pour chaque caractère */
        {
            if (!isdigit(argv[i][j]))    /* Si ce n'est pas un chiffre */
            {
                printf("Error\n");
                return (1);
            }
        }
    }
    return (0);
}
```

---

## 5. Explication des fichiers

| Fichier | Description |
|---|---|
| `0-whatsmyname.c` | Affiche le nom du programme (`argv[0]`) |
| `1-args.c` | Affiche le nombre d'arguments (`argc`) |
| `2-args.c` | Affiche tous les arguments ligne par ligne |
| `3-mul.c` | Prend deux nombres en arguments et affiche leur produit |
| `4-add.c` | Additionne tous les nombres positifs passés en arguments |
| `main.h` | Fichier d'en-tête avec les prototypes |

---

## 6. Points clés

- `argc` inclut toujours le nom du programme (`argv[0]`). Un programme lancé seul a `argc = 1`.
- `argv` est un tableau de chaînes, donc `argv[0]` est une chaîne, même si elle représente un nombre.
- Toujours convertir les arguments en nombres via `atoi()`, `atof()`, ou des fonctions similaires.
- Toujours **valider les arguments** avant de les utiliser.
- Utiliser `(void)variable;` pour éviter les avertissements du compilateur si une variable n'est pas utilisée.

---

## 7. Erreurs courantes

- **Oublier que `argc` inclut le nom du programme** → Les indices des arguments commencent à 1, pas 0.
- **Ne pas vérifier le nombre d'arguments** → Accès à `argv[i]` qui n'existe pas = comportement indéfini.
- **Oublier de convertir les chaînes en nombres** → Faire `atoi()` est obligatoire pour les calculs.
- **Ne pas vérifier la validité des arguments** → Un utilisateur peut passer n'importe quoi.
- **Confondre `argv` (tableau de pointeurs) et `*argv` (chaîne)** → `argv[i]` est une chaîne, pas un caractère.
