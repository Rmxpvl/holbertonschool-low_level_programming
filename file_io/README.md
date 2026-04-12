# File I/O en C - Cours Complet (Basé sur les exercices 0 à 3)

Ce module introduit la gestion de fichiers en C avec les appels système POSIX.
L'objectif est de comprendre la différence entre la bibliothèque standard (stdio) et les appels bas niveau du noyau Linux, puis d'écrire du code robuste avec une vraie gestion d'erreurs.

## 1) Objectifs pédagogiques

A la fin de cette séquence, tu dois savoir :

- Ouvrir un fichier avec open.
- Lire des données avec read.
- Ecrire des données avec write.
- Fermer un descripteur avec close.
- Choisir les bons flags et permissions avec open.
- Gérer correctement les erreurs (valeurs de retour, codes d'erreur, messages sur stderr).
- Construire un petit utilitaire de copie de fichier avec buffer.

## 2) Rappels théoriques

### 2.1 Appels système et descripteurs de fichiers

Un descripteur de fichier (fd) est un entier manipulé par le noyau :

- 0 : entrée standard (STDIN_FILENO)
- 1 : sortie standard (STDOUT_FILENO)
- 2 : erreur standard (STDERR_FILENO)

Quand open réussit, il retourne un fd >= 0.
Quand open échoue, il retourne -1.

Même logique pour read, write, close :

- succès : valeur >= 0
- échec : -1

### 2.2 En-têtes utiles

- fcntl.h : open et flags O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_APPEND...
- unistd.h : read, write, close
- sys/types.h : types comme ssize_t
- stdlib.h : malloc, free, exit
- stdio.h : dprintf (utile pour afficher les erreurs sur stderr)

### 2.3 Types importants

- size_t : taille non signée
- ssize_t : taille signée (permet -1 pour signaler une erreur)

### 2.4 Permissions Unix (rwx)

Exemples utilisés ici :

- 0600 : rw-------
- 0664 : rw-rw-r--

Attention : les permissions passées à open avec O_CREAT s'appliquent lors de la création.
Si le fichier existe déjà, ses permissions ne sont pas modifiées.

## 3) Exercice 0 - Lire et afficher un fichier

Fichier : [Holberton/holbertonschool-low_level_programming/file_io/0-read_textfile.c](Holberton/holbertonschool-low_level_programming/file_io/0-read_textfile.c)

Prototype :

ssize_t read_textfile(const char *filename, size_t letters);

### 3.1 Ce que la fonction doit faire

- Ouvrir filename en lecture seule.
- Lire au plus letters caractères.
- Ecrire ce qui est lu sur STDOUT.
- Retourner le nombre de caractères réellement lus et écrits.
- Retourner 0 en cas d'échec (filename NULL, open/read/write qui échoue, write partiel).

### 3.2 Logique conseillée

1. Vérifier filename.
2. Allouer un buffer de taille letters.
3. open(filename, O_RDONLY)
4. read(fd, buffer, letters)
5. write(STDOUT_FILENO, buffer, bytes_read)
6. Vérifier que bytes_written == bytes_read.
7. free + close.

### 3.3 Pièges fréquents

- Oublier de free le buffer sur un chemin d'erreur.
- Oublier close(fd).
- Considérer write partiel comme succès.

## 4) Exercice 1 - Créer (ou tronquer) un fichier

Fichier : [Holberton/holbertonschool-low_level_programming/file_io/1-create_file.c](Holberton/holbertonschool-low_level_programming/file_io/1-create_file.c)

Prototype :

int create_file(const char *filename, char *text_content);

### 4.1 Exigences

- Retour : 1 succès, -1 échec.
- filename NULL -> -1.
- Créer le fichier si nécessaire.
- Si le fichier existe, le tronquer.
- Ecrire text_content dedans.
- Si text_content est NULL, créer un fichier vide.
- Permissions à la création : 0600 (rw-------).

### 4.2 Flags open

Utiliser :

O_WRONLY | O_CREAT | O_TRUNC

avec mode 0600.

### 4.3 Bon pattern

- Calculer la longueur de text_content manuellement (style Holberton) si non NULL.
- write(fd, text_content, len)
- Vérifier que write renvoie exactement len.
- close(fd) avant de retourner.

## 5) Exercice 2 - Ajouter du texte en fin de fichier

Fichier : [Holberton/holbertonschool-low_level_programming/file_io/2-append_text_to_file.c](Holberton/holbertonschool-low_level_programming/file_io/2-append_text_to_file.c)

Prototype :

int append_text_to_file(const char *filename, char *text_content);

### 5.1 Exigences

- Retour : 1 succès, -1 échec.
- filename NULL -> -1.
- Ne pas créer le fichier s'il n'existe pas.
- text_content NULL : ne rien ajouter.
- Si text_content NULL et fichier accessible en écriture : retourner 1.
- Si fichier absent ou non accessible : -1.

### 5.2 Flags open

Utiliser :

O_WRONLY | O_APPEND

Pas de O_CREAT ici.

### 5.3 Détail subtil

Si text_content est NULL, la longueur vaut 0.
Un write de 0 octet est valide si le fd est bon.

## 6) Exercice 3 - Programme cp

Fichier : [Holberton/holbertonschool-low_level_programming/file_io/3-cp.c](Holberton/holbertonschool-low_level_programming/file_io/3-cp.c)

Usage :

cp file_from file_to

### 6.1 Contraintes clés

- Lire par blocs de 1024 octets.
- Créer file_to avec permissions 0664.
- Si file_to existe : le tronquer.
- Messages d'erreur exacts sur stderr.
- Codes de sortie imposés :
1. 97 : mauvais nombre d'arguments
2. 98 : lecture impossible depuis file_from
3. 99 : écriture impossible vers file_to
4. 100 : close impossible

### 6.2 Stratégie robuste

1. Vérifier argc.
2. Ouvrir source en lecture.
3. Ouvrir destination en écriture/création/troncature.
4. Boucler read(..., 1024) tant que > 0.
5. Ecrire exactement ce qui a été lu.
6. Contrôler chaque erreur immédiatement avec le bon message et code.
7. Fermer les deux fd avec vérification (close peut échouer).

## 7) Tableau récapitulatif des fonctions

1. open(path, flags, mode)
2. read(fd, buffer, count)
3. write(fd, buffer, count)
4. close(fd)
5. dprintf(STDERR_FILENO, ...)

## 8) Erreurs classiques et prévention

1. Ne pas tester les retours de read/write/close
Correction : toujours vérifier, y compris les writes partiels.

2. Fuites mémoire sur retour anticipé
Correction : libérer toutes les ressources sur chaque chemin d'erreur.

3. Mauvais flags open
Correction : adapter les flags à l'énoncé exact (append sans create, etc.).

4. Message d'erreur non conforme
Correction : recopier exactement le format attendu.

5. Oublier que close peut échouer
Correction : traiter close comme une opération critique dans cp.

## 9) Commandes de compilation

Exemples :

gcc -Wall -Wextra -Werror -pedantic -std=gnu89 0-main.c 0-read_textfile.c -o a
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 1-main.c 1-create_file.c -o b
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 2-main.c 2-append_text_to_file.c -o c
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 3-cp.c -o cp

## 10) Mini fiche méthode (checklist avant rendu)

1. Chaque fonction respecte exactement son prototype.
2. Les valeurs de retour sont conformes à l'énoncé.
3. Les erreurs sont toutes gérées.
4. Aucun warning à la compilation stricte.
5. Les permissions demandées sont correctes.
6. Pas de fuite mémoire ni fd non fermé.

## 11) Conclusion

Ces 4 exercices couvrent les bases indispensables du File I/O système en C : lecture, écriture, création, ajout, copie et gestion rigoureuse des erreurs.
Ce sont des compétences directement réutilisables dans des projets plus avancés : logs, outils CLI, parseurs, serveurs, shells et systèmes embarqués.