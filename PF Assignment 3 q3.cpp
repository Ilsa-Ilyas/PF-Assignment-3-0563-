#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateEmail(char *Email) {
    if (Email == NULL || strlen(Email) == 0) {
        return 0; 
    }

    char *At = strchr(Email, '@');
    if (At == NULL) {
        return 0;
    }

    if (strchr(At + 1, '@') != NULL) {
        return 0; 
    }

    char *Dot = strchr(At + 1, '.');
    if (Dot == NULL) {
        return 0; 
    }

    return 1;
}

int main() {
    char buffer[256]; 

    printf("Enter your email address: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0) {
            printf("Invalid Email\n");
            return 1;
        }

        if (validateEmail(buffer)) {
            printf("Valid Email\n");
        } else {
            printf("Invalid Email\n");
        }
    } else {
        perror("Error reading input");
        return 1; 
    }

    return 0;
}
