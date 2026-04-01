# Command-Line Arguments (argc & argv)

## 📚 Objectifs d'Apprentissage

- Comprendre le rôle de `argc` et `argv` dans la fonction `main()`
- Traiter les arguments passés en ligne de commande
- Valider et convertir les arguments
- Parser les arguments numériques avec `atoi()`
- Gérer les erreurs d'arguments invalides

---

## 🎯 Concepts Clés

### Qu'est-ce que argc et argv ?

Quand vous exécutez un programme C en ligne de commande, vous pouvez lui passer des **arguments**. La fonction `main()` reçoit ces arguments via deux paramètres spéciaux :

```c
int main(int argc, char *argv[])
```

- **`argc`** : **Argument Count** — nombre d'arguments (entier)
- **`argv`** : **Argument Vector** — tableau de chaînes de caractères contenant les arguments

### Exemple d'Exécution

```bash
$ ./myprogram arg1 arg2 arg3
```

- `argc` = 4 (le nom du programme compte pour 1)
- `argv[0]` = "./myprogram" (le nom du programme)
- `argv[1]` = "arg1"
- `argv[2]` = "arg2"
- `argv[3]` = "arg3"

---

## 📋 Fichiers et Exercices

### 0. `0-whatsmyname.c` — Afficher le nom du programme

**Objectif** : Afficher le nom du programme exécuté.

**Concept** : `argv[0]` contient toujours le nom du programme.

**Exemple de code** :
```c
int main(int argc, char *argv[])
{
    (void)argc;  // On n'a pas besoin de argc
    printf("%s\n", argv[0]);
    return (0);
}
```

**Utilisation** :
```bash
$ gcc 0-whatsmyname.c -o myprog
$ ./myprog
./myprog
```

---

### 1. `1-args.c` — Compter les arguments

**Objectif** : Afficher le nombre d'arguments passés (sans compter le nom du programme).

**Concept** : `argc` nous donne directement ce nombre. On soustrait 1 pour exclure le programme.

**Exemple de code** :
```c
int main(int argc, char *argv[])
{
    (void)argv;  // On n'a pas besoin de argv
    printf("%d\n", argc - 1);  // argc - 1 = nombre d'arguments (sans le programme)
    return (0);
}
```

**Utilisation** :
```bash
$ gcc 1-args.c -o args
$ ./args
0
$ ./args hello world test
3
```

---

### 2. `2-args.c` — Lister tous les arguments

**Objectif** : Afficher chaque argument sur une ligne séparée.

**Concept** : Boucle sur `argv` de 0 à `argc - 1`.

**Exemple de code** :
```c
int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
        printf("%s\n", argv[i]);
    return (0);
}
```

**Utilisation** :
```bash
$ ./args hello world
hello
world
```

---

### 3. `3-mul.c` — Multiplier deux nombres

**Objectif** : Multiplier deux nombres passés en arguments et afficher le résultat. Afficher "Error" si le nombre d'arguments est incorrect.

**Concepts** :
- Valider le nombre d'arguments avec `argc`
- Convertir des chaînes en nombres avec `atoi()`
- Gérer les erreurs

**Exemple de code** :
```c
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 3)  // Exactement 2 arguments requis
    {
        printf("Error\n");
        return (1);
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int result = num1 * num2;

    printf("%d\n", result);
    return (0);
}
```

**Utilisation** :
```bash
$ gcc 3-mul.c -o mul
$ ./mul 3 4
12
$ ./mul 100 2
200
$ ./mul 5        // Erreur
Error
```

---

### 4. `4-add.c` — Additionner des nombres

**Objectif** : Additionner tous les nombres passés en arguments. Afficher "Error" si un argument n'est pas un nombre valide.

**Concepts** :
- Boucle sur plusieurs arguments
- Valider que chaque caractère est un chiffre avec `isdigit()`
- Convertir et accumuler avec `atoi()`
- Gestion plus complexe des erreurs

**Exemple de code** :
```c
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sum = 0;

    if (argc == 1)  // Pas d'arguments
    {
        printf("0\n");
        return (0);
    }

    for (int i = 1; i < argc; i++)  // Parcourt chaque argument
    {
        for (int j = 0; argv[i][j] != '\0'; j++)  // Vérifie chaque caractère
        {
            if (!isdigit(argv[i][j]))  // N'est pas un chiffre
            {
                printf("Error\n");
                return (1);
            }
        }
        sum += atoi(argv[i]);  // Ajoute le nombre
    }

    printf("%d\n", sum);
    return (0);
}
```

**Utilisation** :
```bash
$ gcc 4-add.c -o add
$ ./add 1 2 3 4
10
$ ./add 100 50 25
175
$ ./add 5 abc      // Erreur
Error
$ ./add            // Pas d'arguments
0
```

---

## 🔑 Points Clés

| Concept | Explication |
|---------|------------|
| `argc` | Nombre d'arguments (incluant le nom du programme) |
| `argv` | Tableau de chaînes, `argv[0]` est le programme |
| `(void)` | Cast pour supprimer les avertissements "unused parameter" |
| `atoi()` | Convertit une chaîne en entier (`ascii to integer`) |
| `isdigit()` | Vérifie si un caractère est un chiffre (0-9) |
| Validation | Toujours vérifier `argc` avant d'accéder aux arguments |

---

## ⚠️ Erreurs Courantes

1. **Oublier que `argv[0]` est le programme lui-même**
   ```c
   // FAUX : compte le programme comme argument
   for (int i = 0; i < argc; i++)

   // BON : commence à 1
   for (int i = 1; i < argc; i++)
   ```

2. **Ne pas vérifier les limites de `argc`**
   ```c
   // FAUX : accès en dehors des limites
   printf("%s\n", argv[10]);  // Peut crasher!

   // BON : vérifier d'abord
   if (argc > 10)
       printf("%s\n", argv[10]);
   ```

3. **Oublier les includes nécessaires**
   ```c
   // Pour atoi() : #include <stdlib.h>
   // Pour isdigit() : #include <ctype.h>
   ```

---

## 📝 Exemple Complet d'Utilisation

```bash
$ gcc 0-whatsmyname.c -o whatsmyname && ./whatsmyname
./whatsmyname

$ gcc 1-args.c -o args && ./args hello world test
3

$ gcc 3-mul.c -o mul && ./mul 12 5
60

$ gcc 4-add.c -o add && ./add 10 20 30 40
100
```
