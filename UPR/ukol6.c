#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int lowerCount(char *buffer);
int upperCount(char *buffer);
int spaceCount(char *buffer);
void ltrim(char *buffer);
void rtrim(char *buffer);
void changeUpper(char *token);
void concatWithSpace(char *result, char *token);

int main() {
    
    char strs[10];
    fgets(strs, sizeof(strs), stdin);
    int lines = atoi(strs);

    // int c;
    // while ((c = getchar()) != '\n');
    
    for (int i = 0; i < lines; i++) {
        char buffer[51];
        char copyBuffer[51];
        char result[51];
        memset(result, 0, sizeof(result));
        memset(copyBuffer, 0, sizeof(copyBuffer));
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);

        strcpy(copyBuffer, buffer);
        ltrim(copyBuffer);
        rtrim(copyBuffer);

        char *token = strtok(copyBuffer, " ");
        while(token) {
            changeUpper(token);
            concatWithSpace(result, token);
            token = strtok(NULL, " ");
        }

        printf("%s\n", result);
        printf("lowercase: %d -> %d\n", lowerCount(buffer), lowerCount(result));
        printf("uppercase: %d -> %d\n", upperCount(buffer), upperCount(result));
        printf("spaces: %d -> %d\n", spaceCount(buffer), spaceCount(result));

        if (i < lines-1) {
        printf("\n");
        }
    }

    return 0;
}

int lowerCount(char *buffer) {
    int j = 0;
    int count = 0;
    while (buffer[j] != '\0') {
        if (islower(buffer[j])) {
            count++;
        }
        j++;
    }
    return count;
}

int upperCount(char *buffer) {
    int j = 0;
    int count = 0;
    while (buffer[j] != '\0') {
        if (isupper(buffer[j])) {
            count++;
        }
        j++;
    }
    return count;
}

int spaceCount(char *buffer) {
    int j = 0;
    int count = 0;
    while (buffer[j] != '\0') {
        if (buffer[j] == ' ') {
            count++;
        }
        j++;
    }
    return count;
}

void ltrim(char *buffer) {
    char *start = buffer;
    
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    
    if (start != buffer) {
        memmove(buffer, start, strlen(start) + 1);
    }
}

void rtrim(char *buffer) {
    size_t len = strlen(buffer);
    if (len == 0) return;

    char *back = buffer + len - 1;

    while (back >= buffer && isspace((unsigned char)*back)) {
        back--;
    }
    
    *(back + 1) = '\0';
}

void changeUpper(char *token) {
    int lowerCount = 0;
    int length = (int)strlen(token);

    for (int i = 0; i < length; i++) {
        if (islower(token[i])) {
            lowerCount++;
        }
    }
    if (lowerCount == length) {
        for (int i = 0; i < length; i++) {
            token[i] = (char)toupper(token[i]);
        }
    }
    else {
        token[0] = (char)toupper(token[0]);
        for (int i = 1; i < length; i++) {
            token[i] = (char)tolower(token[i]);
        }
    }

    int j = 1;
    for (int i = 1; i < length; i++) {
        if (token[i] != token[i - 1]) {
            token[j] = token[i];
            j++;
        }
    }
    token[j] = '\0';
}

void concatWithSpace(char *result, char *token) {
    if (result[0] != '\0') {
        strcat(result, " ");
    }
    strcat(result, token);
}