# Calculatrice Simple en C

Ce projet est une calculatrice interactive en ligne de commande, écrite en C. Il illustre l'utilisation de `scanf`, des structures `if/else if/else`, la gestion d'erreurs et les conversions de types.

---

## Table des matières

1. [Description du programme](#1-description-du-programme)
2. [Lecture des entrées utilisateur avec scanf](#2-lecture-des-entrées-utilisateur-avec-scanf)
3. [Structure du code](#3-structure-du-code)
4. [La division et le cast de type](#4-la-division-et-le-cast-de-type)
5. [Points clés](#5-points-clés)
6. [Erreurs courantes](#6-erreurs-courantes)

---

## 1. Description du programme

La calculatrice propose 4 opérations de base :

```
1 → Addition
2 → Soustraction
3 → Multiplication
4 → Division
0 → Quitter
```

L'utilisateur choisit une opération, saisit deux nombres, et le résultat s'affiche.

### Compilation et exécution

```bash
gcc -Wall -Wextra -pedantic calculator.c -o calculator
./calculator
```

### Exemple d'utilisation

```
Veuillez saisir une opération :
1 pour addition
...
1
Veuillez saisir le premier nombre :
10
Veuillez saisir le deuxième nombre :
3
Le résultat de votre addition est : 13
```

---

## 2. Lecture des entrées utilisateur avec scanf

`scanf` lit une entrée depuis le clavier et la stocke dans une variable.

```c
int choix;
printf("Votre choix : ");
scanf("%d", &choix);   /* & est obligatoire — passe l'adresse de choix */
```

**Important :** Toujours utiliser `&` devant la variable (sauf pour les tableaux/pointeurs).

| Format | Type | Exemple |
|--------|------|---------|
| `%d` | `int` | `scanf("%d", &n)` |
| `%f` | `float` | `scanf("%f", &f)` |
| `%c` | `char` | `scanf("%c", &c)` |
| `%s` | chaîne | `scanf("%s", chaine)` (pas de `&`) |

---

## 3. Structure du code

Le programme utilise des `if/else if/else` imbriqués pour traiter chaque opération :

```c
if (user_choice == 1)
{
    /* addition */
    scanf("%d", &num1);
    scanf("%d", &num2);
    result = num1 + num2;
    printf("Le résultat : %d\n", result);
}
else if (user_choice == 2)
{
    /* soustraction */
}
else if (user_choice == 3)
{
    /* multiplication */
}
else if (user_choice == 4)
{
    /* division — cas spécial */
}
else if (user_choice == 0)
{
    printf("Tu me quittes déjà ?\n");
}
else
{
    printf("Choix invalide.\n");
}
```

---

## 4. La division et le cast de type

La division est le cas le plus complexe car elle nécessite :

1. **Vérifier la division par zéro**
2. **Afficher un entier ou un décimal** selon le résultat

```c
if (numB == 0)
{
    printf("Erreur : Il est impossible de diviser par zéro ! Baka !\n");
    return (0);
}
else
{
    result_division = (float)numA / (float)numB;  /* cast en float avant la division */
}

if (result_division == (int)result_division)
    printf("Résultat entier : %d\n", (int)result_division);
else
    printf("Résultat décimal : %.2f\n", result_division);
```

**Pourquoi `(float)numA / (float)numB` ?**

Sans le cast, `10 / 3` donne `3` (division entière). Avec le cast, `10.0f / 3.0f` donne `3.333...`.

---

## 5. Points clés

- `scanf("%d", &variable)` : le `&` est **obligatoire** pour les variables simples (`int`, `float`, `char`).
- En C, la division entre deux entiers donne un entier tronqué : `7 / 2 = 3`.
- Pour obtenir un résultat décimal, au moins un des opérandes doit être `float` : `(float)7 / 2 = 3.5`.
- Toujours vérifier la division par zéro **avant** d'effectuer la division.
- `if (result == (int)result)` vérifie si un `float` est un entier (pas de partie décimale).
- Le `return (0)` dans le cas d'erreur arrête le programme proprement.

---

## 6. Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Oublier `&` dans `scanf` | `scanf("%d", n)` passe la valeur de `n`, pas son adresse → comportement indéfini | Écrire `scanf("%d", &n)` |
| Division entière | `int / int` tronque le résultat décimal | Caster au moins un opérande en `float` avant la division |
| Ne pas vérifier la division par zéro | Division par 0 → comportement indéfini (crash) | Vérifier `if (b == 0)` avant de diviser |
| `if (choix = 1)` au lieu de `if (choix == 1)` | Affecte 1 à `choix` → condition toujours vraie | Utiliser `==` pour les comparaisons |
| Pas de cas `else` final | Si l'utilisateur entre une valeur inconnue, rien ne s'affiche | Toujours prévoir un `else` pour les cas non gérés |
