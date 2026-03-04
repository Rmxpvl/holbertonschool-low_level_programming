#include "main.h"

/**
 * puts_half - prints the second half of a string
 * @str: string to print
 *
 * Description: prints the last n characters of a string,
 * where n = (length + 1) / 2 if length is odd, else n = length / 2.
 */
void puts_half(char *str)
{
    int len = 0;
    int start;
    int i;

    /* calculer la longueur */
    while (str[len] != '\0')
        len++;

    /* point de départ de la seconde moitié */
    start = (len + 1) / 2;

    /* afficher chaque caractère de la seconde moitié */
    for (i = start; i < len; i++)
        _putchar(str[i]);

    /* saut de ligne final */
    _putchar('\n');
}
