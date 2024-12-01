#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(char*** speciesSupplies, int n, int m, int len);
void display(char*** speciesSupplies, int n, int m);
void deleteSpeice(char*** speciesSupplies, int* n, int m);
void update(char*** speciesSupplies, int n, int m);

int main() {
    int n, m, len = 50;

    printf("Welcome To Pets in Heart\n");
    printf("\nEnter # of Species: ");
    scanf("%d", &n);
    printf("\nEnter # of Supplies: ");
    scanf("%d", &m);
    getchar();

    char*** speciesSupplies = (char***)malloc(n * sizeof(char**));
    if (speciesSupplies == NULL) {
        printf("\nMemory alloc failed\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        speciesSupplies[i] = (char**)malloc((m + 1) * sizeof(char*));
        if (speciesSupplies[i] == NULL) {
            printf("\nMemory alloc failed\n");
            exit(1);
        }
        for (int j = 0; j <= m; j++) {
            speciesSupplies[i][j] = (char*)malloc(len * sizeof(char));
            if (speciesSupplies[i][j] == NULL) {
                printf("\nMemory alloc failed\n");
                exit(1);
            }
        }
    }

    add(speciesSupplies, n, m, len);

    display(speciesSupplies, n, m);

    int exitProgram = 0;
    while (!exitProgram) {
        int choice;
        printf("\n1 for delete, 2 for update, 3 for display inventory, 4 for exit: ");
        scanf("%d", &choice);
        getchar();  
        switch (choice) {
            case 1:
                deleteSpeice(speciesSupplies, &n, m);
                break;
            case 2:
                update(speciesSupplies, n, m);
                break;
            case 3:
                display(speciesSupplies, n, m);
                break;
            case 4:
                printf("\nBye bye :)\n");
                exitProgram = 1;
                break;
            default:
                printf("\nInvalid choice!");
        }
    }

    printf("\nCleaning memory\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            free(speciesSupplies[i][j]);
        }
        free(speciesSupplies[i]);
    }
    free(speciesSupplies);
    printf("\nMemory cleaned.\n");

    return 0;
}

void add(char*** speciesSupplies, int n, int m, int len) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter name of specie %d: ", i + 1);
        fgets(speciesSupplies[i][0], len, stdin);
        speciesSupplies[i][0][strcspn(speciesSupplies[i][0], "\n")] = '\0'; 

        for (int j = 1; j <= m; j++) {
            printf("Enter supply %d for species %d: ", j, i + 1);
            fgets(speciesSupplies[i][j], len, stdin);
            speciesSupplies[i][j][strcspn(speciesSupplies[i][j], "\n")] = '\0'; 
        }
    }
}

void display(char*** speciesSupplies, int n, int m) {
    printf("\n--- Inventory ---\n");
    for (int i = 0; i < n; i++) {
        printf("Species %d: %s\n", i + 1, speciesSupplies[i][0]);  
        printf("Supplies:\n");
        for (int j = 1; j <= m; j++) {
            printf("  Supply %d: %s\n", j, speciesSupplies[i][j]);  
        }
    }
    printf("-----------------\n");
}

void deleteSpeice(char*** speciesSupplies, int* n, int m) {
    if (*n == 0) {
        printf("\nNo species to delete.\n");
        return;
    }

    int index;
    printf("\nEnter the index of the specie to delete (1 to %d): ", *n);
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > *n) {
        printf("\nInvalid!\n");
        return;
    }

    for (int j = 0; j <= m; j++) {
        free(speciesSupplies[index - 1][j]);
    }
    free(speciesSupplies[index - 1]);

    for (int i = index - 1; i < *n - 1; i++) {
        speciesSupplies[i] = speciesSupplies[i + 1];
    }

    (*n)--;  
    printf("\nSpecies %d deleted.\n", index);
}

void update(char*** speciesSupplies, int n, int m) {
    int index;
    printf("\nEnter index of the specie to update (1 to %d): ", n);
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > n) {
        printf("\nInvalid!\n");
        return;
    }

    printf("\nUpdating supplies for species %d (%s):\n", index, speciesSupplies[index - 1][0]);
    for (int j = 1; j <= m; j++) {
        printf("Enter new supply %d: ", j);
        fgets(speciesSupplies[index - 1][j], 50, stdin);
        speciesSupplies[index - 1][j][strcspn(speciesSupplies[index - 1][j], "\n")] = '\0';  
    }
}