#include "main.h"

/**
 * print_triangle - prints a right-aligned triangle
 * @size: size of the triangle
 *
 * Description: prints a triangle of '#' characters using _putchar.
 * If size is 0 or negative, only prints a newline.
 */
void print_triangle(int size)
{
    int i, j;

    if (size <= 0)
    {
        _putchar('\n');
        return;
    }

    for (i = 1; i <= size; i++)
    {
        /* print spaces */
        for (j = 1; j <= size - i; j++)
            _putchar(' ');

        /* print # */
        for (j = 1; j <= i; j++)
            _putchar('#');

        _putchar('\n');
    }
}
