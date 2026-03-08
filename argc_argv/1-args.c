#include <stdio.h>

/**
 * main - Print the number of command line arguments
 * @argc: The number of command line arguments
 * @argv: ignored parameter
 * Description: This program prints the number of command line arguments.
 * Return: 0
 */

int main(int argc, char *argv[])
{
(void)argv;
printf("%d\n", argc);
return (0);
}
