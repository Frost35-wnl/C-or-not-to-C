// Nom : main.c
// Author : Frost35-wnl
#include "../include/projectLibrary.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char userChoice = 0;

    do
    {
        system("clear");
        userChoice = 0;
        afficherMenu();
        userChoice = getchar();
        while (getchar() != '\n');
        
        switch (userChoice)
        {
        case '1': 
        {
            transcodage();
            break;
        } 
        default: return 0;
        // case 2: // appeler fonction dans entierRelatif
        // case 3: // appeler fonction dans nombreReel
        // case 'q':
        //     return 0;
        }

    } while (1);
    
    return 0;
}
