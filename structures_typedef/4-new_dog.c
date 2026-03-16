#include "dog.h"
#include <stdlib.h>

/

_strlen - returns the length of a string
@s: string
Return: length*/
int _strlen(char *s)
{
int i = 0;

while (s[i])
i++;
return (i);
}

/

_strcpy - copies a string
@dest: destination
@src: source
Return: dest*/
char _strcpy(chardest, char *src)
{
int i = 0;

while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = '\0';
return (dest);
}

/**
 
new_dog - creates a new dog
@name: name of the dog
@age: age of the dog
@owner: owner of the dog*
Return: pointer to new dog, or NULL if it fails*/
dog_t new_dog(charname, float age, char owner)
{
dog_td;

if (name == NULL || owner == NULL)
return (NULL);

d = malloc(sizeof(dog_t));
if (d == NULL)
return (NULL);

d->name = malloc(_strlen(name) + 1);
if (d->name == NULL)
{
free(d);
return (NULL);
}

d->owner = malloc(_strlen(owner) + 1);
if (d->owner == NULL)
{
free(d->name);
free(d);
return (NULL);
}

_strcpy(d->name, name);
_strcpy(d->owner, owner);
d->age = age;

return (d);
}
