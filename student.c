/*************************************/
    /* Name: Oomat Latipov */
    /* NetID: U13921223 */
    /* Program Description: This file contains the implementation  */
    /* of functions for managing the student records list. */
/*************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "student.h"

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
	if(name != NULL) {
		printf("Enter the name of the student: ");
		scanf("%[^\n]", name);
	}
	if(netid != NULL) {
		printf("Enter the NetID of the student: ");
		scanf("%s", netid);
	}
	if(cop2510_grade != NULL) {
		printf("Enter the COP2510 letter grade: ");
		scanf(" %c", cop2510_grade);
	}
	if(gpa != NULL) {
		printf("Enter the GPA: ");
		scanf("%lf", gpa);
	}
	if(attempts != NULL) {
		printf("Enter the number of previous attempts: ");
		scanf("%d", attempts);
	}
}

struct student * add_student(struct student *registration, char *name, char *netid, char cop2510_grade, double gpa, int attempts) {

	// Nodes are appended to the linked list to maintain their sequential order.
	struct student *new_student = malloc(sizeof(struct student));
    if (new_student == NULL) {
        return registration;  
    }

    // Fill in the details of the new student
    strcpy(new_student->name, name);
    strcpy(new_student->netid, netid);
    new_student->cop2510_grade = cop2510_grade;
    new_student->gpa = gpa;
    new_student->attempts = attempts;
    new_student->next = NULL;

    // If the list is empty, insert as the first node
    if (registration == NULL) {
        return new_student;
    }

    // If the new student's attempts are greater than the first student, add to the beginning
    if (attempts > registration->attempts) {
        new_student->next = registration;
        return new_student;  // New student becomes the first node.
    }

    //Traverse the list to find the correct position
    struct student *current = registration;
    while (current->next != NULL && current->next->attempts >= attempts) {
        if (current->next->attempts > attempts) {
            // Moving forward to maintain descending order
            current = current->next;
        } else {
            // Stop when we reach the last student with the same number of attempts
            while (current->next != NULL && current->next->attempts == attempts) {
                current = current->next;
            }
            break;  // Exit when the right position is found
        }
    }

    // Insert the new student at the correct position
    new_student->next = current->next;
    current->next = new_student;

    return registration;
}

struct student * pop_student(struct student *registration) {
    if (registration == NULL) {
        return NULL;
    }

    struct student *to_pop = registration;
    // To make sure no empty row is printed.
    if (to_pop->name[0] != '\0' && to_pop->netid[0] != '\0') {
        printf("|----------------------|----------------------|---------|-----|----------|\n");
        printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
        printf("|----------------------|----------------------|---------|-----|----------|\n");
        printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
            to_pop->name, to_pop->netid, to_pop->cop2510_grade, to_pop->gpa, to_pop->attempts);
        printf("|----------------------|----------------------|---------|-----|----------|\n");
    }

    registration = registration->next;  
    free(to_pop);  
    return registration;
}

void list_students(struct student *registration) {
    if (registration == NULL) { //To make sure if an empty list is recieved the function does nothing.
        return;
    }

    struct student *c = registration;
    int hp = 0;

    while (c) {
        
        if (c->name[0] != '\0' && c->netid[0] != '\0') {
            if (!hp) {
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                hp = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
                c->name, c->netid, c->cop2510_grade, c->gpa, c->attempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        c = c->next;
    }
}

void list_gpa_min(struct student *registration, double gpa) {
    if (registration == NULL) { 
        return;
    }

    struct student *c = registration;
    int hp = 0;

    while (c) {
        if (c->gpa >= gpa && c->name[0] != '\0' && c->netid[0] != '\0') {
            if (!hp) {
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                hp = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
                c->name, c->netid, c->cop2510_grade, c->gpa, c->attempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        c = c->next;
    }
}

void list_cop2510_min(struct student *registration, int cop2510_grade) {
    if (registration == NULL) { // Check if the list is empty
        return;
    }

    struct student *c = registration;
    int hp = 0;

    while (c) {
        if (c->cop2510_grade <= cop2510_grade &&
            c->name[0] != '\0' && c->netid[0] != '\0') {
            if (!hp) {
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                hp = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
                   c->name, c->netid, c->cop2510_grade, c->gpa, c->attempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        c = c->next;
    }
}

struct student * clear_queue(struct student *registration) {
    if (registration == NULL) { // Check if the list is empty
        return NULL;
    }

    struct student *c = registration;
    while (c) {
        struct student *temp = c;
        c = c->next;
        free(temp);
    }
    return NULL;
}