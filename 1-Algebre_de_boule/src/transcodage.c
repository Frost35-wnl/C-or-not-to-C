#include "../include/transcodage.h"
#include "../include/standardLibrary.h"

#define SIZE_OF_LONG sizeof(long)
#define MAX_INPUT_LENGTH SIZE_OF_LONG * 8 + 6

int transcodage()
{
    char *userInput = NULL;
    short userNumberLength = 0;
    short userBaseFrom = 0, userBaseTo = 0;
    long userNumberToBase10 = 0;

    do
    {
        userInput = malloc(MAX_INPUT_LENGTH * sizeof(char));
        printTranscodageMenu();
        getUserInput(userInput);

        if (userNavigation(userInput) == 1) break;
        if (userNavigation(userInput) == 2)
        {
            free(userInput);
            continue;
        }

        if (checkUserInput(userInput) == 1)
        {
            free(userInput);
            system("clear");
            printTranscodageGuide();

            printf("\nTaper 'Entrer' pour continuer : ");
            while (getchar() != '\n')
                ;
            system("clear");

            continue;
        }

        userNumberLength = getUserNumberLength(userInput);

        char *userNumber = NULL;
        userNumber = malloc((userNumberLength + 1) * sizeof(char));
        parseUserInput(userInput, userNumberLength, userNumber, &userBaseFrom, &userBaseTo);

        if (checkValidBase(userBaseFrom, userBaseTo) == 1)
        {
            free(userInput);
            free(userNumber);
            system("clear");
            printf("\n\nWARNING : Il y a au moins une base invalide !\n\n");
            system("sleep 3 && clear");
            continue;
        }

        if (checkValidInputForBase(userNumber, userBaseFrom) == 1)
        {
            free(userInput);
            free(userNumber);
            system("sleep 3 && clear");
            continue;
        }

        userNumberToBase10 = toBase10(userNumber, userNumberLength, userBaseFrom);

        if (userNumberToBase10 < 0) // Check overflow
        {
            free(userInput);
            free(userNumber);
            system("clear");
            printf("\n\nWARNING : Il y a une depassement des capacites le nombre maximum autorise est %.0f en base 10 !\n\n", pow(2, SIZE_OF_LONG * 8 - 1));
            printf("\nTaper 'Entrer' pour continuer : ");
            while (getchar() != '\n')
                ;
            continue;
        }

        printFinalresult(userNumber, userNumberToBase10, userBaseFrom, userBaseTo);
        free(userInput);
        free(userNumber);

    } while (1);

    return 0;
}

void printTranscodageMenu(void)
{
    system("clear");
    printf("\n _______________________________________________ \n");
    printf("|                                               |\n");
    printf("|                  Transcodage                  |\n");
    printf("|                                               |\n");
    printf("|_______________________________________________|\n");
    printf("\n\nVous pouvez transformer un nombre d'une base vers une autre (bases 2, 4, 8, 10, 16)\n");
    printf("\nExemple : (nombre)-(base de départ)-(base du résultat) -- exemple : 12345678-10-16\nTaper 'q' pour quitter\nTaper '..' pour revenir au menu principal");
    printf("\n\n\tVotre choix : ");
}

void getUserInput(char *userInputTemplate)
{
    int i = 0;

    while ((userInputTemplate[i] = getchar()) != '\n')
    {
        i++;
    }

    userInputTemplate[i] = '\0';
}

int userNavigation(char *userInputTemplate)
{
    if (userInputTemplate[0] == 'q' || userInputTemplate[0] == 'Q')
    {
        exit(0);
    }

    if (userInputTemplate[0] == '\0')
    {
        return 2;
    }

    if (userInputTemplate[0] == '.' && userInputTemplate[1] == '.')
    {
        return 1;
    }

    return 0;
}

int checkUserInput(char *userInputTemplate)
{
    int i = 0;

    while ((userInputTemplate[i] != '\0'))
    {
        if (userInputTemplate[i] != '-' && !isdigit(userInputTemplate[i]))
        {
            if ((int)userInputTemplate[i] < 65 || ((int)userInputTemplate[i] > 70 && (int)userInputTemplate[i] < 97) || (int)userInputTemplate[i] > 102)
            {
                return 1;
            }
        }

        i++;
    }

    return 0;
}

void printTranscodageGuide(void)
{
    printf("\n _______________________________________________________________________________________\n");
    printf("|                                                                                       |\n");
    printf("|       Guide Transcodage                                                               |\n");
    printf("|                                                                                       |\n");
    printf("|   Voici les erreurs à éviter pour que le code fonctionne :                            |\n");
    printf("|                                                                                       |\n");
    printf("|       1 - Faites en sorte que les bases soient écrites en deux chiffres               |\n");
    printf("|       2 - Le seul caractère valide est '-' pour séparer les chiffres                  |\n");
    printf("|       3 - Pour les nombres HEX (en base 16), évitez des caractères supérieurs à 'f'   |\n");
    printf("|                                                                                       |\n");
    printf("|                                                                                       |\n");
    printf("|  Note : en base 16, A = 10, B = 11, C = 12, D = 13, E = 14, F = 15                    |\n");
    printf("|_______________________________________________________________________________________|\n\n");
}

void parseUserInput(char *userInputTemplate, short userNumberLength, char *userNumberTemplate, short *baseFrom, short *baseTo)
{
    int i = 0;

    while (i < userNumberLength)
    {
        userNumberTemplate[i] = userInputTemplate[i];
        i++;
    }
    userNumberTemplate[i] = '\0';

    i++;
    *baseFrom = (short)(userInputTemplate[i] - '0') * 10 + (short)(userInputTemplate[i + 1] - '0'); // We need to add 48 for ASCII conversion
    *baseTo = ((short)(userInputTemplate[i + 3] - '0')) * 10 + ((short)(userInputTemplate[i + 4] - '0'));
}

short getUserNumberLength(char *userInputTemplate)
{
    short i = 0;
    while (userInputTemplate[i] != '-')
        i++;
    return i;
}

int checkValidBase(int baseFrom, int baseTo)
{
    short baseFromCheck = 0, baseToCheck = 0;
    short validBaseTab[5] = {2, 4, 8, 10, 16};

    for (int i = 0; i < 5; i++)
    {
        if (baseFrom == validBaseTab[i])
        {
            baseFromCheck = 1;
            break;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (baseTo == validBaseTab[i])
        {
            baseToCheck = 1;
            break;
        }
    }

    return (baseFromCheck && baseToCheck) ? 0 : 1;
}

int checkValidInputForBase(char *userNumberTemplate, int baseFrom)
{
    int i = 0;

    while (userNumberTemplate[i] != '\0')
    {
        if (isalpha(userNumberTemplate[i]) && (baseFrom != 16)) // For HEX number
        {
            system("clear");
            printf("\n\nWARNING : Le nombre entré dépasse la base donnée !\n\n");
            return 1;
        }
        else if (isdigit(userNumberTemplate[i]) && (char)userNumberTemplate[i] - 48 > baseFrom) // For int number
        {
            system("clear");
            printf("\n\nWARNING : Le nombre entré dépasse la base donnée !\n\n");
            return 1;
        }

        i++;
    }

    return 0;
}

long toBase10(char *userNumberTemplate, short userNumberLength, short baseFrom)
{
    long base10 = 0;
    int i = 0;
    int power = 0;

    while (userNumberTemplate[i] != '\0')
    {
        if (isalpha(userNumberTemplate[userNumberLength - i - 1]))
        {
            userNumberTemplate[userNumberLength - i - 1] = toupper(userNumberTemplate[userNumberLength - i - 1]);

            switch (userNumberTemplate[userNumberLength - i - 1])
            {
            case 'A':
                base10 += 10 * pow(baseFrom, power);
                break;
            case 'B':
                base10 += 11 * pow(baseFrom, power);
                break;
            case 'C':
                base10 += 12 * pow(baseFrom, power);
                break;
            case 'D':
                base10 += 13 * pow(baseFrom, power);
                break;
            case 'E':
                base10 += 14 * pow(baseFrom, power);
                break;
            case 'F':
                base10 += 15 * pow(baseFrom, power);
                break;
            }
        }
        else
        {
            base10 += ((char)(userNumberTemplate[userNumberLength - i - 1] - '0')) * pow(baseFrom, power);
        }
        power++;
        i++;
    }

    return base10;
}

void toFinalBase(long base10, short baseTo)
{
    if (base10 < baseTo)
    {
        if (base10 > 9)
        {
            printf("%c", (char)(base10 - 10 + 'A')); // Simple formula to get the ASCII code of base10
        }
        else
        {
            printf("%ld", base10);
        }
    }
    else
    {
        toFinalBase(base10 / baseTo, baseTo);
        long remainder = base10 % baseTo;

        if (remainder > 9) // Special treatment for remain in HEX which is > 9
        {
            printf("%c", (char)(remainder - 10 + 'A')); // Simple formula to get the ASCII code of corresponding remain
        }
        else
        {
            printf("%ld", remainder);
        }
    }
}

void printFinalresult(char *userNumberTemplate, long Base10, short userBaseFrom, short userBaseTo)
{
    int i = 0;
    system("clear");
    printf("\n ___________________________________________________________________________________________________________________________________________\n");
    printf("|                                                                                                                                           |\n");
    printf("|                                                                                                                                           |\n");
    printf("|   Le nombre ");
    while (userNumberTemplate[i] != '\0')
    {
        putchar(userNumberTemplate[i]);
        i++;
    }
    printf(" écrit en base %d que vous avez entrée : ", userBaseFrom);
    toFinalBase(Base10, userBaseTo);
    printf(" en base %d \n", userBaseTo);
    printf("|                                                                                                                                           |\n");
    printf("|                                                                                                                                           |\n");
    printf("|___________________________________________________________________________________________________________________________________________|\n\n");
    printf("\nTaper 'Entrée' pour continuer : ");
    while (getchar() != '\n')
        ;
}
