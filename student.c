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

void showUsageGuide() {
	printf("List of operation codes:\n");
	printf("\t'h' for help;\n");
	printf("\t'a' for adding a student to the queue;\n");
	printf("\t'p' for removing a student from the queue;\n");
	printf("\t'l' for listing all students in the queue;\n");
	printf("\t'g' for searching students with a minimum GPA;\n");
	printf("\t'c' for searching students with a minimum grade in COP2510;\n");
	printf("\t'q' to quit.\n");
}

void inputStudentInfo(char *studentName, char *universityID, char *gradeAchieved, double *cumulativeGPA, int *retryAttempts) {
    if (studentName != NULL) {
		printf("Enter the name of the student: ");
        scanf("%[^\n]", studentName);
    }
    if (universityID != NULL) {
		printf("Enter the NetID of the student: ");
        scanf("%s", universityID);
    }
    if (gradeAchieved != NULL) {
		printf("Enter the COP2510 letter grade: ");
        scanf(" %c", gradeAchieved);
    }
    if (cumulativeGPA != NULL) {
		printf("Enter the GPA: ");
        scanf("%lf", cumulativeGPA);
    }
    if (retryAttempts != NULL) {
		printf("Enter the number of previous attempts: ");
        scanf("%d", retryAttempts);
    }
}

struct StudentData * registerStudent(struct StudentData *currentList, char *studentName, char *universityID, char gradeAchieved, double cumulativeGPA, int retryAttempts) {
    struct StudentData *newStudent = malloc(sizeof(struct StudentData));
    if (newStudent == NULL) {
        return currentList;
    }

    strcpy(newStudent->studentName, studentName);
    strcpy(newStudent->universityID, universityID);
    newStudent->gradeAchieved = gradeAchieved;
    newStudent->cumulativeGPA = cumulativeGPA;
    newStudent->retryAttempts = retryAttempts;
    newStudent->nextEntry = NULL;

    if (currentList == NULL) {
        return newStudent;
    }

    if (retryAttempts > currentList->retryAttempts) {
        newStudent->nextEntry = currentList;
        return newStudent;
    }

    struct StudentData *current = currentList;
    while (current->nextEntry != NULL && current->nextEntry->retryAttempts >= retryAttempts) {
        current = current->nextEntry;
    }

    newStudent->nextEntry = current->nextEntry;
    current->nextEntry = newStudent;

    return currentList;
}

struct StudentData * deleteStudent(struct StudentData *currentList) {
    if (currentList == NULL) {
        return NULL;
    }

    struct StudentData *toRemove = currentList;
    if (toRemove->studentName[0] != '\0' && toRemove->universityID[0] != '\0') {
        printf("|----------------------|----------------------|---------|-----|----------|\n");
        printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
        printf("|----------------------|----------------------|---------|-----|----------|\n");
        printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
            toRemove->studentName, toRemove->universityID, toRemove->gradeAchieved, toRemove->cumulativeGPA, toRemove->retryAttempts);
        printf("|----------------------|----------------------|---------|-----|----------|\n");
    }

    currentList = currentList->nextEntry;
    free(toRemove);
    return currentList;
}

void printStudentList(struct StudentData *currentList) {
    if (currentList == NULL) {
        return;
    }

    struct StudentData *current = currentList;
    int headerPrinted = 0;

    while (current) {
        if (current->studentName[0] != '\0' && current->universityID[0] != '\0') {
            if (!headerPrinted) {
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                headerPrinted = 1;
            }
            printf("| %-22s | %-22s |   %c   | %1.1f | %9d |\n",
                current->studentName, current->universityID, current->gradeAchieved, current->cumulativeGPA, current->retryAttempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        current = current->nextEntry;
    }
}

void filterByGPA(struct StudentData *currentList, double gpaThreshold) {
    if (currentList == NULL) {
        return;
    }

    struct StudentData *current = currentList;
    int headerPrinted = 0;

    while (current) {
        if (current->cumulativeGPA >= gpaThreshold && current->studentName[0] != '\0' && current->universityID[0] != '\0') {
            if (!headerPrinted) {
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                headerPrinted = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
                current->studentName, current->universityID, current->gradeAchieved, current->cumulativeGPA, current->retryAttempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        current = current->nextEntry;
    }
}

void filterByGrade(struct StudentData *currentList, int gradeThreshold) {
    if (currentList == NULL) {
        return;
    }

    struct StudentData *current = currentList;
    int headerPrinted = 0;

    while (current) {
        if (current->gradeAchieved <= gradeThreshold && current->studentName[0] != '\0' && current->universityID[0] != '\0') {
            if (!headerPrinted) {
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                headerPrinted = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
                current->studentName, current->universityID, current->gradeAchieved, current->cumulativeGPA, current->retryAttempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        current = current->nextEntry;
    }
}

struct StudentData * resetList(struct StudentData *currentList) {
    if (currentList == NULL) {
        return NULL;
    }

    struct StudentData *current = currentList;
    while (current) {
        struct StudentData *temp = current;
        current = current->nextEntry;
        free(temp);
    }
    return NULL;
}
