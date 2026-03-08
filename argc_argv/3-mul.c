#include <stdio.h>
#include <stdlib.h>

/**
 * main - Multiplie deux nombres passés en arguments
 * @argc: nombre d'arguments
 * @argv: tableau de chaînes de caractères (arguments)
 * Return: 0 si succès, 1 si erreur
 */
int main(int argc, char *argv[])
{
int Num1, Num2, Result;

if (argc < 3)
{
printf("Error\n");
return 1;
}
if (argc > 3)
{
printf("Error\n");
return 1;
}

Num1 = atoi(argv[1]);
Num2 = atoi(argv[2]);
Result = Num1 * Num2;

printf("%d\n", Result);

return 0;
}
