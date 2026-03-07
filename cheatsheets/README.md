# Aide-Mémoire – Fiches de Référence Rapide

Ce dossier contient des fiches de révision condensées pour une consultation rapide pendant le développement.

---

## Fiches disponibles

| Fiche | Description |
|-------|-------------|
| [c_cheatsheet.md](./c_cheatsheet.md) | Synthèse du langage C : types, pointeurs, tableaux, fonctions, I/O |
| [linux_cheatsheet.md](./linux_cheatsheet.md) | Commandes Linux essentielles : navigation, fichiers, compilation, processus |
| [git_cheatsheet.md](./git_cheatsheet.md) | Commandes Git : commit, branches, historique, annulation |
| [debugging_cheatsheet.md](./debugging_cheatsheet.md) | Débogage : gcc, GDB, Valgrind, erreurs courantes |

---

## Utilisation

Ces fiches sont conçues pour être consultées **rapidement** pendant une session de travail, sans avoir à lire une documentation complète.

Pour des explications détaillées avec exemples, consulter les dossiers thématiques :
- [`../c_programming/`](../c_programming/) – Programmation C détaillée
- [`../linux/`](../linux/) – Linux détaillé
- [`../git/`](../git/) – Git détaillé
- [`../debugging/`](../debugging/) – Débogage détaillé
- [`../memory_management/`](../memory_management/) – Gestion mémoire détaillée

---

## Points clés

- Ces fiches sont des **résumés condensés** — pour apprendre un sujet, consulter les dossiers thématiques correspondants.
- En révision, utiliser les fiches comme **check-list** : si un point n'est pas immédiatement compris, approfondir dans le dossier thématique.
- La fiche C couvre les **types**, **pointeurs**, **fonctions**, **I/O** — les bases absolues à maîtriser.
- La fiche Git couvre les commandes du quotidien : `commit`, `push`, `pull`, `branch`, `merge`.
- La fiche Linux couvre la navigation, la gestion de fichiers et la compilation.
- La fiche débogage résume les outils essentiels : `gcc -Wall`, `gdb`, `valgrind`.

---

## Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| Consulter les fiches sans les dossiers thématiques | Les fiches manquent d'explications et d'exemples | Utiliser les fiches pour la **révision rapide**, les dossiers pour **apprendre** |
| Ne pas inclure `<stdio.h>` | `printf`/`scanf` sont indisponibles | Toujours inclure le bon en-tête |
| Confondre `git add` et `git commit` | `add` sélectionne les fichiers, `commit` enregistre le snapshot | `git add .` puis `git commit -m "message"` |
| Utiliser `valgrind` sur un binaire non compilé avec `-g` | Les informations de ligne sont absentes | Compiler avec `gcc -g` pour le débogage |
