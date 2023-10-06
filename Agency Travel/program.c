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

typedef struct 
{
    int id;
    char name[50];
    char description[200];
} Destination;


int lastEmployeedID;
int lastDestinationID;

// Fetch the last ID
void fetchIdEmployee() {
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

void fetchIdDestination() {
    FILE *file = fopen("destination.txt", "r");

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

    lastDestinationID = maxID;    

}

// Add employee function
void addEmployee() {

    fetchIdEmployee();

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

    int idToRemove;
    printf("Enter the ID of the employee to remove: ");
    scanf("%d", &idToRemove);

    FILE *inputFile = fopen("employees.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (inputFile == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char line[100];
    bool found = false;

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        int id;
        if (sscanf(line, "ID: %d", &id) == 1 && id == idToRemove) {
            found = true;
            for (int i = 0; i < 3; i++) {
                fgets(line, sizeof(line), inputFile); // Skip name, status, and salary lines
            }
        } else {
            fputs(line, tempFile);
        }
    }

    fclose(inputFile);
    fclose(tempFile);

    if (!found) {
        remove("temp.txt");
        printf("Employee with ID %d not found.\n", idToRemove);
        return;
    }

    remove("employees.txt");
    rename("temp.txt", "employees.txt");

    printf("Employee with ID %d removed successfully.\n", idToRemove);

}

// List employee function

void listEmployee(){

    char anyKey;

    printf("The list of employees:\n");

    FILE *file = fopen("employees.txt", "r");

    if (file == NULL){
        printf("Error opening files.\n\n");
        return;
    }

    char line[100], name[50], status[50], salary[50];
    int id;

    while (fgets(line, sizeof(line), file)){

        if (sscanf(line, "ID: %d", &id) == 1) {
        
        fgets(line, sizeof(line), file); 
        sscanf(line, "Name: %49[^\n], ", name);
        fgets(line, sizeof(line), file); 
        sscanf(line, "Status: %49[^\n], ", status);
        fgets(line, sizeof(line), file); 
        sscanf(line, "Salary: %49[^\n]", salary);

        
        printf("ID: %d\nName: %s\nStatus: %s\nSalary: %s\n", id, name, status, salary);
    }

    }

    fclose(file);

    printf("Press any key to exit\n");
    scanf(" %c", &anyKey);


}

//Add destination function
void addDestination() {

    fetchIdDestination();

    Destination newDestination;  
    newDestination.id = lastDestinationID + 1;

    printf("Name: ");
    fgets(newDestination.name, 50, stdin);
    newDestination.name[strcspn(newDestination.name, "\n")] = 0;

    printf("Description: ");
    fgets(newDestination.description, 200, stdin);
    newDestination.description[strcspn(newDestination.description, "\n")] = 0;

    FILE *file = fopen("destination.txt", "a");

    if (file == NULL) {
        perror("Error opening destination.txt");
        return;
    }

    fprintf(file, "ID: %d\n", newDestination.id);
    fprintf(file, "Name: %s\n", newDestination.name);
    fprintf(file, "Description: %s\n", newDestination.description);

    fclose(file);

    printf("New destination successfully added!\n");
}


void removeDestination() {

    int idToRemove;
    printf(RED"You are about to delete a destination, be careful.\n"RESET);

    FILE *file = fopen("destination.txt", "r");
    FILE *tempFile = fopen("dest_temp.txt", "w");


    printf("Enter the ID of the employee to remove: ");
    scanf("%d", &idToRemove);
    
    
    if (file == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char line[100];
    bool found = false;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        int id;
        if (sscanf(line, "ID: %d", &id) == 1 && id == idToRemove) {
            found = true;
            for (int i = 0; i < 2; i++) {
                fgets(line, sizeof(line), file); 
            }
        } else {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        remove("dest_temp.txt");
        printf("Destination with ID %d not found.\n", idToRemove);
        return;
    }

    remove("destination.txt");
    rename("dest_temp.txt", "destination.txt");

    printf("Destination with ID %d removed successfully.\n", idToRemove);


}


void listDestination() {

    char anyKey;

    printf("This is the list of destinations:\n");

    FILE *file = fopen("destination.txt", "r");

    if (file == NULL){
        printf("Error opening files.\n\n");
        return;
    }

    char line[100], name[50], description[200];
    int id;

    while (fgets(line, sizeof(line), file)){

        if (sscanf(line, "ID: %d", &id) == 1) {
        
        fgets(line, sizeof(line), file); 
        sscanf(line, "Name: %49[^\n], ", name);
        fgets(line, sizeof(line), file); 
        sscanf(line, "Description: %49[^\n], ", description);
        fgets(line, sizeof(line), file); 
        

        
        printf("ID: %d\nName: %s\nDescription: %s\n", id, name, description);
    }

    }



    fclose(file);

    printf("Press any key to exit\n");
    scanf(" %c", &anyKey);
}



int main(void)
{
    int opt;
    int opt_emp;
    int opt_cust;    

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

                printf(CYAN"\n----Manage Company Menu----\n\n"RESET);
                printf("1 - Add employee\n");
                printf("2 - Remove employee\n");
                printf("3 - List employees\n");
                printf("4 - Add destinations\n");
                printf("5 - Remove destinations\n");
                printf("6 - List destinations\n");
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

                else if (opt_emp == 4)
                {
                    addDestination();
                }

                else if (opt_emp == 5)
                {
                    removeDestination();
                }
                

                else if (opt_emp == 6)
                {
                    listDestination();
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
            while (2)
            {
                printf(CYAN"\n----Custumer Service Menu----\n\n"RESET);
                printf("1 - Check Available Trips\n");
                printf("2 - Make a reservation\n");
                printf("3 - Cancel reservations\n");
                printf("0 - Exit\n");
                printf("Select an option: ");
                scanf("%d", &opt_cust);
                getchar();

                if (opt_cust == 1)
                {
                    
                }
                
            }
            
        }

        else if (opt == 0){
            break;
        }

        else {
            printf("Invalid option. Please try again.\n");
        }

    }
    
    
}