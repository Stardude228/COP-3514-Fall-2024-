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
#define MAX_NAME_LEN 100
#define MAX_ID_LEN 40

typedef struct Student {
    char full_name[MAX_NAME_LEN + 1], student_id[MAX_ID_LEN + 1], grade;
    double grade_point_avg;
    int attempts_count;
    struct Student *next_student;
} Student;

// Function Prototypes
void display_help();
void read_input(char *full_name, char *student_id, char *grade, double *grade_point_avg, int *attempts_count);
Student *enqueue_student(Student *head, char *full_name, char *student_id, char grade, double grade_point_avg, int attempts_count);
Student *dequeue_student(Student *head);
void print_all_students(Student *head);
void print_students_with_min_gpa(Student *head, double min_gpa);
void print_students_with_min_grade(Student *head, int min_grade);
Student *clear_students(Student *head);

// Main Function
int main() {
    char operation;
    char full_name[MAX_NAME_LEN + 1], student_id[MAX_ID_LEN + 1], grade;
    double grade_point_avg;
    int attempts_count;
    Student *student_list = NULL;

    display_help();
    printf("\n");

    for (;;) {
        // Read operation code
        printf("Enter operation code: ");
        scanf(" %c", &operation);
        while (getchar() != '\n') // Skip to end of line
            ;

        // Execute operation
        switch (operation) {
            case 'h':
                display_help();
                break;
            case 'a':
                read_input(full_name, student_id, &grade, &grade_point_avg, &attempts_count);
                student_list = enqueue_student(student_list, full_name, student_id, grade, grade_point_avg, attempts_count);
                break;
            case 'p':
                student_list = dequeue_student(student_list);
                break;
            case 'l':
                print_all_students(student_list);
                break;
            case 'g':
                read_input(NULL, NULL, NULL, &grade_point_avg, NULL);
                print_students_with_min_gpa(student_list, grade_point_avg);
                break;
            case 'c':
                read_input(NULL, NULL, &grade, NULL, NULL);
                print_students_with_min_grade(student_list, grade);
                break;
            case 'q':
                student_list = clear_students(student_list);
                return 0;
            default:
                printf("Invalid operation code!\n");
        }
        printf("\n");
    }
}

// Function Definitions
void display_help() {
    printf("Available operation codes:\n");
    printf("\t'h' for displaying help;\n");
    printf("\t'a' for adding a student to the queue;\n");
    printf("\t'p' for removing a student from the queue;\n");
    printf("\t'l' for listing all students in the queue;\n");
    printf("\t'g' for listing students with a minimum GPA;\n");
    printf("\t'c' for listing students with a minimum grade;\n");
    printf("\t'q' to quit the program.\n");
}

void read_input(char *full_name, char *student_id, char *grade, double *grade_point_avg, int *attempts_count) {
    if (full_name != NULL) {
        printf("Enter student's full name: ");
        scanf("%[^\n]", full_name);
    }
    if (student_id != NULL) {
        printf("Enter student's ID: ");
        scanf("%s", student_id);
    }
    if (grade != NULL) {
        printf("Enter student's grade (letter): ");
        scanf(" %c", grade);
    }
    if (grade_point_avg != NULL) {
        printf("Enter student's GPA: ");
        scanf("%lf", grade_point_avg);
    }
    if (attempts_count != NULL) {
        printf("Enter student's number of attempts: ");
        scanf("%d", attempts_count);
    }
}

/// Converts grade letters to numeric values for comparison
int map_grade_value(char grade) {
    switch (toupper(grade)) {
        case 'A': return 5;
        case 'B': return 4;
        case 'C': return 3;
        case 'D': return 2;
        case 'F': return 1;
        default:  return 0;
    }
}

Student *enqueue_student(Student *head, char *full_name, char *student_id, char grade, double grade_point_avg, int attempts_count) {
    Student *new_student = malloc(sizeof(Student));
    if (new_student == NULL) {
        printf("Error: Memory allocation failed in enqueue_student\n");
        return head;
    }
    // Assign values
    strncpy(new_student->full_name, full_name, MAX_NAME_LEN);
    new_student->full_name[MAX_NAME_LEN] = '\0';
    strncpy(new_student->student_id, student_id, MAX_ID_LEN);
    new_student->student_id[MAX_ID_LEN] = '\0';
    new_student->grade = toupper(grade);
    new_student->grade_point_avg = grade_point_avg;
    new_student->attempts_count = attempts_count;
    new_student->next_student = NULL;

    if (head == NULL || new_student->attempts_count > head->attempts_count) {
        new_student->next_student = head;
        return new_student;
    }

    Student *current = head;
    while (current->next_student != NULL && current->next_student->attempts_count > new_student->attempts_count) {
        current = current->next_student;
    }
    new_student->next_student = current->next_student;
    current->next_student = new_student;

    return head;
}

Student *dequeue_student(Student *head) {
    if (head == NULL) {
        return head;
    }
    Student *first_student = head;
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Name                 | ID                   | Grade   | GPA | Attempts |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", first_student->full_name, first_student->student_id, first_student->grade, first_student->grade_point_avg, first_student->attempts_count);
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    head = first_student->next_student;
    free(first_student);

    return head;
}

void print_all_students(Student *head) {
    if (head == NULL) {
        return;
    }
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Name                 | ID                   | Grade   | GPA | Attempts |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    for (Student *current = head; current != NULL; current = current->next_student) {
        printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", current->full_name, current->student_id, current->grade, current->grade_point_avg, current->attempts_count);
        printf("|----------------------|----------------------|---------|-----|----------|\n");
    }
}

void print_students_with_min_gpa(Student *head, double min_gpa) {
    int found = 0;
    for (Student *current = head; current != NULL; current = current->next_student) {
        if (current->grade_point_avg >= min_gpa) {
            if (!found) {
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | ID                   | Grade   | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                found = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", current->full_name, current->student_id, current->grade, current->grade_point_avg, current->attempts_count);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
    }
}

void print_students_with_min_grade(Student *head, int min_grade) {
    int found = 0;
    char min_grade_char = toupper(min_grade);
    int min_grade_val = map_grade_value(min_grade_char);

    for (Student *current = head; current != NULL; current = current->next_student) {
        if (map_grade_value(current->grade) >= min_grade_val) {
            if (!found) {
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Name                 | ID                   | Grade   | GPA | Attempts |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                found = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", current->full_name, current->student_id, current->grade, current->grade_point_avg, current->attempts_count);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
    }
}

Student *clear_students(Student *head) {
    while (head != NULL) {
        Student *temp = head;
        head = head->next_student;
        free(temp);
    }
    return NULL;
}
