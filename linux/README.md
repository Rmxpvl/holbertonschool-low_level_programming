# Linux – Commandes Essentielles

Ce dossier est une référence rapide des commandes Linux les plus utiles pour un étudiant en programmation C.

---

## Table des matières

1. [Navigation dans le système de fichiers](#1-navigation-dans-le-système-de-fichiers)
2. [Gestion des fichiers et dossiers](#2-gestion-des-fichiers-et-dossiers)
3. [Permissions](#3-permissions)
4. [Compilation C sous Linux](#4-compilation-c-sous-linux)
5. [Processus et système](#5-processus-et-système)
6. [Redirection et pipes](#6-redirection-et-pipes)
7. [Recherche](#7-recherche)
8. [Points clés](#points-clés)
9. [Erreurs courantes](#erreurs-courantes)

---

## 1. Navigation dans le système de fichiers

```bash
pwd                  # Affiche le dossier courant (Print Working Directory)
ls                   # Liste les fichiers du dossier courant
ls -la               # Liste détaillée avec fichiers cachés
cd mon_dossier       # Change de dossier
cd ..                # Remonte d'un niveau
cd ~                 # Retourne au dossier personnel (home)
cd /                 # Va à la racine du système
```

---

## 2. Gestion des fichiers et dossiers

```bash
# Créer
mkdir mon_dossier         # Crée un dossier
mkdir -p a/b/c            # Crée des dossiers imbriqués
touch fichier.c           # Crée un fichier vide (ou met à jour la date)

# Copier / Déplacer / Renommer
cp source.c destination.c # Copie un fichier
cp -r dossier1 dossier2   # Copie un dossier (récursif)
mv ancien.c nouveau.c     # Renomme ou déplace un fichier

# Supprimer
rm fichier.c              # Supprime un fichier
rm -r mon_dossier         # Supprime un dossier et son contenu
rmdir dossier_vide        # Supprime un dossier vide uniquement

# Afficher le contenu
cat fichier.c             # Affiche tout le fichier
head -n 10 fichier.c      # Affiche les 10 premières lignes
tail -n 10 fichier.c      # Affiche les 10 dernières lignes
less fichier.c            # Affichage paginé (q pour quitter)
```

---

## 3. Permissions

Chaque fichier a trois niveaux de permission : **u**tilisateur, **g**roupe, **a**utres.

```bash
ls -l fichier.c
# -rwxr-xr-- 1 user group 1234 mars 1 programme
#  ^^^                              → permissions utilisateur (rwx = lecture, écriture, exécution)
#     ^^^                           → permissions groupe
#        ^^^                        → permissions autres

chmod +x script.sh        # Rend un script exécutable
chmod 644 fichier.c       # rw-r--r-- (lecture/écriture propriétaire, lecture seule pour les autres)
chmod 755 programme       # rwxr-xr-x (exécutable par tous, modifiable uniquement par propriétaire)
```

| Octal | Symbole | Signification         |
|-------|---------|-----------------------|
| 7     | rwx     | lecture + écriture + exécution |
| 6     | rw-     | lecture + écriture    |
| 5     | r-x     | lecture + exécution   |
| 4     | r--     | lecture seule         |
| 0     | ---     | aucune permission     |

---

## 4. Compilation C sous Linux

```bash
# Compilation simple
gcc programme.c -o programme

# Compilation avec tous les avertissements (recommandé Holberton)
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 programme.c -o programme

# Plusieurs fichiers sources
gcc -Wall main.c fonctions.c -o mon_prog

# Vérifier les erreurs sans produire d'exécutable
gcc -Wall -fsyntax-only programme.c

# Exécuter le programme
./programme

# Nettoyer les fichiers compilés
rm -f *.o programme
```

### Options gcc importantes

| Option      | Signification                                    |
|-------------|--------------------------------------------------|
| `-Wall`     | Active tous les avertissements courants           |
| `-Werror`   | Traite les avertissements comme des erreurs       |
| `-Wextra`   | Avertissements supplémentaires                    |
| `-pedantic` | Strict respect de la norme C                     |
| `-std=gnu89`| Utilise la norme C89/C90 avec extensions GNU      |
| `-g`        | Ajoute les informations de débogage (pour gdb)   |
| `-o`        | Spécifie le nom du fichier de sortie             |
| `-E`        | Prétraitement uniquement (génère `.i`)           |
| `-S`        | Compilation uniquement (génère `.s` assembleur)  |
| `-c`        | Compilation + assemblage (génère `.o` objet)     |

---

## 5. Processus et système

```bash
ps aux               # Liste tous les processus
top                  # Moniteur de processus interactif
kill PID             # Termine un processus par son ID
Ctrl+C               # Interrompt le processus en cours
Ctrl+Z               # Suspend le processus en cours

uname -a             # Informations sur le système
whoami               # Affiche l'utilisateur courant
df -h                # Espace disque disponible
free -h              # Mémoire RAM disponible
```

---

## 6. Redirection et pipes

```bash
# Redirection de la sortie
./programme > sortie.txt     # Redirige stdout vers un fichier (écrase)
./programme >> sortie.txt    # Ajoute à la fin du fichier
./programme 2> erreurs.txt   # Redirige stderr

# Pipes – chaîner des commandes
ls -la | grep ".c"           # Filtrer les fichiers .c
cat fichier.c | wc -l        # Compter les lignes d'un fichier
./programme | sort           # Trier la sortie du programme
```

---

## 7. Recherche

```bash
find . -name "*.c"           # Cherche tous les fichiers .c dans le dossier courant
grep "printf" fichier.c      # Cherche "printf" dans un fichier
grep -r "malloc" .           # Cherche récursivement dans tous les fichiers
grep -n "main" fichier.c     # Affiche les numéros de ligne

which gcc                    # Trouve où est installé gcc
man printf                   # Manuel de la fonction printf
man 3 malloc                 # Manuel section 3 (fonctions C)
```

---

## Points clés

- `./` est nécessaire pour exécuter un programme dans le dossier courant.
- Le terminal est **sensible à la casse** : `Fichier.c` ≠ `fichier.c`.
- `Tab` autocomplète les noms de fichiers et commandes.
- `↑` et `↓` naviguent dans l'historique des commandes.
- `Ctrl+L` efface l'écran (équivalent à `clear`).
- `man commande` affiche le manuel de n'importe quelle commande.
- Le code de retour `0` signifie succès ; tout autre valeur signifie erreur.

---

## Erreurs courantes

| Erreur | Explication | Correction |
|--------|-------------|------------|
| `Permission denied` lors de `./prog` | Le fichier n'est pas exécutable | `chmod +x prog` |
| `command not found` | La commande n'existe pas ou le PATH est incorrect | Vérifier l'orthographe ou installer le programme |
| `No such file or directory` | Le chemin n'existe pas | Vérifier avec `ls` et corriger le chemin |
| `rm -rf` accidentel | Suppression irréversible | Toujours vérifier le chemin avant `rm -r` |
| Oubli de `./` avant le programme | Bash cherche dans le PATH système | Toujours préfixer avec `./` |
