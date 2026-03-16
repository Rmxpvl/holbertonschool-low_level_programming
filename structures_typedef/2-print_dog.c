#include <stdio.h>
#include "dog.h"

/**
 * print_dog - prints a struct dog
 * @d: pointer to struct dog to print
 * Description: If an element of d is NULL, print (nil) instead of its value
 * If d is NULL, print nothing
 * Return: void
 */
void print_dog(struct dog *d)
{
if (d == NULL)
return;

printf("%s\n", d->name ? d->name : "(nil)");
printf("%.6f\n", d->age);
printf("%s\n", d->owner ? d->owner : "(nil)");
}
