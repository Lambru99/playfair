#include <stdlib.h>
#include <string.h>
#include "encodeAndDecode.h"
#include "builder.h"
#include "readAndWrite.h"

#define buffer 100000

/**
 *
 * Restituisce una riga
 * @param c
 * @param matrix
 * @return
 */
int rowBack(char c, char **matrix) {
    for (int row = 0; row < 5; row++)
        for (int column = 0; column < 5; column++)
            if (matrix[row][column] == c)
                return row;
    return -1;
}
/**
 * Restituisce una colonna
 * @param c
 * @param matrix
 * @return
 */
int columnBack(char c, char **matrix) {
    for (int row = 0; row < 5; row++)
        for (int column = 0; column < 5; column++)
            if (matrix[row][column] == c)
                return column;
    return -1;
}


/**
 * Permette di codificare un file da to in input
 * @param fileInputPath 
 * @param fileOutputPath 
 * @param inputKey 
 * @param matrix 
 */

void encodeFile(char *fileInputPath, char *fileOutputPath, struct InputKey inputKey, char **matrix) {
    long fileDimension = dimensionFile(fileInputPath), position = 0;
    while (position < fileDimension) {
        char *message = readMessage(fileInputPath, buffer, &position);
        char *cleanMessage = builder(message, &position, fileInputPath, inputKey);
        free(message);
        char *encodedMessage = (char *) malloc(sizeof(char) * (strlen(cleanMessage) + 1));
        int counter = 0;
        while (*cleanMessage != '\0') {
            char c1 = *cleanMessage++;
            char c2 = *cleanMessage++;
            char *separatedMessage = coupleEncode(c1, c2, matrix);
            encodedMessage[counter++] = separatedMessage[0];
            encodedMessage[counter++] = separatedMessage[1];
            free(separatedMessage);
        }
        encodedMessage[counter] = '\0';
        writeMessage(fileOutputPath, encodedMessage);
            free(encodedMessage);
    }

}
/**
 * Permette di decodificare un messaggio dato in input
 * @param filePath
 * @param outputFilePath
 * @param inputKey
 * @param matrix
 */
void decodeFile(char *filePath, char *outputFilePath, struct InputKey inputKey, char **matrix) {
    long fileDimention = dimensionFile(filePath), position = 0;
    while (position < fileDimention) {
        char *message = readMessage(filePath, buffer, &position);
        char *cleanedMessage = builder(message, &position, filePath, inputKey);
        free(message);

        char *decodedMessage = (char *) malloc(sizeof(char) * (strlen(cleanedMessage) + 1));
        int counter = 0;
        while (*cleanedMessage != '\0') {
            char c1 = *cleanedMessage++;
            char c2 = *cleanedMessage++;
            char *splitMessage = coupleDecode(c1, c2, matrix);
            decodedMessage[counter++] = splitMessage[0];
            decodedMessage[counter++] = splitMessage[1];
            free(splitMessage);
        }
        decodedMessage[counter] = '\0';

        writeMessage(outputFilePath, decodedMessage);
        free(decodedMessage);

    }
}
/**
 * Permette di effettuare una decodifica a coppie secondo il builder playfair
 * @param c1
 * @param c2
 * @param matrix
 * @return
 */
char *coupleDecode(char c1, char c2, char **matrix) {
    int row = rowBack(c1, matrix), column = columnBack(c1, matrix), row2 = rowBack(c2, matrix), column2 = columnBack(c2,
                                                                                                                     matrix);
    char *separatedMessage = (char *) malloc(sizeof(char) * 3);

    if (row == row2) {

        if (column > 0)separatedMessage[0] =  matrix[row][column - 1];
        else separatedMessage[0] =  matrix[row][4];

        if (column2 > 0)separatedMessage[1] = matrix[row2][column2 - 1];
        else separatedMessage[1] = matrix[row2][4];

    } else if (column == column2) {

        if (row > 0)separatedMessage[0] = matrix[row - 1][column];
        else separatedMessage[0] = matrix[4][column];

        if (row2 > 0)separatedMessage[1] = matrix[row2 - 1][column2];
        else separatedMessage[1] = matrix[4][column2];

    } else {

        separatedMessage[0] = matrix[row][column2];
        separatedMessage[1] = matrix[row2][column];

    }
    separatedMessage[2] = '\0';
    return separatedMessage;
}
/**
 * Permette di codificare a coppie di lettere un messaggio
 * @param c1
 * @param c2
 * @param matrix
 * @return
 */
char *coupleEncode(char c1, char c2, char **matrix) {
    int row = rowBack(c1, matrix), column = columnBack(c1, matrix), row2 = rowBack(c2, matrix), column2 = columnBack(c2,
                                                                                                                     matrix);
    char *separatedMessage = (char *) malloc(sizeof(char) * 3);

    if (row == row2) {

        if (column < 4)separatedMessage[0]= matrix[row][column + 1];
        else separatedMessage[0]= matrix[row][0];

        if (column2 < 4)separatedMessage[1] =  matrix[row2][column2 + 1];
        else separatedMessage[1] =  matrix[row2][0];

    } else if (column == column2) {

        if (row < 4)separatedMessage[0] = matrix[row + 1][column];
        else separatedMessage[0] = matrix[0][column];

        if (row2 < 4)separatedMessage[1]= matrix[row2 + 1][column2];
        else separatedMessage[1]= matrix[0][column2];

    } else {

        separatedMessage[0] = matrix[row][column2];
        separatedMessage[1] = matrix[row2][column];

    }
    separatedMessage[2] = '\0';
    return separatedMessage;
}
