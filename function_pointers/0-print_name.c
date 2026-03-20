#include <stdio.h>
#include "function_pointers.h"
/**
 * print_name - prints a name using a function pointer
 * @name: name string to print
 * @f: pointer to function used to print the name
 *
 * Return: nothing
 */

void print_name(char *name, void (*f)(char *))
{
    if (name != NULL && f != NULL)
        f(name);
}
