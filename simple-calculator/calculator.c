#include <stdio.h>

/**

 */

 int main(void)
{
int user_choice = 0;
int num1, num2, result;

 while (user_choice != 0)
{

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
	printf("Le résultat de votre addition est : %d", result);
}
else if (user_choice == 2)
{
	printf("Veuillez saisir le premier nombre :\n");
	scanf("%d", &num1);
	printf("Veuillez saisir le deuxième nombre :\n");
	scanf("%d", &num2);
	result = num1 - num2;
	printf("Le résultat de votre soustraction est : %d", result);
}
else if (user_choice == 3)
{
	printf("Veuillez saisir le premier nombre :\n");
	scanf("%d", &num1);
	printf("Veuillez saisir le deuxième nombre :\n");
	scanf("%d", &num2);
	result = num1 * num2;
	printf("Le résultat de votre multiplication est : %d", result);
}
else if (user_choice == 4)
{
    printf("Veuillez saisir le premier nombre :\n");
    scanf("%d", &num1);
    printf("Veuillez saisir le deuxième nombre :\n");
    scanf("%d", &num2);

    if (num2 == 0)
    {
        printf("Erreur : Il est impossible de diviser par zéro ! Baka !\n");
    }
    else
    {
        result = num1 / num2;
        printf("Le résultat de votre division est : %d\n", result);
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
}
return (0);
}
