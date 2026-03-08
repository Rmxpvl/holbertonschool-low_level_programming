#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * main - Adds positive numbers passed as arguments
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 if success, 1 if error (non-digit argument)
 */
int main(int argc, char *argv[])
{
int sum = 0;
int i, j;

if (argc == 1)  /* No numbers provided */
{
printf("0\n");
return (0);
}

for (i = 1; i < argc; i++)  /* Loop over each argument */
{
for (j = 0; argv[i][j] != '\0'; j++)  /* Check every character */
{
if (!isdigit(argv[i][j]))  /* Non-digit found */
{
printf("Error\n");
return (1);
}
}
sum += atoi(argv[i]);  /* Convert argument to int and add */
}

printf("%d\n", sum);  /* Print total sum */
return (0);
}
