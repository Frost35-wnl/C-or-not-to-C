//Nom : main.c
//Author : Frost35-wnl
#include "../include/affichage.h"
#include <stdio.h>

int main(){
    char userChoice = 0;

    afficherMenu();
    userChoice = getchar();
    switch (userChoice)
    {
    case 1 : //appeler fonction dans transcodage
        break;
    case 2 : //appeler fonction dans entierRelatif
        break;
    case 3 : //appeler fonction dans nombreReel
        break;
    case 'q': return 0;
    }
}


