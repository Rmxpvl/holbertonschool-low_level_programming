#include "main.h"
#include <stdio.h>

/**
 * afficher_nom_programme - Affiche le nom du programme
 * @argv: Tableau des arguments passés au programme
 * Description: Affiche le nom du fichier grace a argv et printant le array 0 qui contient le nom du programme
 * Return: 0 (succès)
 */
void afficher_nom_programme(char *argv[])
{
    printf("Nom du programme : %s\n", argv[0]);
    return (0);
}
