#include "main.h"
#include <stdio.h>
/**
 * main - The code assign n to 402 first then turn it into 98 using the function reset_to_98
 * reset_to_98 - Turn the variable into 98
 * Return: Always 0.
 */

void reset_to_98(int *n)
{
*n = 98;
}
int main(void)
{
int n;

n = 402;
printf("n=%d\n", n);
reset_to_98(&n);
printf("n=%d\n", n);

return 0;
}
