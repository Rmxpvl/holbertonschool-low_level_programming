#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - Program that look for last digit number and determine if 0 or more
 * Return: 0 if the program run
 */

int main(void)
{
	int n;

	srand(time(0));
	n = rand() - RAND_MAX / 2;

if (last_digit == 0)
{
printf("Last digit of %d is %d and is 0\n", n, last digit);
}
else if (last_digit > 5)
{
printf("Last digit of %d is %d and is greater than 5\n", n, last digit);
}
else
{
printf("Last digit of %d is %d and is less than - and not 0\n", n, last digit);
}
return (0);
}
