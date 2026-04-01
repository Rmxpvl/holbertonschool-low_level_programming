# Function Pointers - Pointeurs de Fonctions

## 📚 Objectifs d'Apprentissage

- Comprendre ce qu'est un pointeur de fonction
- Déclarer et utiliser des pointeurs de fonction
- Passer une fonction comme argument à une autre fonction (callback)
- Sélectionner une fonction dynamiquement à l'exécution
- Stocker et appeler des fonctions via des pointeurs
- Utiliser des structures pour associer des fonctions et des données

---

## 🎯 Concepts Clés

### Qu'est-ce qu'un Pointeur de Fonction ?

Un **pointeur de fonction** est une variable qui contient l'adresse mémoire d'une fonction. Au lieu de stocker une valeur (comme `int` ou `char`), il stocke l'adresse d'une fonction.

**Pourquoi c'est utile ?**
- Passer des comportements (fonctions) en paramètres
- Changer le comportement d'un programme à l'exécution
- Créer des callbacks (fonctions appelées par d'autres)
- Écrire du code générique et réutilisable

### Déclaration et Syntaxe

**Fonction normale** :
```c
int add(int a, int b)
{
    return (a + b);
}
```

**Pointeur vers cette fonction** :
```c
int (*func_ptr)(int, int);  // Déclare un pointeur de fonction
func_ptr = &add;             // Initialise avec l'adresse de add
// ou simplement :
func_ptr = add;              // add (sans &) donne aussi l'adresse
```

**Appeler via le pointeur** :
```c
int result = func_ptr(3, 5);  // Appelle add(3, 5)
// Ou explicitement :
int result = (*func_ptr)(3, 5);
```

### Syntaxe Générale

```c
type (*nom_pointeur)(paramètres);
```

- `type` : type de retour de la fonction
- `(*nom_pointeur)` : c'est un pointeur
- `(paramètres)` : types des paramètres de la fonction

**Exemples** :
```c
int (*fp1)(int, int);                    // Prend 2 int, retourne int
void (*fp2)(char *);                     // Prend char*, retourne void
float (*fp3)(float, float, float);       // Prend 3 float, retourne float
```

---

## 📋 Fichiers et Exercices

### 0. `0-print_name.c` — Premier Pointeur de Fonction (Callback)

**Objectif** : Créer une fonction qui receive une fonction de callback pour afficher un nom.

**Concept** : Passer une fonction comme paramètre pour définir le comportement.

**Utilité** : La même fonction `print_name` peut appeler différentes fonctions selon le contexte.

**Exemple de code** :
```c
#include <stdio.h>

/**
 * print_name - prints a name using a callback function
 * @name: name to print
 * @f: pointer to the function that prints the name
 */
void print_name(char *name, void (*f)(char *))
{
    if (name != NULL && f != NULL)
        f(name);    // Appelle la fonction fournie
}

// Fonctions de callback possibles
void print_uppercase(char *name)
{
    for (int i = 0; name[i]; i++)
        printf("%c", toupper(name[i]));
    printf("\n");
}

void print_lowercase(char *name)
{
    for (int i = 0; name[i]; i++)
        printf("%c", tolower(name[i]));
    printf("\n");
}

// Utilisation
int main(void)
{
    print_name("Alice", print_uppercase);    // Affiche : ALICE
    print_name("Bob", print_lowercase);      // Affiche : bob
    return (0);
}
```

**Points Clés** :
- La signature doit correspondre : `void (*f)(char *)` attend une fonction qui prend `char*` et retourne `void`
- On valide que le pointeur n'est pas NULL avant d'appeler
- **Callback** = on passe une fonction pour qu'elle soit appelée par une autre

---

### 1. `1-array_iterator.c` — Appliquer une Fonction à chaque Élément

**Objectif** : Créer une fonction qui exécute une fonction sur chaque élément d'un tableau.

**Concept** : Utiliser un pointeur de fonction pour appliquer une action générique à tous les éléments.

**Utilité** : La même fonction peut afficher, modifier, ou traiter les éléments différemment selon la fonction passée.

**Exemple de code** :
```c
#include <stdio.h>

/**
 * array_iterator - executes a function on each element of an array
 * @array: array of integers
 * @size: size of the array
 * @action: pointer to the function to apply
 */
void array_iterator(int *array, size_t size, void (*action)(int))
{
    size_t i;

    if (array == NULL || action == NULL)
        return;

    for (i = 0; i < size; i++)
        action(array[i]);  // Appelle action sur chaque élément
}

// Fonctions d'action possibles
void print_int(int n)
{
    printf("%d\n", n);
}

void double_int(int n)
{
    printf("%d\n", n * 2);
}

// Utilisation
int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5};

    array_iterator(numbers, 5, print_int);
    // Affiche : 1 2 3 4 5

    array_iterator(numbers, 5, double_int);
    // Affiche : 2 4 6 8 10

    return (0);
}
```

**Points Clés** :
- Parcourt chaque élément du tableau
- Appelle la fonction callback sur chaque élément
- La fonction callback ne retourne rien (`void`)
- Très utile pour écrire du code générique

---

### 2. `2-int_index.c` — Chercher un Élément avec une Condition

**Objectif** : Créer une fonction qui cherche le premier élément d'un tableau satisfaisant une condition.

**Concept** : Utiliser un pointeur de fonction pour définir la condition de recherche.

**Utilité** : Chercher des éléments selon différents critères sans duplicater le code.

**Exemple de code** :
```c
/**
 * int_index - finds the first element that satisfies a condition
 * @array: array of integers
 * @size: size of the array
 * @cmp: pointer to the comparison function
 *
 * Return: index of first match, or -1 if none
 */
int int_index(int *array, int size, int (*cmp)(int))
{
    int i;

    if (array == NULL || cmp == NULL || size <= 0)
        return (-1);

    for (i = 0; i < size; i++)
    {
        if (cmp(array[i]) != 0)  // Si cmp retourne != 0, c'est un match
            return (i);
    }

    return (-1);  // Aucun match trouvé
}

// Fonctions de comparaison
int is_positive(int n)
{
    return (n > 0);  // Retourne non-zéro si positif
}

int is_even(int n)
{
    return (n % 2 == 0);  // Retourne non-zéro si pair
}

int is_greater_than_10(int n)
{
    return (n > 10);  // Retourne non-zéro si > 10
}

// Utilisation
int main(void)
{
    int numbers[] = {-1, -2, 3, 4, 5};

    int idx = int_index(numbers, 5, is_positive);
    printf("First positive at index: %d\n", idx);  // 2 (valeur 3)

    idx = int_index(numbers, 5, is_even);
    printf("First even at index: %d\n", idx);      // 3 (valeur 4)

    idx = int_index(numbers, 5, is_greater_than_10);
    printf("First > 10 at index: %d\n", idx);     // -1 (aucun)

    return (0);
}
```

**Points Clés** :
- La fonction de comparaison retourne 0 (pas de match) ou non-zéro (match)
- Retourne l'**index** du premier match
- Retourne -1 si aucun ne correspond
- Valide les entrées (NULL checks)

---

### 3. `3-main.c`, `3-get_op_func.c`, `3-op_functions.c` — Calculatrice Simple

**Objectif** : Créer une calculatrice en ligne de commande qui utilise des pointeurs de fonction pour sélectionner l'opération.

**Concept** : Utiliser un tableau de structures pour stocker des paires (opérateur, fonction).

**Utilité** : Ajouter une nouvelle opération est aussi simple qu'ajouter une ligne au tableau.

**Architecture** :
```c
// 3-calc.h — Header avec les types
typedef struct s_op
{
    char *op;              // Chaîne de l'opérateur (+, -, *, /, %)
    int (*f)(int, int);    // Pointeur vers la fonction d'opération
} op_t;

// Prototypes
int (*get_op_func(char *s))(int, int);
int op_add(int a, int b);
int op_sub(int a, int b);
int op_mul(int a, int b);
int op_div(int a, int b);
int op_mod(int a, int b);
```

**Exemple de sélection** :
```c
int (*get_op_func(char *s))(int, int)
{
    op_t ops[] = {
        {"+", op_add},
        {"-", op_sub},
        {"*", op_mul},
        {"/", op_div},
        {"%", op_mod},
        {NULL, NULL}
    };
    int i = 0;

    while (ops[i].op != NULL)
    {
        if (ops[i].op[0] == s[0] && s[1] == '\0')
            return (ops[i].f);  // Retourne le pointeur vers la fonction
        i++;
    }
    return (NULL);  // Opérateur non trouvé
}
```

**Utilisation** :
```c
int main(int argc, char *argv[])
{
    int num1, num2;
    int (*operation)(int, int);

    if (argc != 4)
    {
        printf("Error\n");
        return (98);
    }

    operation = get_op_func(argv[2]);  // Trouve la fonction correspondante
    if (operation == NULL)
    {
        printf("Error\n");
        return (99);
    }

    num1 = atoi(argv[1]);
    num2 = atoi(argv[3]);

    printf("%d\n", operation(num1, num2));  // Appelle l'opération
    return (0);
}
```

**Utilisation en ligne de commande** :
```bash
$ ./calc 10 + 5
15

$ ./calc 20 / 4
5

$ ./calc 7 % 3
1

$ ./calc 10 ^ 2    // Erreur : ^ n'existe pas
Error
```

**Points Clés** :
- Tableau de structures stockant opérateur + fonction
- Recherche la fonction correspondante
- Appelle la fonction avec les arguments converti
- Très extensible : ajouter une opération = une ligne

---

## 🔑 Points Clés à Retenir

| Concept | Explication |
|---------|------------|
| `int (*fp)(int, int)` | Pointeur vers une fonction prenant 2 int et retournant int |
| `fp = function_name;` | Initialiser un pointeur de fonction |
| `fp(arg1, arg2)` | Appeler une fonction via son pointeur |
| `(*fp)(arg1, arg2)` | Forme alternative (équivalente) |
| Callback | Passer une fonction pour qu'une autre la call |
| NULL checks | Toujours vérifier que les pointeurs ne sont pas NULL |

---

## ⚠️ Erreurs Courantes

1. **Oublier les parenthèses dans la déclaration**
   ```c
   // FAUX : cela veut dire "pointeur int retourné par la fonction"
   int *fp(int, int);

   // BON : pointeur vers une fonction
   int (*fp)(int, int);
   ```

2. **Ne pas valider les pointeurs NULL**
   ```c
   // FAUX : crash si f est NULL
   f(value);

   // BON :
   if (f != NULL)
       f(value);
   ```

3. **Mal initialiser le pointeur**
   ```c
   // FAUX : sans & ou nom de fonction
   fp = NULL;  // OK pour NULL
   fp = &123;  // Erreur!

   // BON :
   fp = function;   // Nom de fonction = adresse
   fp = &function;  // Explicit avec &
   ```

4. **Mélanger les signatures**
   ```c
   // FAUX : signatures incompatibles
   void func(int a, int b) { }
   int (*fp)(int);  // Attend 1 paramètre!
   fp = func;       // Erreur!

   // BON : signatures doivent correspondre
   int (*fp)(int, int);
   int (*fp)(int, int) = func;
   ```

---

## 📝 Exemple Complet : Système de Callbacks

```c
#include <stdio.h>

// Pointeur de fonction pour les callbacks
typedef int (*callback_t)(int, int);

// Deux fonctions différentes
int multiply(int a, int b) { return (a * b); }
int add(int a, int b) { return (a + b); }

// Une fonction générique qui utilise un callback
void process_numbers(int x, int y, callback_t cb)
{
    if (cb != NULL)
        printf("Result: %d\n", cb(x, y));
}

int main(void)
{
    // Utiliser callback pour multiplier
    process_numbers(5, 3, multiply);    // Affiche : Result: 15

    // Utiliser callback pour additionner
    process_numbers(5, 3, add);         // Affiche : Result: 8

    return (0);
}
```

---

## 🎓 Résumé de Progressions

1. **0-print_name** : Simple callback, affiche
2. **1-array_iterator** : Appliquer une fonction à un ensemble
3. **2-int_index** : Chercher selon une condition
4. **3-calc** : Sélection dynamique plutôt que if/else
