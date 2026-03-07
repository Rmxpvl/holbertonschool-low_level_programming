# Aide-mémoire Git – Référence Rapide

## Configuration

```bash
git config --global user.name "Prénom Nom"
git config --global user.email "email@example.com"
```

---

## Initialiser / Cloner

```bash
git init                              # Nouveau dépôt local
git clone https://github.com/u/r.git # Cloner un dépôt
```

---

## Cycle quotidien

```bash
git status                            # État du dépôt
git add fichier.c                     # Indexer un fichier
git add .                             # Indexer tout
git commit -m "Message clair"         # Créer un commit
git push                              # Envoyer au serveur distant
git pull                              # Récupérer les modifications
```

---

## Branches

```bash
git branch                            # Lister les branches
git branch ma-branche                 # Créer une branche
git checkout ma-branche               # Changer de branche
git checkout -b ma-branche            # Créer et basculer
git merge ma-branche                  # Fusionner dans la branche courante
git branch -d ma-branche              # Supprimer (après fusion)
```

---

## Historique

```bash
git log                               # Historique complet
git log --oneline                     # Une ligne par commit
git log --oneline --graph             # Visualisation branches
git diff                              # Modifications non indexées
git diff --staged                     # Modifications indexées
git show abc1234                      # Détails d'un commit
```

---

## Annuler

```bash
git restore fichier.c                 # Annuler modifications non indexées
git restore --staged fichier.c        # Désindexer
git reset --soft HEAD~1               # Annuler dernier commit (garde modifs)
git reset --hard HEAD~1               # Annuler dernier commit (⚠️ supprime tout)
git revert abc1234                    # Créer un commit d'annulation
```

---

## Dépôt distant

```bash
git remote -v                         # Voir les dépôts distants
git remote add origin URL             # Ajouter un dépôt distant
git push origin ma-branche            # Pousser une branche
git fetch origin                      # Télécharger sans fusionner
```

---

## .gitignore

```gitignore
*.o           # Fichiers objets
*.out         # Exécutables gcc par défaut
mon_prog      # Exécutable spécifique
*~            # Fichiers temporaires vim
.DS_Store     # Fichiers macOS
```

---

## Bons messages de commit

```
✅ "Ajoute la fonction _strlen dans 2-strlen.c"
✅ "Corrige l'erreur off-by-one dans print_array"
✅ "Implémente la calculatrice de base"

❌ "fix"
❌ "modifications"
❌ "commit"
```
