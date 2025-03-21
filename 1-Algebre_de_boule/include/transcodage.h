#ifndef TRANSCODAGE_H
#define TRANSCODAGE_H

int transcodage();

void printTranscodageMenu(void);
void printTranscodageGuide(void);
void getUserInput(char *userInputTemplate);

int userNavigation(char *userInputTemplate);
int checkUserInput(char *userInputTemplate);

void parseUserInput(char *userInputTemplate, short userNumberLength, char *userNumberTemplate, short *baseFrom, short *baseTo);
short getUserNumberLength(char *userInputTemplate);
int checkValidBase(int baseFrom, int baseTo);
int checkValidInputForBase(char *userNumberTemplate, int baseFrom);

long toBase10(char *userNumberTemplate, short userNumberLength, short baseFrom);
void toFinalBase(long base10, short baseTo);
void printFinalresult(char *userNumberTemplate, long Base10, short userBaseFrom, short userBaseTo);

#endif