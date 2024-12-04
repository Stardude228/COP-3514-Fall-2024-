/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: receives the registration linked list and the values for student name, NetID */
/* COP2510 grade, GPA, and number of previous attempts, and adds the new student to the registration  */
/* linked list so that the nodes in the list are kept in order by number of previous attempts in  */
/* decreasing order; students with the same number of previous attempts are inserted in first come,  */
/* first serve basis; */
/*************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definitions
#define NAME_LEN 100
#define NETID_LEN 40

struct student {
    char name[NAME_LEN+1], netid[NETID_LEN+1], cop2510_grade;
    double gpa;
    int attempts;
    struct student *next;
};

// Prototypes
void help();
void read(char *name, char *netid, char *cop2510_grade, double *gpa, int *attempts);
struct student *add_student(struct student *registration, char *name, char *netid,
                            char cop2510_grade, double gpa, int attempts);
struct student *pop_student(struct student *registration);
void list_students(struct student *registration);
void list_gpa_min(struct student *registration, double gpa);
void list_cop2510_min(struct student *registration, int cop2510_grade);
struct student *clear_queue(struct student *registration);

// Main
int main() {
    char code;
    char name[NAME_LEN+1], netid[NETID_LEN+1], cop2510_grade;
    double gpa;
    int attempts;
    struct student *registration = NULL;

    help();
    printf("\n");

    for (;;) {
        // read operation code
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n') /* skips to end of line */
            ;

        // run operation
        switch (code) {
            case 'h':
                help();
                break;
            case 'a':
                read(name, netid, &cop2510_grade, &gpa, &attempts);
                registration = add_student(registration, name, netid, cop2510_grade, gpa, attempts);
                break;
            case 'p':
                registration = pop_student(registration);
                break;
            case 'l':
                list_students(registration);
                break;
            case 'g':
                read(NULL, NULL, NULL, &gpa, NULL);
                list_gpa_min(registration, gpa);
                break;
            case 'c':
                read(NULL, NULL, &cop2510_grade, NULL, NULL);
                list_cop2510_min(registration, cop2510_grade);
                break;
            case 'q':
                registration = clear_queue(registration);
                return 0;
            default:
                printf("Illegal operation code!\n");
        }
        printf("\n");
    }
}

// Definitions
void help() {
    printf("List of operation codes:\n");
    printf("\t'h' for help;\n");
    printf("\t'a' for adding a student to the queue;\n");
    printf("\t'p' for removing a student from the queue;\n");
    printf("\t'l' for listing all students in the queue;\n");
    printf("\t'g' for searching students with a minimum GPA;\n");
    printf("\t'c' for searching students with a minimum grade in COP2510;\n");
    printf("\t'q' to quit.\n");
}

void read(char *name, char *netid, char *cop2510_grade, double *gpa, int *attempts) {
    if (name != NULL) {
        printf("Enter the name of the student: ");
        scanf("%[^\n]", name);
    }
    if (netid != NULL) {
        printf("Enter the NetID of the student: ");
        scanf("%s", netid);
    }
    if (cop2510_grade != NULL) {
        printf("Enter the COP2510 letter grade: ");
        scanf(" %c", cop2510_grade);
    }
    if (gpa != NULL) {
        printf("Enter the GPA: ");
        scanf("%lf", gpa);
    }
    if (attempts != NULL) {
        printf("Enter the number of previous attempts: ");
        scanf("%d", attempts);
    }
}

// Function to map grades to numeric values for comparison
int grade_value(char grade) {
    switch (toupper(grade)) {
        case 'A': return 5;
        case 'B': return 4;
        case 'C': return 3;
        case 'D': return 2;
        case 'F': return 1;
        default:  return 0;
    }
}

struct student * add_student(struct student *registration, char *name, char *netid, char cop2510_grade, double gpa, int attempts) {
    struct student *new_student = malloc(sizeof(struct student));
    if (new_student == NULL) {
        printf("Error: malloc failed in add_student\n");
        return registration;
    }
    // Copy the data
    strncpy(new_student->name, name, NAME_LEN);
    new_student->name[NAME_LEN] = '\0';  // Ensure null termination
    strncpy(new_student->netid, netid, NETID_LEN);
    new_student->netid[NETID_LEN] = '\0';  // Ensure null termination
    new_student->cop2510_grade = toupper(cop2510_grade); // Ensure uppercase
    new_student->gpa = gpa;
    new_student->attempts = attempts;
    new_student->next = NULL;

    // If the list is empty or new student has higher attempts than the head
    if (registration == NULL || new_student->attempts > registration->attempts) {
        // Insert at the beginning
        new_student->next = registration;
        registration = new_student;
        return registration;
    }

    struct student *cur = registration;
    // Move forward past students with attempts greater than new student's attempts
    while (cur->next != NULL && cur->next->attempts > new_student->attempts) {
        cur = cur->next;
    }
    // Move forward past students with same number of attempts to maintain first come, first serve
    while (cur->next != NULL && cur->next->attempts == new_student->attempts) {
        cur = cur->next;
    }

    // Insert after cur
    new_student->next = cur->next;
    cur->next = new_student;

    return registration;
}

struct student * pop_student(struct student *registration) {
    if (registration == NULL) {
        // Do nothing if the list is empty
        return registration;
    }
    // Print the information of the first student
    struct student *first_student = registration;

    // Output format
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", first_student->name, first_student->netid, first_student->cop2510_grade, first_student->gpa, first_student->attempts);
    printf("|----------------------|----------------------|---------|-----|----------|\n");

    // Remove the student from the queue
    registration = first_student->next;
    free(first_student);

    return registration;
}

void list_students(struct student *registration) {
    if (registration == NULL) {
        // Do nothing
        return;
    }

    struct student *cur = registration;

    // Output header
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");

    while (cur != NULL) {
        printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", cur->name, cur->netid, cur->cop2510_grade, cur->gpa, cur->attempts);
        printf("|----------------------|----------------------|---------|-----|----------|\n");
        cur = cur->next;
    }
}

void list_gpa_min(struct student *registration, double min_gpa) {
    int found = 0;
    struct student *cur = registration;

    while (cur != NULL) {
        if (cur->gpa >= min_gpa) {
            if (!found) {
                // Output header
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                found = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", cur->name, cur->netid, cur->cop2510_grade, cur->gpa, cur->attempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        cur = cur->next;
    }
    // If no students satisfy this condition, this function does nothing
}

void list_cop2510_min(struct student *registration, int cop2510_grade) {
    int found = 0;
    struct student *cur = registration;
    char min_grade = toupper(cop2510_grade);
    int min_grade_value = grade_value(min_grade);

    while (cur != NULL) {
        int cur_grade_value = grade_value(cur->cop2510_grade);
        if (cur_grade_value >= min_grade_value) {
            if (!found) {
                // Output header
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                found = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", cur->name, cur->netid, cur->cop2510_grade, cur->gpa, cur->attempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        cur = cur->next;
    }
    // If no students satisfy this condition, this function does nothing
}

struct student * clear_queue(struct student *registration) {
    struct student *cur = registration;
    while (cur != NULL) {
        struct student *temp = cur;
        cur = cur->next;
        free(temp);
    }
    return NULL;
}
