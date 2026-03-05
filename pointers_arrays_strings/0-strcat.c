#include "main.h"

/**
 * _strcat - concatène la chaîne src à la fin de dest
 * @dest: chaîne de destination (doit avoir assez de place)
 * @src: chaîne source à ajouter
 * Description: Cette fonction ajoute la chaîne src à la fin
 * de la chaîne dest, en écrasant le caractère nul final
 * de dest, puis ajoute un caractère nul à la fin.
 * Retourne un pointeur vers dest.
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
char *ptr = dest; /* pointeur pour parcourir dest */

/* avancer jusqu'à la fin de dest */
while (*ptr != '\0')
ptr++;

/* copier les caractères de src à la fin de dest */
while (*src != '\0')
{
*ptr = *src;
ptr++;
src++;
}

/* ajouter le caractère nul final */
*ptr = '\0';

return (dest);
}
