#include <stdio.h>
#include <string.h>

void splitString(const char* str) {
    char* token;
    char copy[strlen(str) + 1];
    strcpy(copy, str);

    token = strtok(copy, " "); // Split by space

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}

int main() {
    const char* input = "Write a function that splits a string";
    splitString(input);
    return 0;
}