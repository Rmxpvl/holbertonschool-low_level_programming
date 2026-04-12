# Listes Simplement Chaînées (Singly Linked Lists)

## 📚 Objectifs d'Apprentissage

- Comprendre la structure d'une liste simplement chaînée
- Implémenter les opérations fondamentales (print, len, add, free)
- Manipuler les pointeurs `next` pour parcourir et modifier la liste
- Gérer la mémoire dynamique avec `malloc` et `free`

## 📂 Fichiers

| Fichier | Description |
|---------|-------------|
| `lists.h` | Header avec les prototypes et la définition de la structure |
| `0-print_list.c` | Affiche tous les éléments d'une liste |
| `1-list_len.c` | Retourne le nombre d'éléments d'une liste |
| `2-add_node.c` | Ajoute un nœud au début de la liste |
| `3-add_node_end.c` | Ajoute un nœud à la fin de la liste |
| `4-free_list.c` | Libère toute la mémoire d'une liste |

## 🔧 Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o singly
```