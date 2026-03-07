# Aide-mémoire Linux – Référence Rapide

## Navigation

```bash
pwd                  # Dossier courant
ls -la               # Lister avec détails et fichiers cachés
cd dossier           # Changer de dossier
cd ..                # Remonter d'un niveau
cd ~                 # Aller au home
```

---

## Fichiers et dossiers

```bash
# Créer
mkdir dossier
touch fichier.c

# Lire
cat fichier.c
head -n 20 fichier.c
tail -n 20 fichier.c
less fichier.c       # paginé (q pour quitter)

# Copier / Déplacer
cp source dest
mv ancien nouveau
cp -r dossier1 dossier2

# Supprimer
rm fichier
rm -r dossier        # ⚠️ IRRÉVERSIBLE
```

---

## Permissions

```bash
chmod +x fichier     # Rendre exécutable
chmod 644 fichier    # rw-r--r--
chmod 755 programme  # rwxr-xr-x
ls -l                # Voir les permissions
```

---

## Compilation C

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 prog.c -o prog
./prog
gcc -g prog.c -o prog_debug    # Avec symboles de débogage
```

---

## Processus

```bash
ps aux               # Tous les processus
top / htop           # Moniteur interactif
kill PID             # Tuer un processus
Ctrl+C               # Interrompre le processus courant
```

---

## Redirection et pipes

```bash
./prog > sortie.txt         # Rediriger stdout
./prog >> sortie.txt        # Ajouter à la fin
./prog 2> erreurs.txt       # Rediriger stderr
./prog > tout.txt 2>&1      # Rediriger stdout ET stderr
ls *.c | wc -l              # Compter les fichiers .c
cat fichier | grep "mot"    # Filtrer
```

---

## Recherche

```bash
find . -name "*.c"           # Tous les .c dans l'arborescence
grep "mot" fichier           # Chercher dans un fichier
grep -r "mot" .              # Chercher récursivement
grep -n "main" fichier.c     # Avec numéros de ligne
which gcc                    # Trouver la commande gcc
```

---

## Manuel

```bash
man printf          # Manuel de printf (shell)
man 3 printf        # Manuel section 3 (fonctions C)
man 3 malloc        # Manuel de malloc
```

---

## Raccourcis terminal

| Raccourci | Action                     |
|-----------|----------------------------|
| `Tab`     | Autocomplétion             |
| `↑` / `↓` | Historique des commandes   |
| `Ctrl+C`  | Interrompre le processus   |
| `Ctrl+Z`  | Suspendre le processus     |
| `Ctrl+L`  | Effacer l'écran            |
| `Ctrl+D`  | Fin de fichier / quitter   |
