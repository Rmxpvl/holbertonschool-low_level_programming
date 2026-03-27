#include "main.h"

/**
 * _is_prime_helper - checks whether n is prime using a divisor candidate
 * @n: number to test
 * @divisor: current divisor candidate
 *
 * Return: 1 if n is prime, 0 otherwise
 */
int _is_prime_helper(int n, int divisor)
{
if (divisor > n / divisor)
return (1);

if (n % divisor == 0)
return (0);

return (_is_prime_helper(n, divisor + 1));
}

/**
 * is_prime_number - returns 1 if n is a prime number, else 0
 * @n: number to test
 *
 * Return: 1 if prime, 0 otherwise
 */
int is_prime_number(int n)
{
if (n <= 1)
return (0);

return (_is_prime_helper(n, 2));
}
