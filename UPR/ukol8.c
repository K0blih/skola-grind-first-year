#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv[]) {
    int oCount = 0;
    int iCount = 0;
    int substrCount = 0;
    int inputFileCount = 0;
    int caseSensitive = 1;
    int file = 0;
    int missingOutput = 0;
    char* inputFile = "0";
    char* outputFile = "0";
    char* substr = "0";

    for (int i =1; i < argc; i++) {

        if (strcmp(argv[i], "-i") == 0) {
            caseSensitive = 0;
            iCount++;
        }
        else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                outputFile = argv[i+1];
                i++;
            }
            else {
                missingOutput++;
                i++;
            }
            oCount++;
        }
        else if (file == 0) {
            inputFile = argv[i];
            inputFileCount++;
            file++;
        }
        else {
            substr = argv[i];
            substrCount++;
        }
    }

    if (iCount > 1) {
        printf("Parameter -i provided multiple times\n");
        return 1;
    }
    if (substrCount > 1 || inputFileCount > 1) {
        printf("Too many parameters provided\n");
        return 1;
    }
    if (strcmp(inputFile, "0") == 0) {
        printf("Input path not provided\n");
        return 1;
    }
    if (oCount > 1) {
        printf("Parameter -o provided multiple times\n");
        return 1;
    }
    if (strcmp(substr, "0") == 0) {
        printf("Needle not provided\n");
        return 1;
    }
    if (missingOutput > 0) {
        printf("Missing output path\n");
        return 1;
    }

    FILE* readFile = fopen(inputFile, "r");
    FILE* writeFile = NULL;
    if (strcmp(outputFile, "0") != 0) {
        writeFile = fopen(outputFile, "w");
    }
    
    char buffer[101];
    while(fgets(buffer, sizeof(buffer), readFile)) {
        if (caseSensitive == 1) {
            if (writeFile == NULL) {
                if (strstr(buffer, substr) != NULL) {
                    printf("%s", buffer);
                }
            }
            else {
                if (strstr(buffer, substr) != NULL) {
                    fprintf(writeFile, "%s", buffer);
                }
            }
        }
        else {
            if (writeFile == NULL) {
                if (strcasestr(buffer, substr) != NULL) {
                    printf("%s", buffer);
                }
            }
            else {
                if (strcasestr(buffer, substr) != NULL) {
                    fprintf(writeFile, "%s", buffer);
                }
            }
        }

    }

    fclose(readFile);
    if (writeFile != NULL) {
        fclose(writeFile);
    }

    return 0;
}