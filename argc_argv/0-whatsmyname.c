#include <stdio.h>

/**
 * main - Print the name of the program
 * @argc: The number of command line arguments
 * @argv: An array of strings containing the command line arguments
 * Description: Ecris le nom du programme.
 * Return: 0
 */

int main(int argc, char *argv[])
{
(void)argc;
printf("%s\n", argv[0]);
return (0);
}
