#include <stdio.h>

/**

 */

int main(void)
{
int user_choice;
int num1, num2, result;
int numA, numB;
float result_division;

	printf(" Veuillez saisir une opération :\n");
	printf(" 1 pour addition\n");
	printf(" 2 pour soustraction\n");
	printf(" 3 pour multiplication\n");
	printf(" 4 pour division\n");
	printf(" 0 pour quitter\n");
	scanf("%d", &user_choice);

if (user_choice == 1)
{
	printf("Veuillez saisir le premier nombre :\n");
	scanf("%d", &num1);
	printf("Veuillez saisir le deuxième nombre :\n");
	scanf("%d", &num2);
	result = num1 + num2;
	printf("Le résultat de votre addition est : %d\n", result);
}
else if (user_choice == 2)
{
	printf("Veuillez saisir le premier nombre :\n");
	scanf("%d", &num1);
	printf("Veuillez saisir le deuxième nombre :\n");
	scanf("%d", &num2);
	result = num1 - num2;
	printf("Le résultat de votre soustraction est : %d\n", result);
}
else if (user_choice == 3)
{
	printf("Veuillez saisir le premier nombre :\n");
	scanf("%d", &num1);
	printf("Veuillez saisir le deuxième nombre :\n");
	scanf("%d", &num2);
	result = num1 * num2;
	printf("Le résultat de votre multiplication est : %d\n", result);
}
else if (user_choice == 4)
{
    printf("Veuillez saisir le premier nombre :\n");
    scanf("%d", &numA);
    printf("Veuillez saisir le deuxième nombre :\n");
    scanf("%d", &numB);

    if (numB == 0)
    {
        printf("Erreur : Il est impossible de diviser par zéro ! Baka !\n");
	return (0);
    }
    else
    {
        result_division = (float)numA / (float)numB;
    }
    if (result_division == (int)result_division)
    {
	printf("Le résultat de votre division est un entier : %d\n", (int)result_division);
    }
    else
    {
	printf("Le résultat de votre division est : %.2f\n", result_division);
}
}
else if (user_choice == 0)
{
	printf("Tu me quittes déja ?\n");
}
else
{
	printf("Choix invalide, veuillez réessayer.\n");
}
return (0);
}
