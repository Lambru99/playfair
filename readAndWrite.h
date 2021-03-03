#include <stdio.h>
#ifndef PLAYFAIR_READANDWRITE_H
#define PLAYFAIR_READANDWRITE_H

struct InputKey {
    char *alph;
    char subCharacter;
    char specialCharacter;
    char *key;
};

struct InputKey generateStructureKeyFile(char *);

char findCharacterToSub(char* );

long dimensionFile(char *);

char *readMessage(char *, int , long *);

char readNext(char *, long *);

void writeMessage(char *, char *);

char *generateOutput(char *, char *, char *);

char* readAlpha(FILE *);

char* readKey(FILE *);

char readSubCharacter(FILE *, char );

char readSpecialCharacter(FILE *, char );

#endif //PLAYFAIR_READANDWRITE_H
