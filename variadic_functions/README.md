# Variadic Functions - Fonctions Variadiques

## 📚 Objectifs d'Apprentissage

- Comprendre les **fonctions variadiques** (nombre variable d'arguments)
- Utiliser les macros de `<stdarg.h>` : `va_list`, `va_start`, `va_arg`, `va_end`
- Créer des fonctions qui acceptent un nombre variable d'arguments
- Gérer différents types d'arguments dans une fonction variadique
- Valider les paramètres variadiques

---

## 🎯 Concepts Clés

### Qu'est-ce qu'une Fonction Variadique ?

Une **fonction variadique** peut recevoir un **nombre variable d'arguments**. C'est utile pour des cas comme :
- `printf("Hello %s %d\n", name, age)` — nombre d'arguments flexible
- `sum(3, 10, 20, 30)` — somme d'un nombre quelconque de nombres

### Syntaxe

```c
return_type function_name(fixed_param1, fixed_param2, ...)
{
    va_list args;           // Liste des arguments
    va_start(args, n);      // Initialiser la liste

    // Traiter les arguments avec va_arg()
    type value = va_arg(args, type);

    va_end(args);           // Nettoyer la liste
}
```

**Règles** :
- Au moins un paramètre fixe doit exister
- Les `...` doivent être le **dernier paramètre**
- Le dernier paramètre fixe est généralement utilisé pour indiquer le nombre ou le type d'arguments

### Étapes Essentielles

1. **`va_list args`** : Déclarer une liste d'arguments
2. **`va_start(args, n)`** : Initialiser avec le dernier paramètre fixe
3. **`va_arg(args, type)`** : Récupérer chaque argument avec son type
4. **`va_end(args)`** : Nettoyer (important pour la portabilité)

### Exemple Simple

```c
#include <stdio.h>
#include <stdarg.h>

int sum_two(int a, int b)
{
    return (a + b);
}

int sum_many(int n, ...)  // n = nombre d'arguments à suivre
{
    va_list args;
    int sum = 0;
    int i;

    va_start(args, n);     // Initialiser après n
    for (i = 0; i < n; i++)
        sum += va_arg(args, int);  // Récupérer chaque int
    va_end(args);          // Nettoyer

    return (sum);
}

// Utilisation
int main(void)
{
    printf("%d\n", sum_many(3, 10, 20, 30));   // 60
    printf("%d\n", sum_many(5, 1, 2, 3, 4, 5)); // 15
    return (0);
}
```

---

## 📋 Fichiers et Exercices

### 0. `0-sum_them_all.c` — Additionner des Nombres

**Objectif** : Créer une fonction qui additionne un nombre variable d'entiers.

**Concept** : Le premier paramètre fixe indique combien d'entiers suivent.

**Exemple de code** :
```c
#include <stdarg.h>

int sum_them_all(const unsigned int n, ...)
{
    va_list args;
    unsigned int i;
    int sum;

    if (n == 0)         // Pas d'arguments à additionner
        return (0);

    va_start(args, n);  // Initialiser après n
    sum = 0;

    for (i = 0; i < n; i++)
        sum += va_arg(args, int);  // Récupérer et additionner

    va_end(args);       // Nettoyer
    return (sum);
}
```

**Utilisation** :
```c
int result = sum_them_all(3, 10, 20, 30);  // 60
int result = sum_them_all(0);              // 0
int result = sum_them_all(5, 1, 2, 3, 4, 5); // 15
```

**Points Clés** :
- Si `n == 0`, retourner 0 immédiatement
- Utiliser `va_arg(args, int)` pour lire chaque entier
- Toujours appeler `va_end()` pour nettoyer

---

### 1. `1-print_numbers.c` — Afficher des Nombres avec Séparateur

**Objectif** : Créer une fonction qui affiche des entiers avec un séparateur entre eux.

**Concept** : Gérer un paramètre optionnel (`separator` peut être NULL) et afficher proprement.

**Exemple de code** :
```c
#include <stdio.h>
#include <stdarg.h>

void print_numbers(const char *separator, const unsigned int n, ...)
{
    va_list args;
    unsigned int i;

    va_start(args, n);  // Initialiser après n

    for (i = 0; i < n; i++)
    {
        printf("%d", va_arg(args, int));  // Afficher le nombre

        // Ajouter le séparateur (sauf après le dernier)
        if (separator != NULL && i < (n - 1))
            printf("%s", separator);
    }

    va_end(args);
    printf("\n");  // Nouvelle ligne à la fin
}
```

**Utilisation** :
```c
print_numbers(", ", 3, 1, 2, 3);      // Affiche: 1, 2, 3
print_numbers(" - ", 4, 10, 20, 30, 40); // Affiche: 10 - 20 - 30 - 40
print_numbers(NULL, 3, 5, 15, 25);    // Affiche: 51525 (pas de séparateur)
```

**Points Clés** :
- `separator` peut être NULL → vérifier avant utilisation
- N'ajouter le séparateur qu'entre les éléments (`i < (n - 1)`)
- Toujours terminer par `\n`

---

### 2. `2-print_strings.c` — Afficher des Chaînes avec Séparateur

**Objectif** : Afficher des chaînes de caractères avec un séparateur, en gérant les NULL.

**Concept** : Similaire à `print_numbers`, mais avec des chaînes et gestion des NULL.

**Exemple de code** :
```c
#include <stdio.h>
#include <stdarg.h>

void print_strings(const char *separator, const unsigned int n, ...)
{
    va_list args;
    unsigned int i;
    char *str;

    va_start(args, n);  // Initialiser après n

    for (i = 0; i < n; i++)
    {
        str = va_arg(args, char *);  // Récupérer une chaîne

        if (str == NULL)
            printf("(nil)");           // Afficher (nil) si NULL
        else
            printf("%s", str);         // Afficher la chaîne

        if (separator != NULL && i < (n - 1))
            printf("%s", separator);   // Ajouter séparateur
    }

    va_end(args);
    printf("\n");  // Nouvelle ligne à la fin
}
```

**Utilisation** :
```c
print_strings(", ", 3, "Alice", "Bob", "Charlie");
// Affiche: Alice, Bob, Charlie

print_strings(" | ", 4, "Hello", NULL, "World", "!");
// Affiche: Hello | (nil) | World | !

print_strings(NULL, 2, "test", "case");
// Affiche: testcase
```

**Points Clés** :
- Gérer les pointeurs NULL avec `(nil)`
- Vérifier `NULL` avant d'afficher
- Même logique de séparateur que `print_numbers`
- `va_arg(args, char *)` pour récupérer un pointeur

---

## 📚 Tableau Récapitulatif

| Fichier | Concept | Description |
|---------|---------|-------------|
| `0-sum_them_all.c` | Lecture d'entiers | Additionne un nombre variable d'entiers |
| `1-print_numbers.c` | Affichage d'entiers | Affiche les nombres avec séparateur |
| `2-print_strings.c` | Affichage de chaînes | Affiche les chaînes, gère NULL |
| `variadic_functions.h` | Prototypes | Définition des fonctions |

---

## 🔑 Points Clés

| Concept | Explication |
|---------|------------|
| `va_list` | Variable de type liste d'arguments |
| `va_start()` | Initialiser la liste avec le dernier paramètre fixe |
| `va_arg()` | Récupérer et avancer au prochain argument |
| `va_end()` | Nettoyer la liste (important!) |
| Dernier paramètre fixe | Indique généralement le nombre ou le type d'arguments |
| `...` | Doit être le dernier paramètre de la fonction |

---

## ⚠️ Erreurs Courantes

1. **Oublier `va_end()`**
   ```c
   // FAUX : oublie le cleanup
   va_start(args, n);
   for (i = 0; i < n; i++)
       sum += va_arg(args, int);
   // Pas de va_end() !

   // BON :
   va_start(args, n);
   for (i = 0; i < n; i++)
       sum += va_arg(args, int);
   va_end(args);  // Toujours nettoyer
   ```

2. **Mauvais type avec `va_arg()`**
   ```c
   // FAUX : récupérer un float comme int
   float f = va_arg(args, int);  // Comportement indéfini!

   // BON : utiliser le bon type
   float f = va_arg(args, double);  // Les float sont passés en double
   ```

3. **Ne pas avoir de paramètre fixe**
   ```c
   // FAUX : pas de paramètre fixe
   int func(...) { }

   // BON : au moins un paramètre fixe
   int func(int n, ...) { }
   ```

4. **Oublier le nombre d'arguments**
   ```c
   // FAUX : comment savoir combien d'arguments?
   void print_strings(const char *separator, ...)

   // BON : ajouter le nombre
   void print_strings(const char *separator, const unsigned int n, ...)
   ```

5. **Ne pas valider les pointeurs NULL**
   ```c
   // FAUX : crash si str est NULL
   printf("%s", str);

   // BON :
   if (str == NULL)
       printf("(nil)");
   else
       printf("%s", str);
   ```

---

## 📝 Héritage vs Variadique

Avant (sans fonctions variadiques) :
```c
int sum_2(int a, int b) { return (a + b); }
int sum_3(int a, int b, int c) { return (a + b + c); }
int sum_4(int a, int b, int c, int d) { return (a + b + c + d); }
// ... répétition ! Pas scalable !
```

Avec variadiques :
```c
int sum_many(int n, ...)  // Une seule fonction pour tous les cas!
{
    va_list args;
    int sum = 0;
    va_start(args, n);
    for (int i = 0; i < n; i++)
        sum += va_arg(args, int);
    va_end(args);
    return (sum);
}

sum_many(2, 5, 10);       // 15
sum_many(4, 1, 2, 3, 4);  // 10
```

---

## 🎓 Progression

1. **`0-sum_them_all`** : Lire et utiliser des arguments
2. **`1-print_numbers`** : Afficher avec séparateur optionnel
3. **`2-print_strings`** : Gérer les pointeurs et NULL
