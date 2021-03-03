
#include "readAndWrite.h"
#include "builder.h"
#include "encodeAndDecode.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printAnExemple() {
    printf("playfair <encode|decode> <keyfile> <outputdir> <file1> ... <filen>\n");

}

int main(int argc, char **argv) {
    if (argc==2 && (strcmp(argv[1],"-h")==0 || strcmp(argv[1],"--help")==0)){
        printf("\n\nPLAYFAIR è un programma per cifrare e decifrare messaggi data una chiave ed un alfabeto.\n"
               "Comando di esempio per eseguire il programma:\n\n");
        printAnExemple();
        printf("\n\n\nplayfair\t\tEseguibile del programma a cui passare paramentri.\n\n"
               "encode,decode\t\tParametro per codificare,decodificare un messaggio.\n\n"
               "keyfile\t\t\tPercorso della file chiave contenente alfabeto, carattere sostitutivo, carattere speciale e chiave di cifratura.\n\n"
               "outputdir\t\tPercorso della cartella di destinazione del file cifrato/decifrato con estenzione \".pf/.dec\".\n\n"
               "file1...filen\t\tPercorsi dei file da codificare/decodificare.\n\n"
               "-h,\t--help\t\tStampa delle informazioni.\n\n\n\n");
        return 0;
    }else if (argc < 5 ) {
            printf("Numero parametri errato! (necessari 5, inseriti: %d)!\nPer ulteriori info \"-h o --help\"\n\n", argc);
        printAnExemple();
        return -1;
    }

    struct InputKey inputKey = generateStructureKeyFile(argv[2]);
    char **matrix = createMatrixStructure(inputKey);
    if (strcmp(argv[1], "encode") == 0) {
        for (int i = 4; i < argc; i++) {
            encodeFile(argv[i], generateOutput(argv[3], argv[i], ".pf"), inputKey, matrix);
        }
        free(matrix);
        return 0;
    }else if (strcmp(argv[1], "decode") == 0) {
        for (int i = 4; i < argc; i++) {
            decodeFile(argv[i], generateOutput(argv[3], argv[i], ".dec"), inputKey, matrix);
        }
        free(matrix);
        return 0;
    }else printf("Errore %s!\n", argv[1]);
    printAnExemple();
    return 0;
}
