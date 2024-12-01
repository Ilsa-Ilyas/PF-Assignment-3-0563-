#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int *ratings;
    int totalScore;
};

void inputEmployees(struct Employee *employees, int numEmployees, int numPeriods) {
    for (int i = 0; i < numEmployees; i++) {
        employees[i].ratings = (int *)malloc(numPeriods * sizeof(int));
        employees[i].totalScore = 0;
        printf("Enter ratings for Employee %d:\n", i + 1);
        for (int j = 0; j < numPeriods; j++) {
            int rating;
            do {
                printf("  Rating for Period %d (1-10): ", j + 1);
                scanf("%d", &rating);
                if (rating < 1 || rating > 10) {
                    printf("    Invalid rating. Please enter a value between 1 and 10.\n");
                }
            } while (rating < 1 || rating > 10);
            employees[i].ratings[j] = rating;
            employees[i].totalScore += rating;
        }
    }
}

void displayPerformance(struct Employee *employees, int numEmployees, int numPeriods) {
    printf("\nPerformance Ratings:\n");
    for (int i = 0; i < numEmployees; i++) {
        printf("Employee %d: ", i + 1);
        for (int j = 0; j < numPeriods; j++) {
            printf("%d ", employees[i].ratings[j]);
        }
        printf(" | Total Score: %d\n", employees[i].totalScore);
    }
}

int findEmployeeOfTheYear(struct Employee *employees, int numEmployees, int numPeriods) {
    int employeeOfTheYear = 0;
    float maxAverage = 0.0f;

    for (int i = 0; i < numEmployees; i++) {
        float average = (float)employees[i].totalScore / numPeriods;
        if (average > maxAverage) {
            maxAverage = average;
            employeeOfTheYear = i;
        }
    }
    return employeeOfTheYear;
}

int findHighestRatedPeriod(struct Employee *employees, int numEmployees, int numPeriods) {
    int highestRatedPeriod = 0;
    float maxAverage = 0.0f;

    for (int j = 0; j < numPeriods; j++) {
        int totalScore = 0;
        for (int i = 0; i < numEmployees; i++) {
            totalScore += employees[i].ratings[j];
        }
        float average = (float)totalScore / numEmployees;
        if (average > maxAverage) {
            maxAverage = average;
            highestRatedPeriod = j;
        }
    }
    return highestRatedPeriod;
}

int findWorstPerformingEmployee(struct Employee *employees, int numEmployees) {
    int worstEmployee = 0;
    float minAverage = 11.0f;

    for (int i = 0; i < numEmployees; i++) {
        float average = (float)employees[i].totalScore / numEmployees;
        if (average < minAverage) {
            minAverage = average;
            worstEmployee = i;
        }
    }
    return worstEmployee;
}

int main() {
    int numEmployees, numPeriods;
    printf("Enter # of employees: ");
    scanf("%d", &numEmployees);
    printf("Enter # of evaluating periods: ");
    scanf("%d", &numPeriods);

    struct Employee *employees = (struct Employee *)malloc(numEmployees * sizeof(struct Employee));

    inputEmployees(employees, numEmployees, numPeriods);
    displayPerformance(employees, numEmployees, numPeriods);

    int employeeOfTheYear = findEmployeeOfTheYear(employees, numEmployees, numPeriods);
    printf("Employee of the Year: Employee %d\n", employeeOfTheYear + 1);

    int highestRatedPeriod = findHighestRatedPeriod(employees, numEmployees, numPeriods);
    printf("Highest Rated Period: Period %d\n", highestRatedPeriod + 1);

    int worstPerformingEmployee = findWorstPerformingEmployee(employees, numEmployees);
    printf("Worst Performing Employee: Employee %d\n", worstPerformingEmployee + 1);

    for (int i = 0; i < numEmployees; i++) {
        free(employees[i].ratings);
    }
    free(employees);

    return 0;
}
