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

//////////////////////
// data definitions //
//////////////////////
#define MAX_NAME_LENGTH 100
#define MAX_NETID_LENGTH 40

struct learner {
    char full_name[MAX_NAME_LENGTH + 1], student_id[MAX_NETID_LENGTH + 1], course_grade;
    double grade_point_average;
    int retries;
    struct learner *next_learner;
};

/////////////////////////
// function prototypes //
/////////////////////////
void show_help();
void gather_data(char *full_name, char *student_id, char *course_grade, double *grade_point_average, int *retries);
struct learner *enroll_learner(struct learner *queue, char *full_name, char *student_id,
                                char course_grade, double grade_point_average, int retries);
struct learner *remove_learner(struct learner *queue);
void display_learners(struct learner *queue);
void display_min_gpa(struct learner *queue, double grade_point_average);
void display_min_course_grade(struct learner *queue, int course_grade);
struct learner *clear_queue(struct learner *queue);

///////////////////
// main function //
///////////////////
int main() {
    char action_code;
    char full_name[MAX_NAME_LENGTH + 1], student_id[MAX_NETID_LENGTH + 1], course_grade;
    double grade_point_average;
    int retries;
    struct learner *queue = NULL;

    show_help();
    printf("\n");

    for (;;) {
        // read action code
        printf("Enter action code: ");
        scanf(" %c", &action_code);
        while (getchar() != '\n') /* skips to end of line */
            ;

        // run action
        switch (action_code) {
            case 'h':
                show_help();
                break;
            case 'a':
                gather_data(full_name, student_id, &course_grade, &grade_point_average, &retries);
                queue = enroll_learner(queue, full_name, student_id, course_grade, grade_point_average, retries);
                break;
            case 'r':
                queue = remove_learner(queue);
                break;
            case 'd':
                display_learners(queue);
                break;
            case 'g':
                gather_data(NULL, NULL, NULL, &grade_point_average, NULL);
                display_min_gpa(queue, grade_point_average);
                break;
            case 'c':
                gather_data(NULL, NULL, &course_grade, NULL, NULL);
                display_min_course_grade(queue, course_grade);
                break;
            case 'q':
                queue = clear_queue(queue);
                return 0;
            default:
                printf("Illegal action code!\n");
        }
        printf("\n");
    }
}

//////////////////////////
// function definitions //
//////////////////////////
void show_help() {
    printf("List of action codes:\n");
    printf("\t'h' for help;\n");
    printf("\t'a' for adding a learner to the queue;\n");
    printf("\t'r' for removing a learner from the queue;\n");
    printf("\t'd' for displaying all learners in the queue;\n");
    printf("\t'g' for searching learners with a minimum GPA;\n");
    printf("\t'c' for searching learners with a minimum grade in the course;\n");
    printf("\t'q' to quit.\n");
}

void gather_data(char *full_name, char *student_id, char *course_grade, double *grade_point_average, int *retries) {
    if (full_name != NULL) {
        printf("Enter the full name of the learner: ");
        scanf("%[^\n]", full_name);
    }
    if (student_id != NULL) {
        printf("Enter the Student ID: ");
        scanf("%s", student_id);
    }
    if (course_grade != NULL) {
        printf("Enter the course letter grade: ");
        scanf(" %c", course_grade);
    }
    if (grade_point_average != NULL) {
        printf("Enter the GPA: ");
        scanf("%lf", grade_point_average);
    }
    if (retries != NULL) {
        printf("Enter the number of previous attempts: ");
        scanf("%d", retries);
    }
}

/// Function to map grades to numeric values for comparison
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

struct learner * enroll_learner(struct learner *queue, char *full_name, char *student_id, char course_grade, double grade_point_average, int retries) {
    struct learner *new_learner = malloc(sizeof(struct learner));
    if (new_learner == NULL) {
        printf("Error: malloc failed in enroll_learner\n");
        return queue;
    }
    // Copy the data
    strncpy(new_learner->full_name, full_name, MAX_NAME_LENGTH);
    new_learner->full_name[MAX_NAME_LENGTH] = '\0';  // Ensure null termination
    strncpy(new_learner->student_id, student_id, MAX_NETID_LENGTH);
    new_learner->student_id[MAX_NETID_LENGTH] = '\0';  // Ensure null termination
    new_learner->course_grade = toupper(course_grade); // Ensure uppercase
    new_learner->grade_point_average = grade_point_average;
    new_learner->retries = retries;
    new_learner->next_learner = NULL;

    // If the list is empty or new learner has higher retries than the head
    if (queue == NULL || new_learner->retries > queue->retries) {
        // Insert at the beginning
        new_learner->next_learner = queue;
        queue = new_learner;
        return queue;
    }

    struct learner *cur = queue;
    // Move forward past learners with retries greater than new learner's retries
    while (cur->next_learner != NULL && cur->next_learner->retries > new_learner->retries) {
        cur = cur->next_learner;
    }
    // Move forward past learners with same number of retries to maintain first come, first serve
    while (cur->next_learner != NULL && cur->next_learner->retries == new_learner->retries) {
        cur = cur->next_learner;
    }

    // Insert after cur
    new_learner->next_learner = cur->next_learner;
    cur->next_learner = new_learner;

    return queue;
}

struct learner * remove_learner(struct learner *queue) {
    if (queue == NULL) {
        // Do nothing if the list is empty
        return queue;
    }
    // Print the information of the first learner
    struct learner *first_learner = queue;

    // Output format
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Full Name           | Student ID           | Course  | GPA | Retries  |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", first_learner->full_name, first_learner->student_id, first_learner->course_grade, first_learner->grade_point_average, first_learner->retries);
    printf("|----------------------|----------------------|---------|-----|----------|\n");

    // Remove the learner from the queue
    queue = first_learner->next_learner;
    free(first_learner);

    return queue;
}

void display_learners(struct learner *queue) {
    if (queue == NULL) {
        // Do nothing
        return;
    }

    struct learner *cur = queue;

    // Output header
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Full Name           | Student ID           | Course  | GPA | Retries  |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");

    while (cur != NULL) {
        printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", cur->full_name, cur->student_id, cur->course_grade, cur->grade_point_average, cur->retries);
        printf("|----------------------|----------------------|---------|-----|----------|\n");
        cur = cur->next_learner;
    }
}

void display_min_gpa(struct learner *queue, double min_gpa) {
    int found = 0;
    struct learner *cur = queue;

    while (cur != NULL) {
        if (cur->grade_point_average >= min_gpa) {
            if (!found) {
                // Output header
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Full Name           | Student ID           | Course  | GPA | Retries  |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                found = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", cur->full_name, cur->student_id, cur->course_grade, cur->grade_point_average, cur->retries);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        cur = cur->next_learner;
    }
    // If no learners satisfy this condition, this function does nothing
}

void display_min_course_grade(struct learner *queue, int course_grade) {
    int found = 0;
    struct learner *cur = queue;
    char min_grade = toupper(course_grade);
    int min_grade_value = map_grade_value(min_grade);

    while (cur != NULL) {
        int cur_grade_value = map_grade_value(cur->course_grade);
        if (cur_grade_value >= min_grade_value) {
            if (!found) {
                // Output header
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Full Name           | Student ID           | Course  | GPA | Retries  |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                found = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", cur->full_name, cur->student_id, cur->course_grade, cur->grade_point_average, cur->retries);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        cur = cur->next_learner;
    }
    // If no learners satisfy this condition, this function does nothing
}

struct learner * clear_queue(struct learner *queue) {
    struct learner *cur = queue;
    while (cur != NULL) {
        struct learner *temp = cur;
        cur = cur->next_learner;
        free(temp);
    }
    return NULL;
}
