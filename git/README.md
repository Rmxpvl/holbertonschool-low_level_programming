# Git – Contrôle de Version

Ce dossier est un guide de référence Git pour la gestion de projets de programmation.

---

## Table des matières

1. [Configuration initiale](#1-configuration-initiale)
2. [Créer et cloner un dépôt](#2-créer-et-cloner-un-dépôt)
3. [Le cycle de travail quotidien](#3-le-cycle-de-travail-quotidien)
4. [Branches](#4-branches)
5. [Synchronisation avec le dépôt distant](#5-synchronisation-avec-le-dépôt-distant)
6. [Inspecter l'historique](#6-inspecter-lhistorique)
7. [Annuler des modifications](#7-annuler-des-modifications)
8. [Points clés](#points-clés)
9. [Erreurs courantes](#erreurs-courantes)

---

## 1. Configuration initiale

À faire **une seule fois** après l'installation de Git :

```bash
git config --global user.name "Ton Prénom Nom"
git config --global user.email "ton@email.com"
git config --global core.editor "nano"    # ou vim, code, etc.
git config --list                          # Vérifier la configuration
```

---

## 2. Créer et cloner un dépôt

```bash
# Initialiser un nouveau dépôt local
git init mon_projet
cd mon_projet

# Cloner un dépôt existant depuis GitHub
git clone https://github.com/utilisateur/depot.git

# Cloner dans un dossier spécifique
git clone https://github.com/utilisateur/depot.git mon_dossier
```

---

## 3. Le cycle de travail quotidien

```
Modifier fichiers → git add → git commit → git push
```

```bash
# 1. Vérifier l'état du dépôt
git status

# 2. Ajouter des fichiers à l'index (staging area)
git add fichier.c              # Ajoute un fichier spécifique
git add .                      # Ajoute tous les fichiers modifiés
git add *.c                    # Ajoute tous les fichiers .c

# 3. Créer un commit
git commit -m "Description claire du changement"

# 4. Envoyer les commits sur le dépôt distant
git push origin main           # Pousse vers la branche main
git push                       # Pousse vers la branche par défaut
```

### Bonnes pratiques pour les messages de commit

```bash
# ✅ Bon message – descriptif et clair
git commit -m "Ajoute la fonction _strlen dans 2-strlen.c"
git commit -m "Corrige le débordement de tableau dans print_array"

# ❌ Mauvais messages
git commit -m "fix"
git commit -m "asdf"
git commit -m "modification"
```

---

## 4. Branches

```bash
# Créer une nouvelle branche
git branch ma-fonctionnalite

# Changer de branche
git checkout ma-fonctionnalite
# ou (Git moderne)
git switch ma-fonctionnalite

# Créer ET basculer vers la nouvelle branche (raccourci)
git checkout -b ma-fonctionnalite

# Lister toutes les branches
git branch                     # Branches locales
git branch -a                  # Toutes les branches (locales + distantes)

# Fusionner une branche dans la branche courante
git checkout main
git merge ma-fonctionnalite

# Supprimer une branche (après fusion)
git branch -d ma-fonctionnalite
```

---

## 5. Synchronisation avec le dépôt distant

```bash
# Récupérer les modifications distantes
git fetch origin               # Télécharge sans fusionner
git pull                       # Télécharge ET fusionne (fetch + merge)
git pull origin main           # Spécifie la branche distante

# Envoyer vers le dépôt distant
git push origin ma-branche     # Première fois pour une nouvelle branche
git push                       # Fois suivantes

# Lier un dépôt distant
git remote add origin https://github.com/user/repo.git
git remote -v                  # Affiche les dépôts distants configurés
```

---

## 6. Inspecter l'historique

```bash
git log                        # Historique complet des commits
git log --oneline              # Historique condensé (une ligne par commit)
git log --oneline --graph      # Visualisation des branches
git log -n 5                   # Les 5 derniers commits
git log --author="Prénom"      # Commits d'un auteur spécifique

git show abc1234               # Détails d'un commit spécifique
git diff                       # Différences non indexées
git diff --staged              # Différences indexées (avant commit)
git diff HEAD~1 HEAD           # Différences entre les 2 derniers commits
```

---

## 7. Annuler des modifications

```bash
# Annuler les modifications non indexées d'un fichier
git restore fichier.c          # (Git moderne)
git checkout -- fichier.c      # (Git classique)

# Retirer un fichier de l'index (unstage)
git restore --staged fichier.c
git reset HEAD fichier.c       # (Git classique)

# Annuler le dernier commit (en gardant les modifications)
git reset --soft HEAD~1

# Annuler le dernier commit (en supprimant les modifications)
git reset --hard HEAD~1        # ⚠️ IRRÉVERSIBLE

# Créer un commit qui annule un commit précédent (sans réécrire l'historique)
git revert abc1234
```

---

## Points clés

- **Ne jamais** faire `git push --force` sur une branche partagée.
- Commiter **souvent** avec des messages clairs.
- Utiliser `.gitignore` pour exclure les fichiers compilés (`*.o`, exécutables).
- `git status` avant chaque `git add` pour vérifier ce qui sera commité.
- Les branches permettent de travailler en parallèle sans risquer la branche principale.
- Un commit = **une** modification logique et cohérente.

### Exemple de `.gitignore` pour C

```gitignore
# Fichiers objets
*.o

# Exécutables (sans extension sur Linux)
mon_programme
calculatrice

# Fichiers de débogage
*.dSYM

# Fichiers temporaires
*~
*.swp
```

---

## Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| `git push` refusé | La branche distante est en avance | Faire `git pull` d'abord |
| Commit sur la mauvaise branche | On a oublié de changer de branche | `git reset --soft HEAD~1` puis changer de branche |
| Fichier compilé commité | Oubli du `.gitignore` | Ajouter au `.gitignore` et `git rm --cached fichier` |
| Conflit de fusion | Deux branches modifient le même fichier | Éditer le fichier pour résoudre, puis `git add` et `git commit` |
| Message de commit vague | Difficile de comprendre l'historique | Écrire des messages descriptifs dès le début |
