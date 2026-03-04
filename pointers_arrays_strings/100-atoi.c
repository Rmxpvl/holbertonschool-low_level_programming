#include "main.h"
#include <stdio.h>

/**
 * _atoi - convert a string to an integer
 * @s: pointer to the string to be converted
 * Return: The integer value represented by the string, or 0 if no number
 */

int _atoi(char *s)
{
int result = 0;
int sign = 1;
int i = 0;
int started = 0;

while (s[i] != '\0')
{
if (s[i] == '-')
sign *= -1;
else if (s[i] == '+' && !started)
;
else if (s[i] >= '0' && s[i] <= '9')
{
result = result * 10 + s[i] - '0';
started = 1;
}
else if (started)
break;
i++;
}
return (result *sign);
}
