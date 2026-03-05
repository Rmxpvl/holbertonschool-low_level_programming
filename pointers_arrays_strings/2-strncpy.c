#include "main.h"

/**
 * _strncpy - copie au maximum n caractères de src dans dest
 * @dest: chaîne de destination
 * @src: chaîne source
 * @n: nombre maximum de caractères à copier
 *
 * Description: Si src contient moins de n caractères, le reste
 * de dest est rempli avec des '\0'. La fonction retourne dest.
 *
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
int i;

/* Copier les caractères de src dans dest */
for (i = 0; i < n && src[i] != '\0'; i++)
{
dest[i] = src[i];
}

/* Remplir le reste de dest avec des '\0' si src est plus court que n */
for (; i < n; i++)
{
dest[i] = '\0';
}

return (dest);
}
