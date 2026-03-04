#include "main.h"

/**
 * puts2 - prints every other character of a string
 * @str: string to print
 */

void puts2(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        _putchar(str[i]);  // affiche le caractère courant
        i += 2;            // passe au caractère suivant "tous les deux"
    }

    _putchar('\n');        // saut de ligne final
}
