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

// Data Definitions
#define MAX_NAME_LENGTH 100
#define MAX_NETID_LENGTH 40

typedef struct Student
{
    char studentName[MAX_NAME_LENGTH + 1];
    char studentNetID[MAX_NETID_LENGTH + 1];
    char cop2510Grade;
    double studentGPA;
    int attemptCount;
    struct Student *nextStudent;
} Student;

// Function Declarations
void displayHelp();
void collectInput(char *name, char *netid, char *grade, double *gpa, int *attempts);
Student *enqueueStudent(Student *head, char *name, char *netid, char grade, double gpa, int attempts);
Student *dequeueStudent(Student *head);
void printStudentList(Student *head);
void filterByGPA(Student *head, double minimumGPA);
void filterByGrade(Student *head, int minimumGrade);
Student *clearQueue(Student *head);

// Main Function 
int main()
{
    char operationCode;
    char inputName[MAX_NAME_LENGTH + 1];
    char inputNetID[MAX_NETID_LENGTH + 1];
    char inputGrade;
    double inputGPA;
    int inputAttempts;
    Student *studentQueue = NULL;

    displayHelp();
    printf("\n");

    while (1)
    {
        // Prompt for operation code
        printf("Enter operation code: ");
        scanf(" %c", &operationCode);
        while (getchar() != '\n')
            ; // Clear input buffer

        // Execute selected operation
        switch (operationCode)
        {
        case 'h':
            displayHelp();
            break;
        case 'a':
            collectInput(inputName, inputNetID, &inputGrade, &inputGPA, &inputAttempts);
            studentQueue = enqueueStudent(studentQueue, inputName, inputNetID, inputGrade, inputGPA, inputAttempts);
            break;
        case 'p':
            studentQueue = dequeueStudent(studentQueue);
            break;
        case 'l':
            printStudentList(studentQueue);
            break;
        case 'g':
            collectInput(NULL, NULL, NULL, &inputGPA, NULL);
            filterByGPA(studentQueue, inputGPA);
            break;
        case 'c':
            collectInput(NULL, NULL, &inputGrade, NULL, NULL);
            filterByGrade(studentQueue, inputGrade);
            break;
        case 'q':
            studentQueue = clearQueue(studentQueue);
            return 0;
        default:
            printf("Invalid operation code!\n");
        }
        printf("\n");
    }
}

// Function Implementations //
void displayHelp()
{
    printf("Available Operation Codes:\n");
    printf("\t'h' - Display help menu\n");
    printf("\t'a' - Add a student to the queue\n");
    printf("\t'p' - Remove a student from the queue\n");
    printf("\t'l' - List all students in the queue\n");
    printf("\t'g' - List students with a minimum GPA\n");
    printf("\t'c' - List students with a minimum COP2510 grade\n");
    printf("\t'q' - Quit the program\n");
}

void collectInput(char *name, char *netid, char *grade, double *gpa, int *attempts)
{
    if (name)
    {
        printf("Enter student name: ");
        scanf("%[^\n]", name);
        while (getchar() != '\n')
            ;
    }
    if (netid)
    {
        printf("Enter student NetID: ");
        scanf("%s", netid);
    }
    if (grade)
    {
        printf("Enter COP2510 grade: ");
        scanf(" %c", grade);
    }
    if (gpa)
    {
        printf("Enter GPA: ");
        scanf("%lf", gpa);
    }
    if (attempts)
    {
        printf("Enter number of attempts: ");
        scanf("%d", attempts);
    }
}

// Map grades to numeric values for comparisons
int mapGradeToValue(char grade)
{
    switch (toupper(grade))
    {
    case 'A':
        return 5;
    case 'B':
        return 4;
    case 'C':
        return 3;
    case 'D':
        return 2;
    case 'F':
        return 1;
    default:
        return 0;
    }
}

Student *enqueueStudent(Student *head, char *name, char *netid, char grade, double gpa, int attempts)
{
    Student *newNode = malloc(sizeof(Student));
    if (!newNode)
    {
        printf("Error: Memory allocation failed\n");
        return head;
    }

    strncpy(newNode->studentName, name, MAX_NAME_LENGTH);
    newNode->studentName[MAX_NAME_LENGTH] = '\0';
    strncpy(newNode->studentNetID, netid, MAX_NETID_LENGTH);
    newNode->studentNetID[MAX_NETID_LENGTH] = '\0';
    newNode->cop2510Grade = toupper(grade);
    newNode->studentGPA = gpa;
    newNode->attemptCount = attempts;
    newNode->nextStudent = NULL;

    if (!head || newNode->attemptCount > head->attemptCount)
    {
        newNode->nextStudent = head;
        return newNode;
    }

    Student *current = head;
    while (current->nextStudent && current->nextStudent->attemptCount >= newNode->attemptCount)
    {
        current = current->nextStudent;
    }

    newNode->nextStudent = current->nextStudent;
    current->nextStudent = newNode;
    return head;
}

Student *dequeueStudent(Student *head)
{
    if (!head)
        return NULL;

    Student *temp = head;
    printf("Dequeued Student: %s, NetID: %s\n", temp->studentName, temp->studentNetID);
    head = head->nextStudent;
    free(temp);
    return head;
}

void printStudentList(Student *head)
{
    Student *current = head;
    while (current)
    {
        printf("Name: %s, NetID: %s, Grade: %c, GPA: %.2f, Attempts: %d\n",
            current->studentName, current->studentNetID,
            current->cop2510Grade, current->studentGPA, current->attemptCount);
        current = current->nextStudent;
    }
}

void filterByGPA(Student *head, double minimumGPA)
{
    Student *current = head;
    while (current)
    {
        if (current->studentGPA >= minimumGPA)
        {
            printf("Name: %s, GPA: %.2f\n", current->studentName, current->studentGPA);
        }
        current = current->nextStudent;
    }
}

void filterByGrade(Student *head, int minimumGrade)
{
    Student *current = head;
    int targetValue = mapGradeToValue(minimumGrade);
    while (current)
    {
        if (mapGradeToValue(current->cop2510Grade) >= targetValue)
        {
            printf("Name: %s, Grade: %c\n", current->studentName, current->cop2510Grade);
        }
        current = current->nextStudent;
    }
}

Student *clearQueue(Student *head)
{
    Student *current = head;
    while (current)
    {
        Student *temp = current;
        current = current->nextStudent;
        free(temp);
    }
    return NULL;
}
