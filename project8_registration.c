/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: A local party equipment company */
/* offers bounce house rentals. The program */
/* calculates the cost for a bounce house rental. */
/*************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Updated data struct

#define MAX_NAME_LENGTH 100
#define MAX_ID_LENGTH 40

struct participant
{
    char fullName[MAX_NAME_LENGTH + 1];
    char id[MAX_ID_LENGTH + 1];
    char courseGrade;
    double gradePointAverage;
    int retryCount;
    struct participant *nextEntry;
};


// Updated function names

void displayHelp();
void inputData(char *fullName, char *id, char *courseGrade, double *gradePointAverage, int *retryCount);
struct participant *addEntry(struct participant *head, char *fullName, char *id, char courseGrade, double gradePointAverage, int retryCount);
struct participant *removeEntry(struct participant *head);
void displayAll(struct participant *head);
void filterByGPA(struct participant *head, double minGPA);
void filterByGrade(struct participant *head, char minGrade);
struct participant *clearList(struct participant *head);

////////////////////
// Main Function //
////////////////////

int main()
{
    char operation;
    char fullName[MAX_NAME_LENGTH + 1], id[MAX_ID_LENGTH + 1], courseGrade;
    double gradePointAverage;
    int retryCount;

    struct participant *head = NULL;

    displayHelp();
    printf("\n");

    for (;;)
    {
        printf("Enter command: ");
        scanf(" %c", &operation);
        while (getchar() != '\n') /* Skip to the end of the line */
            ;

        switch (operation)
        {
        case 'h':
            displayHelp();
            break;
        case 'a':
            inputData(fullName, id, &courseGrade, &gradePointAverage, &retryCount);
            head = addEntry(head, fullName, id, courseGrade, gradePointAverage, retryCount);
            break;
        case 'r':
            head = removeEntry(head);
            break;
        case 'd':
            displayAll(head);
            break;
        case 'g':
            inputData(NULL, NULL, NULL, &gradePointAverage, NULL);
            filterByGPA(head, gradePointAverage);
            break;
        case 'f':
            inputData(NULL, NULL, &courseGrade, NULL, NULL);
            filterByGrade(head, courseGrade);
            break;
        case 'q':
            head = clearList(head);
            return 0;
        default:
            printf("Invalid command!\n");
        }
        printf("\n");
    }
}

// Updated Functionality

void displayHelp()
{
    printf("Commands:\n");
    printf("\t'h': Display help.\n");
    printf("\t'a': Add a participant.\n");
    printf("\t'r': Remove the first participant.\n");
    printf("\t'd': Display all participants.\n");
    printf("\t'g': Filter participants by minimum GPA.\n");
    printf("\t'f': Filter participants by course grade.\n");
    printf("\t'q': Quit the program.\n");
}

void inputData(char *fullName, char *id, char *courseGrade, double *gradePointAverage, int *retryCount)
{
    if (fullName != NULL)
    {
        printf("Enter full name: ");
        scanf("%[^\n]", fullName);
    }
    if (id != NULL)
    {
        printf("Enter ID: ");
        scanf("%s", id);
    }
    if (courseGrade != NULL)
    {
        printf("Enter course grade: ");
        scanf(" %c", courseGrade);
    }
    if (gradePointAverage != NULL)
    {
        printf("Enter GPA: ");
        scanf("%lf", gradePointAverage);
    }
    if (retryCount != NULL)
    {
        printf("Enter retry count: ");
        scanf("%d", retryCount);
    }
}

struct participant *addEntry(struct participant *head, char *fullName, char *id, char courseGrade, double gradePointAverage, int retryCount)
{
    struct participant *newEntry = malloc(sizeof(struct participant));
    if (!newEntry)
    {
        exit(EXIT_FAILURE);
    }

    strcpy(newEntry->fullName, fullName);
    strcpy(newEntry->id, id);
    newEntry->courseGrade = courseGrade;
    newEntry->gradePointAverage = gradePointAverage;
    newEntry->retryCount = retryCount;
    newEntry->nextEntry = NULL;

    if (!head)
    {
        return newEntry;
    }

    struct participant *current = head;
    while (current->nextEntry)
    {
        current = current->nextEntry;
    }
    current->nextEntry = newEntry;

    return head;
}

struct participant *removeEntry(struct participant *head)
{
    if (!head)
    {
        return NULL;
    }

    struct participant *next = head->nextEntry;

    printf("|-----------------|-----------------|--------|-----|--------|\n");
    printf("| Full Name       | ID              | Grade  | GPA | Retries|\n");
    printf("|-----------------|-----------------|--------|-----|--------|\n");
    printf("| %-15s | %-15s |   %c    | %.2f | %6d |\n",
        head->fullName, head->id, head->courseGrade, head->gradePointAverage, head->retryCount);
    printf("|-----------------|-----------------|--------|-----|--------|\n");

    free(head);
    return next;
}

void displayAll(struct participant *head)
{
    if (!head)
    {
        return;
    }

    printf("|-----------------|-----------------|--------|-----|--------|\n");
    printf("| Full Name       | ID              | Grade  | GPA | Retries|\n");
    printf("|-----------------|-----------------|--------|-----|--------|\n");

    struct participant *current = head;
    while (current)
    {
        printf("| %-15s | %-15s |   %c    | %.2f | %6d |\n",
            current->fullName, current->id, current->courseGrade, current->gradePointAverage, current->retryCount);
        printf("|-----------------|-----------------|--------|-----|--------|\n");
        current = current->nextEntry;
    }
}

void filterByGPA(struct participant *head, double minGPA)
{
    if (!head)
    {
        return;
    }

    int found = 0;
    struct participant *current = head;

    while (current)
    {
        if (current->gradePointAverage >= minGPA)
        {
            if (!found)
            {
                printf("|-----------------|-----------------|--------|-----|--------|\n");
                printf("| Full Name       | ID              | Grade  | GPA | Retries|\n");
                printf("|-----------------|-----------------|--------|-----|--------|\n");
            }
            printf("| %-15s | %-15s |   %c    | %.2f | %6d |\n",
                current->fullName, current->id, current->courseGrade, current->gradePointAverage, current->retryCount);
            printf("|-----------------|-----------------|--------|-----|--------|\n");
            found = 1;
        }
        current = current->nextEntry;
    }
}

void filterByGrade(struct participant *head, char minGrade)
{
    if (!head)
    {
        return;
    }

    int found = 0;
    struct participant *current = head;

    while (current)
    {
        if (current->courseGrade <= minGrade)
        {
            if (!found)
            {
                printf("|-----------------|-----------------|--------|-----|--------|\n");
                printf("| Full Name       | ID              | Grade  | GPA | Retries|\n");
                printf("|-----------------|-----------------|--------|-----|--------|\n");
            }
            printf("| %-15s | %-15s |   %c    | %.2f | %6d |\n",
                current->fullName, current->id, current->courseGrade, current->gradePointAverage, current->retryCount);
            printf("|-----------------|-----------------|--------|-----|--------|\n");
            found = 1;
        }
        current = current->nextEntry;
    }
}

struct participant *clearList(struct participant *head)
{
    while (head)
    {
        struct participant *next = head->nextEntry;
        free(head);
        head = next;
    }
    return NULL;
}
