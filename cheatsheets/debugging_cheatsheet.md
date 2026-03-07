# Aide-mémoire Débogage C – Référence Rapide

## Compilation avec avertissements

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 prog.c -o prog
gcc -g prog.c -o prog_debug    # Avec symboles pour GDB
```

---

## Messages d'erreur gcc fréquents

| Message | Signification | Solution |
|---------|---------------|----------|
| `implicit declaration of function` | Prototype manquant | Inclure le bon `.h` |
| `undefined reference` | Fonction non définie | Ajouter le fichier `.c` |
| `unused variable` | Variable déclarée non utilisée | Utiliser ou supprimer |
| `return type defaults to int` | Type de retour manquant | Ajouter `int` ou `void` |
| `missing terminating character` | Chaîne non fermée | Ajouter `"` ou `'` |

---

## Débogage avec printf

```c
printf("[DEBUG] variable = %d\n", variable);
printf("[DEBUG] pointeur = %p\n", (void *)pointeur);
fprintf(stderr, "[ERREUR] condition inattendue\n");
```

---

## GDB – commandes essentielles

```bash
gdb ./programme          # Lancer GDB
(gdb) run                # Exécuter
(gdb) break main         # Point d'arrêt dans main
(gdb) break 25           # Point d'arrêt ligne 25
(gdb) next               # Prochaine ligne
(gdb) step               # Entrer dans la fonction
(gdb) continue           # Continuer jusqu'au prochain break
(gdb) print variable     # Afficher une variable
(gdb) print *pointeur    # Afficher la valeur pointée
(gdb) backtrace          # Pile d'appels (après crash)
(gdb) info locals        # Toutes les variables locales
(gdb) quit               # Quitter
```

---

## Valgrind – détection d'erreurs mémoire

```bash
valgrind ./programme
valgrind --leak-check=full ./programme
valgrind --track-origins=yes ./programme
```

### Interprétation

```
Invalid read/write   → accès hors limites ou pointeur invalide
Use of uninitialised → variable non initialisée
definitely lost      → fuite mémoire certaine
possibly lost        → fuite mémoire probable
```

---

## Erreurs courantes

| Symptôme | Cause probable | Vérification |
|----------|----------------|--------------|
| Segfault | Pointeur NULL ou hors tableau | `backtrace` dans GDB |
| Résultat faux | Bug logique | Tracer avec printf |
| Boucle infinie | Variable non incrémentée | Vérifier la condition |
| Valeur aléatoire | Variable non initialisée | Initialiser à 0 |
| `free` double | Pointeur libéré deux fois | Mettre à NULL après free |

---

## Checklist de débogage

```
□ Compiler avec -Wall -Werror
□ Vérifier les pointeurs NULL avant déréférencement
□ Vérifier les indices de tableau (0 à n-1)
□ Vérifier l'initialisation des variables
□ Vérifier chaque malloc avec != NULL
□ Vérifier que chaque malloc a un free
□ Passer par Valgrind pour les bugs mémoire
```
