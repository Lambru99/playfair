#ifndef PLAYFAIR_ENCODEANDDECODE_H
#define PLAYFAIR_ENCODEANDDECODE_H

#include "readAndWrite.h"

void encodeFile(char *fileInputPath, char *fileOutputPath, struct InputKey inputKey, char **matrix);

char *coupleEncode(char , char , char **);

void decodeFile(char *filePath, char *outputFilePath, struct InputKey inputKey, char **matrix);

int columnBack(char , char **);

char *coupleDecode(char , char , char **);

int rowBack(char , char **);

#endif //PLAYFAIR_ENCODEANDDECODE_H

