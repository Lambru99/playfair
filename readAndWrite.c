#include "readAndWrite.h"
#include "builder.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *slash =
#ifdef _WIN32
        "\\";
#else
        "/";
#endif


/**
* Genera la struct utilizzata per salvare alfabeto, carattere sostitutivo, carattere speciale e chiave di codifica/decodifica
* @param path
* @return
*/
struct InputKey  generateStructureKeyFile(char* path) {
    FILE *in = fopen(path, "r+");
    struct InputKey inputKey;

    inputKey.alph = readAlpha(in);
    char toSub = findCharacterToSub(inputKey.alph);
    inputKey.subCharacter = readSubCharacter(in, toSub);

    if (strchr(inputKey.alph, inputKey.subCharacter) == NULL){
        fprintf(stderr, "\nCarattere sostitutivo non rovato");
        exit(EXIT_FAILURE);
    }
    inputKey.specialCharacter = readSpecialCharacter(in, toSub);
    if (strchr(inputKey.alph, inputKey.specialCharacter) == NULL){
        fprintf(stderr, "\nCarattere speciale non trovato");
        exit(EXIT_FAILURE);
    }
    inputKey.key = readKey(in);
    substitutionCharacter(inputKey.key, inputKey);
    return inputKey;
}

/**
 * Permette di leggere l'alfabeto trovaton all'interno del file key dato input input al programma
 * @param input
 * @return alfabeto
 */
    char* readAlpha(FILE* input){
        char *alphaTemp = (char *) malloc(sizeof(char) * 26);
        char c = (char) toupper( fgetc(input));
        int i = 0;
        while (c != '\n') {
            if (c==EOF){
                fprintf(stderr, "\nFormato del file non corretto!!");
                exit(EXIT_FAILURE);
            }
            if ((isalpha(c) != 0) && (strchr(alphaTemp, c)) == NULL) {
                alphaTemp[i++] = (char) toupper(c);
            }
            c = (char) toupper( fgetc(input));
        }
    alphaTemp[25] = '\0';
        if (i != 25) {
            fprintf(stderr, "\nL'alfabeto non e' di 25 caratteri!!");
            exit(EXIT_FAILURE);
        }

        return alphaTemp;
}


/**
  * Legge il carattere speciale assicurandosi che sia differente dal carattere toSub
 * @param input
 * @param toSub
 * @return
 */
char readSpecialCharacter(FILE* input, char toSub){
    char c;
    do {
        c = (char) fgetc(input);
        if (c==EOF){
            fprintf(stderr, "\n!!ERRORE!! Il formato non è riconosciuto");
            exit(EXIT_FAILURE);
        }
        if (c =='\n'){
            fprintf(stderr, "\nNon e' presente il carattere speciale");
            exit(EXIT_FAILURE);
        }
    } while (isalpha(c)==0 || toupper(c) == toSub);
    char end;
    do{
        end=(char) fgetc(input);
    }while(end != '\n' && end !=EOF);
    return (char) toupper(c);

}
/**
 * Trova il carattere da sostituire con subCharacter della struct
 * @param alphabetKey
 * @return
 */
char findCharacterToSub(char* alphabetKey){
    char alpha[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char cToSub;
    for (int i = 0; i < 26; i++) {
        if (strchr(alphabetKey, alpha[i]) == NULL)
            cToSub = alpha[i];
    }
    return cToSub;
}
/**
 * Calcola la dimenzione del file
 * @param path
 * @return dimenzione
 */
long dimensionFile(char *path) {
    FILE *in = fopen(path, "r+");
    fseek(in, 0, SEEK_END);
    long dimension = ftell(in);
    fclose(in);
    return dimension;
}
/**
 * Legge la chiave presente nel file dato input input al programma
 * @param input
 * @return chiave
 */
char* readKey(FILE* input){
    char c;
    char *keyTemp = (char *) malloc(sizeof(char) * (1));
    c = (char) fgetc(input);
    int i = 0;
    while (c != EOF) {
        if (isalpha(c) != 0) {
            keyTemp = realloc(keyTemp, (strlen(keyTemp) + 2));
            keyTemp[i++] = (char) toupper(c);
        }
        c = (char) fgetc(input);
    }
    keyTemp[i] = '\0';
    return keyTemp;
}
/**
 * Legge il messaggio a gruppi di buffer
 * @param path
 * @param buffer
 * @param position
 * @return
 */
    char *readMessage(char *path, int buffer, long *position) {
        long characterRemaining = dimensionFile(path) - *position;
        long charToRead;
        if (buffer <= characterRemaining)
            charToRead = buffer;
        else charToRead = characterRemaining;

        FILE *in = fopen(path, "r+");
        fseek(in, *position, SEEK_SET);

        char *temp = (char *) malloc(sizeof(char) * (charToRead + 1));
        fread(temp, sizeof(char), charToRead, in);
        temp[charToRead] = '\0';
    toUpperString(temp);

        *position = ftell(in);
        fclose(in);
        return temp;
    }
/**
 * Legge una lettera da aggiungere alla frase bufferizzata da codificare/decodificare
 * @param path
 * @param position
 * @return
 */
    char readNext(char *path, long *position) {
        FILE *in = fopen(path, "r+");
        fseek(in, *position, SEEK_SET);
        char nextChar;
        do {
            nextChar = (char) toupper(fgetc(in));
        } while ((isalpha(nextChar) == 0) && (feof(in) == 0));
        *position = ftell(in);
        fclose(in);
        if (isalpha(nextChar) != 0)
            return nextChar;
        else return -1;
    }
/**
 * Scrive sul file il message passato separando due lettere alla volta
 * @param path
 * @param message
 */
void writeMessage(char *path, char *message) {
    FILE *out = fopen(path, "a+");

    while (*message != '\0') {
        fputc(*message, out);
        message++;
        if (*message != '\0') {
            fputc(*message, out);
            fputc(' ', out);
            message++;
        }
    }

    fclose(out);
}
/**
 * Genera il percorso del file .pf o .dec da creare con all'interno il risultato della codifica o della decodifica
 * @param dir
 * @param fileInitialPath
 * @param extension
 * @return
 */
char *generateOutput(char *dir, char *fileInitialPath, char *extension) {
    char *temp = malloc(sizeof(char) * (strlen(fileInitialPath) + 1));
    strcpy(temp, fileInitialPath);
    char *finalFileName = malloc(sizeof(char) + 1);
    char *ch;
    ch = strtok(temp, slash);
    while (ch != NULL) {
        finalFileName = realloc(finalFileName, strlen(ch) + 1);
        strcpy(finalFileName, ch);
        ch = strtok(NULL, slash);
    }
    strtok(finalFileName, ".");
    free(temp);
    free(ch);
    char *finalPath = (char *) malloc((strlen(dir) + 1) * sizeof(char));
    strcpy(finalPath, dir);
    finalPath = realloc(finalPath, strlen(finalPath) + 3);
    strcat(finalPath, slash);

    finalPath = realloc(finalPath, strlen(finalPath) + strlen(finalFileName) + 1);
    strcat(finalPath, finalFileName);

    finalPath = realloc(finalPath, strlen(finalPath) + strlen(extension) + 1);
    strcat(finalPath, extension);

    return finalPath;
}
/**
 * Legge il carattere sostitutivo e lo confronta con il carattere non presente nell'alfabeto
 * @param input
 * @param cToSub
 * @return
 */
char readSubCharacter(FILE* input, char cToSub){
    char c;

    do {
        c = (char) fgetc(input);
        if (c==EOF){
            fprintf(stderr, "\n!!ERRORE!! Il formato non è riconosciuto");
            exit(EXIT_FAILURE);
        }
        if (c =='\n'){
            fprintf(stderr, "\nCarattere sostitutivo non trovato");
            exit(EXIT_FAILURE);
        }
    } while (isalpha(c)==0 || toupper(c) == cToSub);
    char end;
    do{
        end=(char) fgetc(input);
        if (end==EOF){
            fprintf(stderr, "\n!!ERRORE!! Il formato non è riconosciuto");
            exit(EXIT_FAILURE);
        }
    }while(end != '\n');
    return (char) toupper(c);
}