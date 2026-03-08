#include "main.h"

/**
 * main - Affiche le nom du programme
 * @argc: Nombre d'arguments passés au programme
 * @argv: Tableau de chaînes de caractères représentant les arguments, ici 0.
 * Description: Cette fonction affiche le nom du programme, qui est le premier argument passé à la fonction main. Le nom du programme est stocké dans argv[0].
 * Return: 0 (succès)
 */

int main(int argc, char *argv[])
{
    char *Nom_programme = argv[0];  // Stocke le nom du programme
    printf("Nom du programme : %s\n", Nom_programme);
    return 0;
}
