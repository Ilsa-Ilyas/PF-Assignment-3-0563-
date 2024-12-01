#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* title;
    float rating;
    int runtime;
    char* encodingFormat;
} ContentMetadata;

typedef struct {
    int resolution;
    float bandwidthUsage;
    int playbackPosition;
} DevicePreferences;

double** initializeEngagementMatrix(int numUsers, int numCategories) {
    double** matrix = (double**)malloc(numUsers * sizeof(double*));
    if (!matrix) {
        printf("Memory allocation failed for engagement matrix.\n");
        exit(1);
    }
    for (int i = 0; i < numUsers; i++) {
        matrix[i] = (double*)malloc(numCategories * sizeof(double));
        if (!matrix[i]) {
            printf("Memory allocation failed for engagement row %d.\n", i);
            exit(1);
        }
        for (int j = 0; j < numCategories; j++) {
            matrix[i][j] = 0.0; 
        }
    }
    return matrix;
}

DevicePreferences*** initializeDeviceMatrix(int numUsers, int numDevices) {
    DevicePreferences*** matrix = (DevicePreferences***)malloc(numUsers * sizeof(DevicePreferences**));
    if (!matrix) {
        printf("Memory allocation failed for device matrix.\n");
        exit(1);
    }
    for (int i = 0; i < numUsers; i++) {
        matrix[i] = (DevicePreferences**)malloc(numDevices * sizeof(DevicePreferences*));
        if (!matrix[i]) {
            printf("Memory allocation failed for user %d in device matrix.\n", i);
            exit(1);
        }
        for (int j = 0; j < numDevices; j++) {
            matrix[i][j] = (DevicePreferences*)malloc(sizeof(DevicePreferences));
            if (!matrix[i][j]) {
                printf("Memory allocation failed for device %d of user %d.\n", j, i);
                exit(1);
            }
            matrix[i][j]->resolution = 1080;
            matrix[i][j]->bandwidthUsage = 5.0;
            matrix[i][j]->playbackPosition = 0;
        }
    }
    return matrix;
}

ContentMetadata*** initializeContentMetadataMatrix(int numCategories, int numContent) {
    ContentMetadata*** matrix = (ContentMetadata***)malloc(numCategories * sizeof(ContentMetadata**));
    if (!matrix) {
        printf("Memory allocation failed for content metadata matrix.\n");
        exit(1);
    }
    for (int i = 0; i < numCategories; i++) {
        matrix[i] = (ContentMetadata**)malloc(numContent * sizeof(ContentMetadata*));
        if (!matrix[i]) {
            printf("Memory allocation failed for category %d.\n", i);
            exit(1);
        }
        for (int j = 0; j < numContent; j++) {
            matrix[i][j] = (ContentMetadata*)malloc(sizeof(ContentMetadata));
            if (!matrix[i][j]) {
                printf("Memory allocation failed for content %d in category %d.\n", j, i);
                exit(1);
            }
            matrix[i][j]->title = (char*)malloc(100 * sizeof(char));
            matrix[i][j]->encodingFormat = (char*)malloc(20 * sizeof(char));
        }
    }
    return matrix;
}

void freeMemory(double** engagementMatrix, DevicePreferences*** deviceMatrix, ContentMetadata*** contentMetadataMatrix,
                int numUsers, int numCategories, int numDevices, int numContent) {
    for (int i = 0; i < numUsers; i++) {
        free(engagementMatrix[i]);
    }
    free(engagementMatrix);

    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numDevices; j++) {
            free(deviceMatrix[i][j]);
        }
        free(deviceMatrix[i]);
    }
    free(deviceMatrix);

    for (int i = 0; i < numCategories; i++) {
        for (int j = 0; j < numContent; j++) {
            free(contentMetadataMatrix[i][j]->title);
            free(contentMetadataMatrix[i][j]->encodingFormat);
            free(contentMetadataMatrix[i][j]);
        }
        free(contentMetadataMatrix[i]);
    }
    free(contentMetadataMatrix);
}

int main() {
    int numUsers, numCategories, numDevices, numContent;

    printf("\n--- Netflix-Like Streaming Platform ---\n");
    printf("Enter the number of users: ");
    scanf("%d", &numUsers);

    printf("Enter the number of content categories: ");
    scanf("%d", &numCategories);

    printf("Enter the number of devices per user: ");
    scanf("%d", &numDevices);

    printf("Enter the number of content items per category: ");
    scanf("%d", &numContent);

    double** engagementMatrix = initializeEngagementMatrix(numUsers, numCategories);
    DevicePreferences*** deviceMatrix = initializeDeviceMatrix(numUsers, numDevices);
    ContentMetadata*** contentMetadataMatrix = initializeContentMetadataMatrix(numCategories, numContent);

    printf("\n--- Enter Engagement Scores ---\n");
    for (int i = 0; i < numUsers; i++) {
        printf("\nUser %d Engagement Scores:\n", i + 1);
        for (int j = 0; j < numCategories; j++) {
            printf("  Category %d Score: ", j + 1);
            scanf("%lf", &engagementMatrix[i][j]);
        }
    }

    printf("\n--- Enter Device Preferences ---\n");
    for (int i = 0; i < numUsers; i++) {
        printf("\nUser %d Devices:\n", i + 1);
        for (int j = 0; j < numDevices; j++) {
            printf("  Device %d:\n", j + 1);
            printf("    Resolution: ");
            scanf("%d", &deviceMatrix[i][j]->resolution);
            printf("    Bandwidth Usage: ");
            scanf("%f", &deviceMatrix[i][j]->bandwidthUsage);
            printf("    Playback Position: ");
            scanf("%d", &deviceMatrix[i][j]->playbackPosition);
        }
    }

    printf("\n--- Enter Content Metadata ---\n");
    for (int i = 0; i < numCategories; i++) {
        printf("\nCategory %d:\n", i + 1);
        for (int j = 0; j < numContent; j++) {
            printf("  Content %d:\n", j + 1);
            printf("    Title: ");
            scanf(" %[^\n]", contentMetadataMatrix[i][j]->title);
            printf("    Rating: ");
            scanf("%f", &contentMetadataMatrix[i][j]->rating);
            printf("    Runtime (in minutes): ");
            scanf("%d", &contentMetadataMatrix[i][j]->runtime);
            printf("    Encoding Format: ");
            scanf(" %[^\n]", contentMetadataMatrix[i][j]->encodingFormat);
        }
    }

    printf("\n--- Data Overview ---\n");
    for (int i = 0; i < numUsers; i++) {
        printf("\nUser %d:\n", i + 1);
        printf("  Engagement Scores:\n");
        for (int j = 0; j < numCategories; j++) {
            printf("    Category %d: %.2f\n", j + 1, engagementMatrix[i][j]);
        }
        printf("  Device Preferences:\n");
        for (int j = 0; j < numDevices; j++) {
            printf("    Device %d: Resolution: %d, Bandwidth Usage: %.2f, Playback Position: %d\n",
                   j + 1, deviceMatrix[i][j]->resolution, deviceMatrix[i][j]->bandwidthUsage, deviceMatrix[i][j]->playbackPosition);
        }
    }

    for (int i = 0; i < numCategories; i++) {
        printf("\nCategory %d Content:\n", i + 1);
        for (int j = 0; j < numContent; j++) {
            printf("  Content %d: Title: %s, Rating: %.1f, Runtime: %d minutes, Encoding: %s\n",
                   j + 1, contentMetadataMatrix[i][j]->title, contentMetadataMatrix[i][j]->rating,
                   contentMetadataMatrix[i][j]->runtime, contentMetadataMatrix[i][j]->encodingFormat);
        }
    }

    freeMemory(engagementMatrix, deviceMatrix, contentMetadataMatrix, numUsers, numCategories, numDevices, numContent);
    printf("\nMemory freed. Program terminated.\n");

    return 0;
}
