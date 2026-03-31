# Analyse Dynamique : GDB et Valgrind

Ce dossier introduit l'**analyse dynamique** en C : utiliser des outils comme **GDB** (débogueur) et **Valgrind** (détecteur de fuites mémoire) pour déboguer et analyser des programmes en temps réel.

---

## Table des matières

1. [Analyse dynamique vs statique](#1-analyse-dynamique-vs-statique)
2. [Compilation pour le débogage](#2-compilation-pour-le-débogage)
3. [GDB - Le débogueur GNU](#3-gdb---le-débogueur-gnu)
4. [Valgrind - Détection des fuites mémoire](#4-valgrind---détection-des-fuites-mémoire)
5. [Combiner GDB et Valgrind](#5-combiner-gdb-et-valgrind)
6. [Points clés](#6-points-clés)
7. [Ressources et exercices](#7-ressources-et-exercices)

---

## 1. Analyse dynamique vs statique

### Analyse statique

Examiner le code **sans l'exécuter**. Exemples :
- Lire le code et chercher des erreurs
- Utiliser des linters comme `gcc -Wall -Wextra`

### Analyse dynamique (le sujet de ce dossier)

Analyser le code **pendant son exécution**. Utiliser des outils pour observer :
- Les valeurs en mémoire à chaque instant
- L'état des variables
- Les appels de fonctions
- Les fuites mémoire
- Les accès à la mémoire invalides

---

## 2. Compilation pour le débogage

Pour utiliser GDB correctement, compiler avec le flag `-g` qui ajoute les **symboles de débogage** au binaire.

### Compilation standard (sans débogage)

```bash
gcc -c source.c
gcc source.o -o prog
```

Les symboles de débogage **manquent**, GDB ne pourra pas voir les noms de variable.

### Compilation avec débogage

```bash
gcc -g -c source.c
gcc -g source.o -o prog
```

Le flag `-g` ajoute les symboles de débogage. Le binaire `prog` est plus gros mais devient complètement déboguable.

### Compilation optimale pour le développement

```bash
gcc -g -Wall -Wextra -pedantic -c source.c
gcc -g -Wall -Wextra -pedantic source.o -o prog
```

- `-g` : Symboles de débogage
- `-Wall` : Tous les avertissements principaux
- `-Wextra` : Avertissements supplémentaires
- `-pedantic` : Strict respect de la norme C

---

## 3. GDB - Le débogueur GNU

GDB permet de **contrôler l'exécution** d'un programme et d'inspecter son état.

### Lancer GDB

```bash
gdb ./prog
```

Cela lance GDB et prépare le programme `prog` pour le débogage. Le shell GDB apparaît :

```
GNU gdb (GDB) 9.2
...
(gdb)
```

### Commandes GDB essentielles

#### 1. **run** - Exécuter le programme

```
(gdb) run
```

ou avec des arguments :

```
(gdb) run arg1 arg2
```

#### 2. **break** - Placer un point d'arrêt

```
(gdb) break main              # Arrêt au début de main
(gdb) break source.c:42       # Arrêt à la ligne 42 du fichier source.c
(gdb) break function_name     # Arrêt au début d'une fonction
```

Dès qu'un point d'arrêt est déclenché, l'exécution s'arrête et on peut inspecter l'état.

#### 3. **next** - Exécuter la ligne suivante

```
(gdb) next
```

Exécute la ligne actuelle et arrête avant la prochaine.

#### 4. **step** - Entrer dans une fonction

```
(gdb) step
```

Comme `next`, mais si la ligne actuelle est un appel de fonction, `step` rentre **dans** cette fonction.

#### 5. **print** - Afficher la valeur d'une variable

```
(gdb) print variable_name
(gdb) print &variable_name    # Afficher l'adresse
(gdb) print *pointer          # Déréférencer un pointeur
(gdb) print array[i]          # Afficher un élément de tableau
```

#### 6. **info locals** - Voir toutes les variables locales

```
(gdb) info locals
```

#### 7. **backtrace** - Voir la pile d'appels

```
(gdb) backtrace
```

Affiche toutes les fonctions actuellement en exécution (l'historique d'appels).

#### 8. **continue** - Continuer l'exécution

```
(gdb) continue
```

Reprend l'exécution jusqu'au prochain point d'arrêt.

#### 9. **quit** - Quitter GDB

```
(gdb) quit
```

---

### Exemple complet de débogage

```bash
$ gcc -g -Wall source.c -o prog
$ gdb ./prog
(gdb) break main
Breakpoint 1 at 0x1234
(gdb) run
Starting program: ./prog
Breakpoint 1, main () at source.c:5
5       int x = 10;
(gdb) next
6       int y = 20;
(gdb) print x
$1 = 10
(gdb) continue
Program exited normally
(gdb) quit
```

---

## 4. Valgrind - Détection des fuites mémoire

Valgrind surveille **tous les accès mémoire** effectués par un programme et rapporte :
- Les fuites mémoire (mémoire allouée mais jamais libérée)
- Les accès à la mémoire invalide (buffer overflow, use-after-free)
- Les lectures non initialisées

### Installation

```bash
# Sur Ubuntu/Debian
sudo apt-get install valgrind

# Sur macOS
brew install valgrind
```

### Utilisation basique

```bash
valgrind ./prog
```

Valgrind exécute le programme et affiche un rapport détaillé à la fin.

### Rapport Valgrind typique

```
==12345== HEAP SUMMARY:
==12345== total heap usage: 3 allocs, 2 frees, 1,024 bytes allocated
==12345== 
==12345== 512 bytes in 1 blocks are still reachable in loss record 1 of 1
==12345==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==12345==    by 0x1234 (source.c:10)
```

Cela signifie : 512 bytes alloués à la ligne 10 de `source.c` n'ont jamais été libérés (fuite mémoire).

### Flags courants de Valgrind

```bash
# Rapport détaillé
valgrind --leak-check=full ./prog

# Afficher même les petites fuites
valgrind --leak-check=full --show-leak-kinds=all ./prog

# Générer un fichier de rapport
valgrind --leak-check=full --log-file=report.txt ./prog
```

---

## 5. Combiner GDB et Valgrind

### Utiliser Valgrind avec GDB

```bash
valgrind --vgdb=full ./prog &
gdb ./prog
(gdb) target remote | vgdb
```

Cela permet de déboguer tout en surveillant la mémoire.

### Identifier les fuites avec le numéro de ligne

```bash
# Compiler avec símbolos
gcc -g -Wall source.c -o prog

# Valgrind affichera le numéro de ligne précis de la fuite
valgrind --leak-check=full ./prog
```

---

## 6. Points clés

- **Toujours compiler avec `-g`** pour le débogage.
- **GDB** permet de contrôler l'exécution et d'inspecter l'état.
- **Valgrind** détecte les fuites mémoire et les accès invalides.
- Utiliser `break` et `continue` pour naviguer rapidement vers le code intéressant.
- Utiliser `print` et `info locals` pour inspecter les variables.
- Une fuite mémoire est une allocation (malloc) sans correspondance `free`.
- Les adresses mémoire commencent par `0x` en hexadécimal.

---

## 7. Ressources et exercices

### Fichiers de ce dossier

| Fichier | Description |
|---|---|
| `source.c` | Programme complexe pour l'analyse dynamique |
| `prog` | Binaire compilé prêt pour le débogage |
| `gdb_fundamentals.txt` | Notes sur les fondamentaux de GDB |
| `gdb_vsc.txt` | Configuration de GDB pour VS Code |

### Exercices pratiques

1. **Déboguer `source.c`** avec GDB :
   - Placer un breakpoint à `main`
   - Exécuter le programme
   - Afficher les variables locales
   - Observer le flux d'exécution

2. **Détecter les fuites mémoire** avec Valgrind :
   - Exécuter `valgrind ./prog`
   - Lire le rapport HEAP SUMMARY
   - Identifier où les allocations ne sont pas libérées

3. **Corriger les fuites** :
   - Ajouter les `free()` manquants
   - Réexécuter Valgrind pour vérifier

### Commandes rapides

```bash
# Compiler pour débogage
gcc -g -Wall -Wextra source.c -o prog

# Déboguer
gdb ./prog

# Vérifier les fuites
valgrind ./prog

# Rapport complet
valgrind --leak-check=full --show-leak-kinds=all ./prog
```
