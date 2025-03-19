#include "../include/transcodage.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void printTranscodageGuide(void);
void getUserInput(char *userInputTemplate);

void userNavigation(char *userInputTemplate);
void checkUserInput(char *userInputTemplate);

void parseUserInput(char *userInputTemplate, short userNumberLength, char *userNumberTemplate, short *baseFrom, short *baseTo);
short getUserNumberLength(char *userInputTemplate);
void checkValidBase(int baseFrom, int baseTo);

long toBase10( char *userNumberTemplate,short userNumberLength, short baseFrom);

int main()
{
    char *userInput = NULL;
    userInput = malloc(sizeof(char));
    short userNumberLength = 0;
    short userBaseFrom = 0, userBaseTo = 0;
    long userNumberToBase10 = 0;

    printTranscodageMenu();
    getUserInput(userInput);

    userNavigation(userInput);
    checkUserInput(userInput);

    userNumberLength = getUserNumberLength(userInput);
    char *userNumber = NULL;
    userNumber = malloc((userNumberLength + 1 ) * sizeof(char));

    parseUserInput(userInput, userNumberLength, userNumber, &userBaseFrom, &userBaseTo);
    checkValidBase(userBaseFrom, userBaseTo);

    userNumberToBase10 = toBase10(userNumber, userNumberLength, userBaseFrom);
    printf("%ld", userNumberToBase10);

    // // Limit the number to 8 bits
    // while (i < USER_MAX_DATA - 1 && (userDataInput[i] = getchar()) != '\n')
    //     i++;
    // userDataInput[i] = '\0';

    // // Check invalid Input
    // checkInvalidInput(userDataInput, &validInput);

    // // Check if it's an HEX number
    // i = 0;
    // while (userDataInput[i] != '-')
    // {
    //     if ((isalpha(userDataInput[i])))
    //         hexNumberCheck = 1;
    //     i++;
    // }
    // numberLength = i;

    // // Calling function based on user number (HEX or not)
    // switch (hexNumberCheck)
    // {
    // case 1: // Call funciton for hex
    //     break;
    // default:
    // {
    //     getUserEntryForInt(userDataInput, numberLength, &userNumber, &userBaseFrom, &userBaseTo);
    //     transcodeIntNumber(userNumber, userBaseFrom, userBaseTo);
    // }
    // break;
    // }
}

void printTranscodageMenu(void)
{
    // system("clear");
    printf("\n\tTranscodage");
    printf("\n\nVous pouvez transformer un nombre depuis une base vers une autre base (base 2, 4, 8, 10, 16)\n");
    printf("\nExemple : (nombre)-(base de depart)-(base du resultat) --exemple : 12345678-02-16\nTaper 'q' pour quitter\nTaper '..' pour revenir au menu principal");
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

void checkUserInput(char *userInputTemplate)
{
    int i = 0;
    int invalidInput = 0;

    while ((userInputTemplate[i] != '\0'))
    {
        if (userInputTemplate[i] != '-' && !isdigit(userInputTemplate[i]))
        {
            if ((int)userInputTemplate[i] < 65 || ((int)userInputTemplate[i] > 70 && (int)userInputTemplate[i] < 97) || (int)userInputTemplate[i] > 102)
            {
                invalidInput = 1;
            }
        }

        i++;
    }

    if (invalidInput == 1)
    {
        system("clear");
        printTranscodageGuide();

        printf("\nTaper 'Entrer' pour continuer : ");
        while (getchar() != '\n')
            ;
        system("clear");

        main(); // TODO A REMPLACER A LA FIN
    }
}

void printTranscodageGuide(void)
{
    printf("---------------------------------------------------------------------------------------\n");
    printf("\n\tGuide Transcodage");
    printf("\n\nVoici les erreurs a eviter pour que le code fonctionne : ");
    printf("\n\t1 - Faites en sorte que les bases soient ecritent en deux digits\n\t2 - Le seul caractere valide est '-' pour separer les chiffres\n\t3 - Pour les nombres HEX (en base 16) eviter des caracteres superieures a 'f'");

    printf("\n\nNote : en base 16 A = 10, B = 11, C = 12, D = 13, E = 14, F = 16\n\n");
    printf("---------------------------------------------------------------------------------------\n\n");
}

void userNavigation(char *userInputTemplate)
{

    if (userInputTemplate[0] == 'q' || userInputTemplate[0] == 'Q' || userInputTemplate[0] == '\n')
    {
        exit(0);
    }

    if (userInputTemplate[0] == '.' && userInputTemplate[1] == '.')
    {
        // go to main
    }
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
    *baseFrom = (short)(userInputTemplate[i] - '0') * 10 + (short)(userInputTemplate[i + 1] - '0');//We need to add 48 for ASCII conversio
    *baseTo = ((short)(userInputTemplate[i + 3] - '0')) * 10 + ((short)(userInputTemplate[i + 4] - '0'));
}

short getUserNumberLength(char *userInputTemplate)
{
    short i = 0;
    while (userInputTemplate[i] != '-')
        i++;
    return i;
}

void checkValidBase(int baseFrom, int baseTo)
{
    short baseFromCheck = 0, baseToCheck = 0;
    short validBaseTab[5] = {2, 4, 8, 10, 16};

    for (int i = 0; i < 5; i++)
    {
        if (baseFrom != validBaseTab[i])
            continue;
        else
        {
            baseFromCheck = 1;
            break;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (baseTo != validBaseTab[i])
            continue;
        else
        {
            baseToCheck = 1;
            break;
        }
    }

    if (!(baseFromCheck && baseToCheck))
    {
        printf("\n\nWARNING : Il y a au moins une base invalide a ete detecte !\n\n");
        main();
    }
}

long toBase10( char *userNumberTemplate, short userNumberLength, short baseFrom)
{
    long base10 = 0;
    int i = 0;
    int power = 0;

    while (userNumberTemplate[i] != '\0')
    {
        if (isalpha(userNumberTemplate[userNumberLength - i - 1]))
        {
            userNumberTemplate[userNumberLength - i - 1] = toupper(userNumberTemplate[userNumberLength - i - 1]);

            switch (userNumberTemplate[i])
            {
            case 'A': base10 += 10 * pow(baseFrom, power);
                break;
            case 'B': base10 += 11 * pow(baseFrom, power);
                break;
            case 'C': base10 += 12 * pow(baseFrom, power);
                break;
            case 'D': base10 += 13 * pow(baseFrom, power);
                break;
            case 'E': base10 += 14 * pow(baseFrom, power);
                break;
            case 'F': base10 += 15 * pow(baseFrom, power);
                break;
            }
        }
        else
        {
            base10 +=  ((char)(userNumberTemplate[userNumberLength - i - 1] - '0')) * pow(baseFrom, power);   
        }
        power++;
        i++;
    }

    return base10;
}

// // Function to print the result for int number
// void transcodeIntNumber(int number, int baseFrom, int baseTo)
// {
//     int base10 = 0;
//     int result = 0;

//     base10 = toBase10(number, baseFrom);
//     result = fromBase10(base10, baseTo);

//     printf("Le nombre %d en base %d ecrit en base %d est %d\n\n", number, baseFrom, baseTo, result);
// }

// // To compute a int number from base 10 to any base
// int fromBase10(int number, int baseTo)
// {
//     int result = 0;
//     int factor = 1;
//     while (number > 0)
//     {
//         result += (number % baseTo) * factor;
//         number /= baseTo;
//         factor *= 10;
//     }

//     return result;
// }

// // Add checking function
// void checkInvalidInput(char *userDataInput, int *validInput)
// {
//     int i = 0;
//     while ((userDataInput[i] != '\0'))
//     {
//         if (userDataInput[i] != '-' && isalpha(userDataInput[i]))
//         {
//             if ((int)userDataInput[i] < 65 || ((int)userDataInput[i] > 70 && (int)userDataInput[i] < 97) || (int)userDataInput[i] > 102)
//             {
//                 *validInput = 1;
//             }
//         }

//         i++;
//     }

//     if (*validInput == 1)
//     {
//         system("clear");
//         afficherGuideTranscodage();
//         system("sleep 5");
//         main();
//     }
// }

// void afficherGuideTranscodage()
// {
//     printf("---------------------------------------------------------------------------------------\n");
//     printf("\n\n\tGuide Transcodage");
//     printf("\n\nVoici les erreurs a eviter pour que le code fonctionne : ");
//     printf("\n\t1 - Faites en sorte que le nombre entre soit compose de 8  caracteres\n\t2 - Le seul caractere valide est '-' pour separer les chiffres\n\t3 - Pour les nombres HEX (en base 16) eviter des caracteres superieures a 'f'");

//     printf("\n\nNote : en base 16 A = 10, B = 11, C = 12, D = 13, E = 14, F = 16\n\n");
//     printf("---------------------------------------------------------------------------------------\n\n");
// }
