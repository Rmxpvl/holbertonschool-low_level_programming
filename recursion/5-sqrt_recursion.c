#include "main.h"

/**
 * _sqrt_helper - finds the natural square root candidate recursively
 * @n: number to evaluate
 * @guess: current candidate
 *
 * Return: natural square root, or -1 if not found
 */
int _sqrt_helper(int n, int guess)
{
if (guess == n / guess && n % guess == 0)
return (guess);

if (guess > n / guess)
return (-1);

return (_sqrt_helper(n, guess + 1));
}

/**
 * _sqrt_recursion - returns the natural square root of a number
 * @n: number to evaluate
 *
 * Return: natural square root, or -1 if none exists
 */
int _sqrt_recursion(int n)
{
if (n < 0)
return (-1);

if (n == 0)
return (0);

return (_sqrt_helper(n, 1));
}
