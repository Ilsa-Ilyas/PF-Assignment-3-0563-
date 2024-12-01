#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct employee {
    int employeecode;
    char employeename[50];
    int dateofjoin;
};

void employeeinput(struct employee *Employee) {
    printf("Enter Employee Code: ");
    scanf("%d", &Employee->employeecode);
    printf("Enter Employee Name: ");
    getchar();
    fgets(Employee->employeename, sizeof(Employee->employeename), stdin);
    Employee->employeename[strcspn(Employee->employeename, "\n")] = 0;
    printf("Enter Joining Date (YYYYMMDD): ");
    scanf("%d", &Employee->dateofjoin);
}

void calctenure(struct employee employees[], int size) {
    int currentdate, count = 0;
    printf("Enter the current date (YYYYMMDD):\n");
    scanf("%d", &currentdate);

    printf("\nEmployees with tenure > 3 years:\n");
    for (int i = 0; i < size; i++) {
        int yearofjoin = employees[i].dateofjoin / 10000;
        int currentyear = currentdate / 10000;
        int tenure = currentyear - yearofjoin;

        if (tenure > 3) {
            count++;
            printf("Employee Code: %d\n", employees[i].employeecode);
            printf("Employee Name: %s\n", employees[i].employeename);
            printf("Date of Joining: %d\n", employees[i].dateofjoin);
            printf("Tenure: %d years\n\n", tenure);
        }
    }
    printf("Total employees with tenure > 3 years: %d\n", count);
}

int main() {
    struct employee employees[4];
    printf("Enter details for 4 employees:\n");
    for (int i = 0; i < 4; i++) {
        printf("\nEmployee %d:\n", i + 1);
        employeeinput(&employees[i]);
    }
    calctenure(employees, 4);
    return 0;
}
