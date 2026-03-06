Voici un README simple et propre pour ton projet de calculette en C.

Calculator in C
Description

Cette application est une calculatrice simple écrite en C qui permet à l’utilisateur d’effectuer plusieurs opérations mathématiques de base depuis le terminal.

L’utilisateur peut choisir entre :

Addition

Soustraction

Multiplication

Division

Le programme demande ensuite deux nombres et affiche le résultat.

La division gère également :

l'erreur division par zéro

l'affichage entier ou décimal selon le résultat.

Fonctionnalités

Menu interactif dans le terminal

Calcul de :

addition

soustraction

multiplication

division

Gestion de la division par zéro

Affichage intelligent du résultat :

entier si possible

sinon affichage avec 2 décimales

Compilation

Pour compiler le programme :

gcc calculator.c -o calculator
Exécution

Une fois compilé :

./calculator
Exemple d'utilisation
Veuillez saisir une opération :
1 pour addition
2 pour soustraction
3 pour multiplication
4 pour division
0 pour quitter

1
Veuillez saisir le premier nombre :
10
Veuillez saisir le deuxième nombre :
5
Le résultat de votre addition est : 15
Gestion des erreurs

Le programme vérifie si l’utilisateur tente de diviser par zéro.

Exemple :

Erreur : Il est impossible de diviser par zéro ! Baka !
Améliorations possibles

Améliorations intéressantes pour la suite :

Ajouter une boucle pour relancer la calculatrice

Ajouter d’autres opérations :

modulo

puissance

racine carrée

Nettoyer le code en utilisant des fonctions

Ajouter une interface plus robuste pour les entrées utilisateur
