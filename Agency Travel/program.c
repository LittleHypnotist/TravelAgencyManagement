#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

typedef struct {
    int id;
    char name[50];
    char status[50];
    char salary[50];
} Employee;

typedef struct {
    int id;
    char name[50];
    char email[50];
} Customer;

int lastEmployeedID;

// Fetch the last ID
void fetchID() {
    FILE *file = fopen("employees.txt", "r");

    if (file == NULL){
        printf("Error opening the file.\n");
        return;
    }

    int maxID = 0;
    char line[100];

    while (fgets(line, sizeof(line), file) != NULL){
        if (strstr(line, "ID:") != NULL){
            int ID;
            sscanf(line, "ID: %d", &ID);
            if (ID > maxID){
                maxID = ID;
            }
        }
    }

    fclose(file);

    lastEmployeedID = maxID;    

}

// Add employee function
void addEmployee() {

    fetchID();

    Employee newEmployee;  

    newEmployee.id = lastEmployeedID + 1;

    printf("Name: ");
    // fflush(stdin);
    fgets(newEmployee.name, 50, stdin);
    newEmployee.name[strcspn(newEmployee.name, "\n")] = 0;

    printf("Status: ");
    // fflush(stdin);
    fgets(newEmployee.status, 50, stdin);
    newEmployee.status[strcspn(newEmployee.status, "\n")] = 0;

    printf("Salary: ");
    //fflush(stdin);
    fgets(newEmployee.salary, 50, stdin);
    newEmployee.salary[strcspn(newEmployee.salary, "\n")] = 0;

    FILE *file = fopen("employees.txt", "a");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    fprintf(file, "ID: %d\n", newEmployee.id);
    fprintf(file, "Name: %s\n", newEmployee.name);
    fprintf(file, "Status: %s\n", newEmployee.status);
    fprintf(file, "Salary: %s\n", newEmployee.salary);    

    fclose(file);

    printf("New employee successfully added!\n");

}

// Remove employee function

void removeEmployee(){


}

// List employee function

void listEmployee(){


}


int main(void)
{
    int opt;
    int opt_emp;    

    while (1)
    {
        printf(CYAN"\n-------Home Menu-------\n\n"RESET);
        printf(GREEN"1 - Manage Company\n"RESET);
        printf(GREEN"2 - Customer service\n"RESET);
        printf(RED"\n0 - Exit\n"RESET);
        printf(YELLOW"Select an option: \n"RESET);
        scanf("%d", &opt);        
        getchar();

        if (opt == 1) {
            while (1) {

                printf(CYAN"\n-------Employee Menu-------\n\n"RESET);
                printf("1 - Add employee\n");
                printf("2 - Remove employee\n");
                printf("3 - List employees\n");
                printf("0 - Exit\n");
                printf("Select an option: ");
                scanf("%d", &opt_emp);
                getchar();

                if (opt_emp == 1){
                    
                    addEmployee();
                }

                else if (opt_emp == 2){
                    removeEmployee();
                }

                else if (opt_emp == 3){
                    listEmployee();
                }

                else if (opt_emp == 0) {
                    break;
                }

                else {
                    printf("Invalid option. Please try again.\n");
                }

            }
        }

        else if (opt == 2){
            printf("Option Customer service.\n");
        }

        else if (opt == 0){
            break;
        }

        else {
            printf("Invalid option. Please try again.\n");
        }

    }
    
    
}