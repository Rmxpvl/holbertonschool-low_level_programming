#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dog.h"

/**
 * new_dog - creates a new dog
 * @name: name of the dog
 * @age: age of the dog
 * @owner: owner of the dog
 *
 * Return: pointer to new dog (dog_t), or NULL if failure
 */
dog_t *new_dog(char *name, float age, char *owner)
{
dog_t *d;
char *name_copy;
char *owner_copy;

/* allocate memory for struct dog */
d = malloc(sizeof(dog_t));
if (d == NULL)
return (NULL);

/* allocate and copy name */
if (name)
{
name_copy = malloc(strlen(name) + 1);
if (name_copy == NULL)
{
free(d);
return (NULL);
}
strcpy(name_copy, name);
}
else
name_copy = NULL;

/* allocate and copy owner */
if (owner)
{
owner_copy = malloc(strlen(owner) + 1);
if (owner_copy == NULL)
{
free(name_copy);
free(d);
return (NULL);
}
strcpy(owner_copy, owner);
}
else
owner_copy = NULL;

/* assign values */
d->name = name_copy;
d->age = age;
d->owner = owner_copy;

return (d);
}
