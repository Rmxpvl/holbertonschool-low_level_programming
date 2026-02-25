#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - prints the alphabet in lowercase without letters q and e
 *
 * Return: Always 0
 */

int main(void)
{

char c = 'a';

while (c <= 'z')
{
    if(c !='q' && 'e')
putchar(c);
c++;
putchar('\n')
}