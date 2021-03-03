#ifndef PLAYFAIR_BUILDER_H
#define PLAYFAIR_BUILDER_H

#include "readAndWrite.h"

char* builder(char *message, long *position, char *path, struct InputKey inputKey);

void substitutionCharacter(char *message, struct InputKey inputKey);

void toUpperString(char *);

char **createMatrixStructure(struct InputKey );

#endif //PLAYFAIR_BUILDER_H