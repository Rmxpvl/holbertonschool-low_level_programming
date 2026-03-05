#include "main.h"

/**
 * _strcmp - compare deux chaînes de caractères
 * @s1: première chaîne
 * @s2: deuxième chaîne
 *
 * Description: Compare s1 et s2 caractère par caractère.
 * Retourne la différence entre le premier caractère différent
 * ou 0 si les chaînes sont identiques.
 *
 * Return: valeur entière <0, 0 ou >0
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	/* Parcourir les deux chaînes tant que les caractères sont identiques */
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]); /* retourner la différence du premier caractère différent */
		i++;
	}

	/* Si l'une des chaînes se termine, retourner la différence finale */
	return (s1[i] - s2[i]);
}
