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

// Structure Definitions
#define MAX_NAME_LEN 100
#define MAX_ID_LEN 40

struct participant {
    char full_name[MAX_NAME_LEN+1], id[MAX_ID_LEN+1], course_grade;
    double performance_score;
    int retry_count;
    struct participant *next;
};

// Function Declarations //
void display_help();
void input_details(char *full_name, char *id, char *course_grade, double *performance_score, int *retry_count);
struct participant *add_participant(struct participant *list, char *full_name, char *id,
char course_grade, double performance_score, int retry_count);
struct participant *remove_participant(struct participant *list);
void display_participants(struct participant *list);
void filter_by_min_score(struct participant *list, double min_score);
void filter_by_min_grade(struct participant *list, int min_grade);
struct participant *clear_list(struct participant *list);

// Main Application
int main() {
    char operation;
    char full_name[MAX_NAME_LEN+1], id[MAX_ID_LEN+1], course_grade;
    double performance_score;
    int retry_count;
    struct participant *list = NULL;

    display_help();
    printf("\n");

    for (;;) {
        // Get user operation choice
        printf("Enter operation code: ");
        scanf(" %c", &operation);
        while (getchar() != '\n') /* Skip to end of line */
            ;

        // Execute operation
        switch (operation) {
            case 'h':
                display_help();
                break;
            case 'a':
                input_details(full_name, id, &course_grade, &performance_score, &retry_count);
                list = add_participant(list, full_name, id, course_grade, performance_score, retry_count);
                break;
            case 'r':
                list = remove_participant(list);
                break;
            case 'd':
                display_participants(list);
                break;
            case 's':
                input_details(NULL, NULL, NULL, &performance_score, NULL);
                filter_by_min_score(list, performance_score);
                break;
            case 'g':
                input_details(NULL, NULL, &course_grade, NULL, NULL);
                filter_by_min_grade(list, course_grade);
                break;
            case 'q':
                list = clear_list(list);
                return 0;
            default:
                printf("Invalid operation code!\n");
        }
        printf("\n");
    }
}

// Helper and Utility Implementations
void display_help() {
    printf("Available operation codes:\n");
    printf("\t'h' for help;\n");
    printf("\t'a' to add a participant to the list;\n");
    printf("\t'r' to remove a participant from the list;\n");
    printf("\t'd' to display all participants in the list;\n");
    printf("\t's' to find participants with a minimum performance score;\n");
    printf("\t'g' to find participants with a minimum grade;\n");
    printf("\t'q' to quit.\n");
}

void input_details(char *full_name, char *id, char *course_grade, double *performance_score, int *retry_count) {
    if (full_name != NULL) {
        printf("Enter participant's full name: ");
        scanf("%[^\n]", full_name);
    }
    if (id != NULL) {
        printf("Enter participant's ID: ");
        scanf("%s", id);
    }
    if (course_grade != NULL) {
        printf("Enter course letter grade: ");
        scanf(" %c", course_grade);
    }
    if (performance_score != NULL) {
        printf("Enter performance score: ");
        scanf("%lf", performance_score);
    }
    if (retry_count != NULL) {
        printf("Enter retry count: ");
        scanf("%d", retry_count);
    }
}

// Helper function for grade comparison
int get_grade_value(char grade) {
    switch (toupper(grade)) {
        case 'A': return 5;
        case 'B': return 4;
        case 'C': return 3;
        case 'D': return 2;
        case 'F': return 1;
        default:  return 0;
    }
}

struct participant *add_participant(struct participant *list, char *full_name, char *id, char course_grade, double performance_score, int retry_count) {
    struct participant *new_participant = malloc(sizeof(struct participant));
    if (new_participant == NULL) {
        printf("Error: Memory allocation failed in add_participant\n");
        return list;
    }

    // Populate new participant's data
    strncpy(new_participant->full_name, full_name, MAX_NAME_LEN);
    new_participant->full_name[MAX_NAME_LEN] = '\0';  // Ensure null termination
    strncpy(new_participant->id, id, MAX_ID_LEN);
    new_participant->id[MAX_ID_LEN] = '\0';  // Ensure null termination
    new_participant->course_grade = toupper(course_grade);
    new_participant->performance_score = performance_score;
    new_participant->retry_count = retry_count;
    new_participant->next = NULL;

    // Insert participant into the sorted list
    if (list == NULL || new_participant->retry_count > list->retry_count) {
        new_participant->next = list;
        list = new_participant;
        return list;
    }

    struct participant *current = list;
    while (current->next != NULL && current->next->retry_count >= new_participant->retry_count) {
        current = current->next;
    }

    new_participant->next = current->next;
    current->next = new_participant;

    return list;
}

struct participant *remove_participant(struct participant *list) {
    if (list == NULL) {
        return list;
    }

    struct participant *first_participant = list;

    // Display the removed participant's data
    printf("|------------------|------------------|-------|-----|---------|\n");
    printf("| Full Name        | ID               | Grade | Score | Retries |\n");
    printf("|------------------|------------------|-------|-----|---------|\n");
    printf("| %-16s | %-16s |     %c |  %.1f | %7d |\n", first_participant->full_name, first_participant->id, first_participant->course_grade, first_participant->performance_score, first_participant->retry_count);
    printf("|------------------|------------------|-------|-----|---------|\n");

    // Remove from the list
    list = first_participant->next;
    free(first_participant);

    return list;
}

void display_participants(struct participant *list) {
    if (list == NULL) {
        return;
    }

    struct participant *current = list;

    printf("|------------------|------------------|-------|-----|---------|\n");
    printf("| Full Name        | ID               | Grade | Score | Retries |\n");
    printf("|------------------|------------------|-------|-----|---------|\n");

    while (current != NULL) {
        printf("| %-16s | %-16s |     %c |  %.1f | %7d |\n", current->full_name, current->id, current->course_grade, current->performance_score, current->retry_count);
        printf("|------------------|------------------|-------|-----|---------|\n");
        current = current->next;
    }
}

void filter_by_min_score(struct participant *list, double min_score) {
    int found = 0;
    struct participant *current = list;

    while (current != NULL) {
        if (current->performance_score >= min_score) {
            if (!found) {
                printf("|------------------|------------------|-------|-----|---------|\n");
                printf("| Full Name        | ID               | Grade | Score | Retries |\n");
                printf("|------------------|------------------|-------|-----|---------|\n");
                found = 1;
            }
            printf("| %-16s | %-16s |     %c |  %.1f | %7d |\n", current->full_name, current->id, current->course_grade, current->performance_score, current->retry_count);
            printf("|------------------|------------------|-------|-----|---------|\n");
        }
        current = current->next;
    }
}

void filter_by_min_grade(struct participant *list, int min_grade) {
    int found = 0;
    struct participant *current = list;
    char target_grade = toupper(min_grade);
    int grade_threshold = get_grade_value(target_grade);

    while (current != NULL) {
        if (get_grade_value(current->course_grade) >= grade_threshold) {
            if (!found) {
                printf("|------------------|------------------|-------|-----|---------|\n");
                printf("| Full Name        | ID               | Grade | Score | Retries |\n");
                printf("|------------------|------------------|-------|-----|---------|\n");
                found = 1;
            }
            printf("| %-16s | %-16s |     %c |  %.1f | %7d |\n", current->full_name, current->id, current->course_grade, current->performance_score, current->retry_count);
            printf("|------------------|------------------|-------|-----|---------|\n");
        }
        current = current->next;
    }
}

struct participant *clear_list(struct participant *list) {
    struct participant *current = list;
    while (current != NULL) {
        struct participant *temp = current;
        current = current->next;
        free(temp);
    }
    return NULL;
}
