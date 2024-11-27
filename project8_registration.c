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

//////////////////////
// Data definitions //
//////////////////////

#define MAX_NAME_SIZE 100
#define MAX_NETID_SIZE 40

struct queue_node {
    char student_name[MAX_NAME_SIZE + 1];
    char student_netid[MAX_NETID_SIZE + 1];
    char course_grade;
    double student_gpa;
    int num_attempts;
    struct queue_node *next_node;
};

/////////////////////////
// Function prototypes //
/////////////////////////

void display_help();
void input_values(char *student_name, char *student_netid, char *course_grade, double *student_gpa, int *num_attempts);
struct queue_node *enqueue(struct queue_node *head, char *student_name, char *student_netid, char course_grade, double student_gpa, int num_attempts);
struct queue_node *dequeue(struct queue_node *head);
void print_queue(struct queue_node *head);
void filter_by_gpa(struct queue_node *head, double min_gpa);
void filter_by_grade(struct queue_node *head, int min_grade);
struct queue_node *clear_all(struct queue_node *head);

///////////////////
// Main function //
///////////////////

int main() {
    char operation;
    char student_name[MAX_NAME_SIZE + 1], student_netid[MAX_NETID_SIZE + 1], course_grade;
    double student_gpa;
    int num_attempts;

    struct queue_node *queue_head = NULL;

    display_help();
    printf("\n");

    for (;;) {
        printf("Enter operation code: ");
        scanf(" %c", &operation);
        while (getchar() != '\n') /* skips to end of line */
            ;

        switch (operation) {
            case 'h':
                display_help();
                break;
            case 'a':
                input_values(student_name, student_netid, &course_grade, &student_gpa, &num_attempts);
                queue_head = enqueue(queue_head, student_name, student_netid, course_grade, student_gpa, num_attempts);
                break;
            case 'p':
                queue_head = dequeue(queue_head);
                break;
            case 'l':
                print_queue(queue_head);
                break;
            case 'g':
                input_values(NULL, NULL, NULL, &student_gpa, NULL);
                filter_by_gpa(queue_head, student_gpa);
                break;
            case 'c':
                input_values(NULL, NULL, &course_grade, NULL, NULL);
                filter_by_grade(queue_head, course_grade);
                break;
            case 'q':
                queue_head = clear_all(queue_head);
                return 0;
            default:
                printf("Illegal operation code!\n");
        }
        printf("\n");
    }
}

//////////////////////////
// Function definitions //
//////////////////////////

void display_help() {
    printf("List of operation codes:\n");
    printf("\t'h' for help;\n");
    printf("\t'a' for adding a student to the queue;\n");
    printf("\t'p' for removing a student from the queue;\n");
    printf("\t'l' for listing all students in the queue;\n");
    printf("\t'g' for searching students with a minimum GPA;\n");
    printf("\t'c' for searching students with a minimum grade in COP2510;\n");
    printf("\t'q' to quit.\n");
}

void input_values(char *student_name, char *student_netid, char *course_grade, double *student_gpa, int *num_attempts) {
    if (student_name != NULL) {
        printf("Enter the name of the student: ");
        scanf("%[^\n]", student_name);
    }
    if (student_netid != NULL) {
        printf("Enter the NetID of the student: ");
        scanf("%s", student_netid);
    }
    if (course_grade != NULL) {
        printf("Enter the COP2510 letter grade: ");
        scanf(" %c", course_grade);
    }
    if (student_gpa != NULL) {
        printf("Enter the GPA: ");
        scanf("%lf", student_gpa);
    }
    if (num_attempts != NULL) {
        printf("Enter the number of previous attempts: ");
        scanf("%d", num_attempts);
    }
}

struct queue_node *enqueue(struct queue_node *head, char *student_name, char *student_netid, char course_grade, double student_gpa, int num_attempts) {
    struct queue_node *new_node = malloc(sizeof(struct queue_node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->student_name, student_name);
    strcpy(new_node->student_netid, student_netid);
    new_node->course_grade = course_grade;
    new_node->student_gpa = student_gpa;
    new_node->num_attempts = num_attempts;
    new_node->next_node = NULL;

    if (!head) {
        return new_node;
    }

    struct queue_node *current_node = head;
    while (current_node->next_node) {
        current_node = current_node->next_node;
    }
    current_node->next_node = new_node;

    return head;
}

struct queue_node *dequeue(struct queue_node *head) {
    if (!head) {
        return NULL;
    }

    struct queue_node *next_node = head->next_node;

    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
           head->student_name, head->student_netid, head->course_grade, head->student_gpa, head->num_attempts);
    printf("|----------------------|----------------------|---------|-----|----------|\n");

    free(head);
    return next_node;
}

void print_queue(struct queue_node *head) {
    if (!head) {
        return;
    }

    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");

    struct queue_node *current_node = head;
    while (current_node) {
        printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
               current_node->student_name, current_node->student_netid, current_node->course_grade, current_node->student_gpa, current_node->num_attempts);
        printf("|----------------------|----------------------|---------|-----|----------|\n");
        current_node = current_node->next_node;
    }
}

void filter_by_gpa(struct queue_node *head, double min_gpa) {
    if (!head) {
        return;
    }

    int found = 0;
    struct queue_node *current_node = head;

    while (current_node) {
        if (current_node->student_gpa >= min_gpa) {
            if (!found) {
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
                   current_node->student_name, current_node->student_netid, current_node->course_grade, current_node->student_gpa, current_node->num_attempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
            found = 1;
        }
        current_node = current_node->next_node;
    }
}

void filter_by_grade(struct queue_node *head, int min_grade) {
    if (!head) {
        return;
    }

    int found = 0;
    struct queue_node *current_node = head;

    while (current_node) {
        if (current_node->course_grade <= min_grade) {
            if (!found) {
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
                   current_node->student_name, current_node->student_netid, current_node->course_grade, current_node->student_gpa, current_node->num_attempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
            found = 1;
        }
        current_node = current_node->next_node;
    }
}

struct queue_node *clear_all(struct queue_node *head) {
    while (head) {
        struct queue_node *next_node = head->next_node;
        free(head);
        head = next_node;
    }
    return NULL;
}
