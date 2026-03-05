#include "main.h"

/**
 * _strncat - concatène au maximum n caractères de src à la fin de dest
 * @dest: chaîne de destination (doit avoir assez de place)
 * @src: chaîne source à ajouter
 * @n: nombre maximum de caractères à copier depuis src
 *
 * Description: La fonction ajoute au plus n caractères de src
 * à la fin de dest, en écrasant le caractère nul final de dest.
 * Un caractère nul est ajouté à la fin de la chaîne résultante.
 * Retourne un pointeur vers dest.
 *
 * Return: dest
 */
char *_strncat(char *dest, char *src, int n)
{
char *ptr = dest; /* pointeur pour parcourir dest */
int i;

/* avancer jusqu'à la fin de dest */
while (*ptr != '\0')
ptr++;

/* copier au plus n caractères de src */
for (i = 0; i < n && src[i] != '\0'; i++)
{
ptr[i] = src[i];
}

/* ajouter le caractère nul final */
ptr[i] = '\0';

return (dest);
}
