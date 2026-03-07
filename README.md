# Base de Connaissances – Programmation en C

> Dépôt personnel d'apprentissage organisé comme une base de connaissances révisable. Toutes les explications sont en français.

---

## Table des matières

### 🗂️ Dossiers de la base de connaissances

| Dossier | Contenu |
|---------|---------|
| [📘 c_programming/](./c_programming/) | Bases du C : compilation, variables, fonctions, boucles |
| [🔢 algorithms/](./algorithms/) | Complexité algorithmique, Big O, benchmarking |
| [🐧 linux/](./linux/) | Commandes Linux, permissions, compilation |
| [🔀 git/](./git/) | Contrôle de version : commits, branches, historique |
| [🧠 memory_management/](./memory_management/) | Pointeurs, tableaux, chaînes, malloc/free |
| [🏗️ data_structures/](./data_structures/) | Listes chaînées, piles, files, arbres binaires |
| [🐛 debugging/](./debugging/) | Débogage : printf, GDB, Valgrind, méthode |
| [📋 cheatsheets/](./cheatsheets/) | Fiches de référence rapide (C, Linux, Git, Débogage) |
| [❌ mistakes/](./mistakes/) | Erreurs courantes : code faux, explication, correction |
| [🧪 experiments/](./experiments/) | Petits programmes C pour tester des concepts |

---

### 📁 Exercices pratiques (code source)

| Dossier | Contenu |
|---------|---------|
| [hello_world/](./hello_world/) | Pipeline de compilation, `puts`, `printf`, `sizeof` |
| [variables_if_else_while/](./variables_if_else_while/) | Variables, conditions, boucles while |
| [functions_nested_loops/](./functions_nested_loops/) | Fonctions, prototypes, boucles imbriquées |
| [more_functions_nested_loops/](./more_functions_nested_loops/) | Fonctions avancées, FizzBuzz, formes géométriques |
| [pointers_arrays_strings/](./pointers_arrays_strings/) | Pointeurs, tableaux, manipulation de chaînes |
| [intro_debugging/](./intro_debugging/) | Exercices de débogage : sommes, tables, boucles |
| [benchmarking/](./benchmarking/) | Mesure de performances CPU, comparaison O(n²) vs O(n) |
| [simple-calculator/](./simple-calculator/) | Calculatrice interactive en C |

---

## Comment utiliser ce dépôt

### Pour réviser un concept
1. Aller dans le dossier thématique correspondant (ex: `c_programming/`)
2. Lire le `README.md` qui explique le concept avec exemples
3. Consulter les fichiers de code source dans les dossiers d'exercices

### Pour une consultation rapide
- Aller dans [`cheatsheets/`](./cheatsheets/) pour les fiches condensées

### Pour comprendre une erreur
- Aller dans [`mistakes/`](./mistakes/) pour voir l'erreur, l'explication et la correction

### Pour expérimenter
- Aller dans [`experiments/`](./experiments/) pour des idées de petits programmes de test

---

## Conventions du dépôt

- **Langage :** C (norme GNU89)
- **Compilation :** `gcc -Wall -Werror -Wextra -pedantic -std=gnu89`
- **Plateforme :** Ubuntu 20.04 LTS
- **Langue des explications :** Français

---

## Progression recommandée

```
1. c_programming/    → Bases du C
2. linux/            → Environnement de travail
3. git/              → Contrôle de version
4. memory_management/→ Pointeurs et mémoire
5. debugging/        → Débogage
6. data_structures/  → Structures de données
7. algorithms/       → Complexité et performance
```
