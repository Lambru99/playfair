#include "builder.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * Permette di aggiustare il messaggio da codificare o decodificare dato in input e di costruire la matrice da esso
 * @param message
 * @param position
 * @param path
 * @param inputKey
 * @return
 */
char* builder(char *message, long *position, char *path, struct InputKey inputKey){
    unsigned int messageDimension = strlen(message);
    char *temp = (char *) malloc(sizeof(char) * (messageDimension + 1));
    int count = 0;
    while (*message != '\0') {
        if (isalpha(*message) != 0)
            temp[count++] = *message;
        else
            temp = realloc(temp, --messageDimension + 1);
        message++;
    }
    temp[count] = '\0';
    substitutionCharacter(temp, inputKey);
    count=0;
    unsigned int newDimension = strlen(temp);
    char *temp2 = (char *) malloc(sizeof(char) * (newDimension + 1));
    while (*temp != '\0') {
        temp2[count++] = *temp;
        temp++;
        if (*temp != '\0') {
            if (temp2[count - 1] != *temp) {
                temp2[count++] = *temp;
                temp++;
            } else {
                temp2 = realloc(temp2, ++newDimension + 1);
                temp2[count++] = inputKey.specialCharacter;
            }
        }
    }
    temp2[count] = '\0';
    if ((strlen(temp2) % 2) != 0) {
        temp2 = realloc(temp2, count + 2);
        char c = readNext(path, position);
        if ((c != -1) && (c != temp2[count - 1]))
            temp2[count++] = c;
        else
            temp2[count++] = inputKey.specialCharacter;
        temp2[count] = '\0';
    }

    return temp2;

}
/**
 * Permette di sostituire con il carattere di sostituzione
 * @param message
 * @param inputKey
 */
void substitutionCharacter(char *message, struct InputKey inputKey) {
    char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lostC;
    for (int i = 0; i < 26; i++) {
        if (strchr(inputKey.alph, alphabet[i]) == NULL)
            lostC = alphabet[i];
    }
    while (*message != '\0') {
        if (*message == lostC)
            *message = inputKey.subCharacter;
        message++;
    }
}
/**
 * Dato un messaggio, questo metodo lo restituisce tutto in maiuscolo
 * @param message
 */
void toUpperString(char *message) {
    while (*message != '\0') {
        *message = (char) toupper(*message);
        message++;
    }


}
/**
 * Crea la struttura della matrice
 * @param inputKey
 * @return
 */
char **createMatrixStructure(struct InputKey inputKey) {
    int position = 0;
    char *text = malloc(25 + sizeof(char) );
    for (int i = 0; i < strlen(inputKey.key); i++) {
        if (isalpha(inputKey.key[i]) != 0) {
            if (strchr(text, inputKey.key[i]) == NULL){
                text[position++] = inputKey.key[i];
            }
        }
    }
    for (int i = 0; i < 25; i++) {
        if (strchr(text, inputKey.alph[i]) == NULL){
            text[position++] = inputKey.alph[i];
        }
    }
    text[position] = '\0';
    position=0;
    char **matrix = (char **) malloc(5 * sizeof(char *));
    for (int i = 0; i < 5; i++) {
        matrix[i] = (char *) malloc(5 * sizeof(char));
    }
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < 5; i++) {
            matrix[k][i] = text[position];
            position++;
        }
    }
    return matrix;
}