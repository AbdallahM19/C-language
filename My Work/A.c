#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a linked list node
struct PathNode {
    char* directory;
    struct PathNode* next;
};

// Function to add a new directory to the linked list
void addDirectoryToList(struct PathNode** head, const char* directory) {
    struct PathNode* newNode = (struct PathNode*)malloc(sizeof(struct PathNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    newNode->directory = strdup(directory);
    newNode->next = *head;
    *head = newNode;
}

// Function to print the linked list of directories
void printPathList(const struct PathNode* head) {
    while (head != NULL) {
        printf("%s\n", head->directory);
        head = head->next;
    }
}

int main() {
    // Get the PATH environment variable
    char* path = getenv("PATH");

    if (path == NULL) {
        printf("PATH environment variable is not set.\n");
        return 0;
    }

    struct PathNode* pathList = NULL;
    char* token = strtok(path, ":");

    // Build the linked list
    while (token != NULL) {
        addDirectoryToList(&pathList, token);
        token = strtok(NULL, ":");
    }

    // Print the linked list
    printf("Directories in PATH variable (linked list):\n");
    printPathList(pathList);

    // Free memory used by the linked list
    while (pathList != NULL) {
        struct PathNode* current = pathList;
        pathList = pathList->next;
        free(current->directory);
        free(current);
    }

    return 0;
}