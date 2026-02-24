#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * main - Set random number and say positive of not
 * Return: 0 if the program run
 */

int main(void)
{
int n;

srand(time(0));
n = rand() - RAND_MAX / 2;

if (n > 0)
{
printf("%d is positive\n", n);
}
else if (n == 0)
{
printf("%d is zero\n", n);
}
else
{
printf("%d is negative\n", n);
}
return (0);
}
