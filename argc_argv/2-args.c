#include <stdio.h>

/**
 * main - Print all command line arguments
 * @argc: The number of command line arguments
 * @argv: An array of strings containing the command line arguments
 * Description: This program prints all command line arguments, one per line.
 * Return: 0
 */

int main(int argc, char *argv[])
{
int i;

for (i = 0; i < argc; i++)
{
printf("%s\n", argv[i]);
}

return (0);
}
