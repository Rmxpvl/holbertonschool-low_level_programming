#include <stdio.h>

/**
 * main - Print the name of the program
 * @argc: The number of command line arguments
 * @argv: An array of strings containing the command line arguments
 * Description: This program prints the name of the program, followed by a new line.
 * Return: 0
 */

int main(int argc, char *argv[])
{
(void)argc;
printf("%s\n", argv[0]);
return (0);
}
