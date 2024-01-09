#include <stdio.h>
#include <string.h>

// Define the Employee struct
struct Employee {
    char name[50];
    int empID;
    float hourlyRate;
    int hoursWorked;
};

// Function to calculate the salary
float calculateSalary(struct Employee emp) {
    return emp.hourlyRate * emp.hoursWorked;
}

int main() {
    // Create instances of Employee struct
    struct Employee fullTimeEmp = {"Sanad Alwerfali", 101, 15.5, 40};
    struct Employee partTimeEmp = {"Negib Sherif", 102, 12.0, 20};

    // Calculate and display salaries
    printf("%s's Salary: $%.2f\n", fullTimeEmp.name, calculateSalary(fullTimeEmp));
    printf("%s's Salary: $%.2f\n", partTimeEmp.name, calculateSalary(partTimeEmp));

    return 0;
}