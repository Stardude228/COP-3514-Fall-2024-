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

// data definitions 
#define MAX_NAME_LEN 100
#define MAX_ID_LEN 40

struct participant {
    char full_name[MAX_NAME_LEN+1], id[MAX_ID_LEN+1], course_grade;
    double performance_score;
    int retry_count;
    struct participant *next;
};

// function prototypes 
void display_help();
void input_data(char *full_name, char *id, char *course_grade, double *performance_score, int *retry_count);
struct participant *add_participant(struct participant *list, char *full_name, char *id,
char course_grade, double performance_score, int retry_count);
struct participant *remove_participant(struct participant *list);
void display_participants(struct participant *list);
void filter_min_score(struct participant *list, double performance_score);
void filter_min_grade(struct participant *list, int course_grade);
struct participant *clear_list(struct participant *list);

// main function
int main() {
    char operation;
    char full_name[MAX_NAME_LEN+1], id[MAX_ID_LEN+1], course_grade;
    double performance_score;
    int retry_count;
    struct participant *list = NULL;

    display_help();
    printf("\n");

    for (;;) {
        // read operation code
        printf("Enter operation code: ");
        scanf(" %c", &operation);
        while (getchar() != '\n') /* skips to end of line */
            ;

        // run operation
        switch (operation) {
            case 'h':
                display_help();
                break;
            case 'a':
                input_data(full_name, id, &course_grade, &performance_score, &retry_count);
                list = add_participant(list, full_name, id, course_grade, performance_score, retry_count);
                break;
            case 'r':
                list = remove_participant(list);
                break;
            case 'd':
                display_participants(list);
                break;
            case 's':
                input_data(NULL, NULL, NULL, &performance_score, NULL);
                filter_min_score(list, performance_score);
                break;
            case 'g':
                input_data(NULL, NULL, &course_grade, NULL, NULL);
                filter_min_grade(list, course_grade);
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

// function definitions
void display_help() {
    printf("List of operation codes:\n");
    printf("\t'h' for help;\n");
    printf("\t'a' for adding a participant to the list;\n");
    printf("\t'r' for removing a participant from the list;\n");
    printf("\t'd' for displaying all participants in the list;\n");
    printf("\t's' for searching participants with a minimum score;\n");
    printf("\t'g' for searching participants with a minimum grade;\n");
    printf("\t'q' to quit.\n");
}

void input_data(char *full_name, char *id, char *course_grade, double *performance_score, int *retry_count) {
    if (full_name != NULL) {
        printf("Enter the participant's full name: ");
        scanf("%[^\n]", full_name);
    }
    if (id != NULL) {
        printf("Enter the participant's ID: ");
        scanf("%s", id);
    }
    if (course_grade != NULL) {
        printf("Enter the course letter grade: ");
        scanf(" %c", course_grade);
    }
    if (performance_score != NULL) {
        printf("Enter the performance score: ");
        scanf("%lf", performance_score);
    }
    if (retry_count != NULL) {
        printf("Enter the number of retries: ");
        scanf("%d", retry_count);
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

struct participant * add_participant(struct participant *list, char *full_name, char *id, char course_grade, double performance_score, int retry_count) {
    struct participant *new_participant = malloc(sizeof(struct participant));
    if (new_participant == NULL) {
        printf("Error: malloc failed in add_participant\n");
        return list;
    }
    // Copy the data
    strncpy(new_participant->full_name, full_name, MAX_NAME_LEN);
    new_participant->full_name[MAX_NAME_LEN] = '\0';  // Ensure null termination
    strncpy(new_participant->id, id, MAX_ID_LEN);
    new_participant->id[MAX_ID_LEN] = '\0';  // Ensure null termination
    new_participant->course_grade = toupper(course_grade); // Ensure uppercase
    new_participant->performance_score = performance_score;
    new_participant->retry_count = retry_count;
    new_participant->next = NULL;

    // If the list is empty or new participant has higher retries than the head
    if (list == NULL || new_participant->retry_count > list->retry_count) {
        // Insert at the beginning
        new_participant->next = list;
        list = new_participant;
        return list;
    }

    struct participant *cur = list;
    // Move forward past participants with retries greater than the new participant
    while (cur->next != NULL && cur->next->retry_count > new_participant->retry_count) {
        cur = cur->next;
    }
    // Move forward past participants with same retries to maintain first come, first serve
    while (cur->next != NULL && cur->next->retry_count == new_participant->retry_count) {
        cur = cur->next;
    }

    // Insert after cur
    new_participant->next = cur->next;
    cur->next = new_participant;

    return list;
}

struct participant * remove_participant(struct participant *list) {
    if (list == NULL) {
        // Do nothing if the list is empty
        return list;
    }
    // Print the information of the first participant
    struct participant *first_participant = list;

    // Output format
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Full Name            | ID                   | Grade   | Score | Retries |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", first_participant->full_name, first_participant->id, first_participant->course_grade, first_participant->performance_score, first_participant->retry_count);
    printf("|----------------------|----------------------|---------|-----|----------|\n");

    // Remove the participant from the list
    list = first_participant->next;
    free(first_participant);

    return list;
}

void display_participants(struct participant *list) {
    if (list == NULL) {
        // Do nothing
        return;
    }

    struct participant *cur = list;

    // Output header
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Full Name            | ID                   | Grade   | Score | Retries |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");

    while (cur != NULL) {
        printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", cur->full_name, cur->id, cur->course_grade, cur->performance_score, cur->retry_count);
        printf("|----------------------|----------------------|---------|-----|----------|\n");
        cur = cur->next;
    }
}

void filter_min_score(struct participant *list, double min_score) {
    int found = 0;
    struct participant *cur = list;

    while (cur != NULL) {
        if (cur->performance_score >= min_score) {
            if (!found) {
                // Output header
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Full Name            | ID                   | Grade   | Score | Retries |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                found = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", cur->full_name, cur->id, cur->course_grade, cur->performance_score, cur->retry_count);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        cur = cur->next;
    }
}

void filter_min_grade(struct participant *list, int course_grade) {
    int found = 0;
    struct participant *cur = list;
    char min_grade = toupper(course_grade);
    int min_grade_value = grade_value(min_grade);

    while (cur != NULL) {
        int cur_grade_value = grade_value(cur->course_grade);
        if (cur_grade_value >= min_grade_value) {
            if (!found) {
                // Output header
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                printf("| Full Name            | ID                   | Grade   | Score | Retries |\n");
                printf("|----------------------|----------------------|---------|-----|----------|\n");
                found = 1;
            }
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n", cur->full_name, cur->id, cur->course_grade, cur->performance_score, cur->retry_count);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        cur = cur->next;
    }
}

struct participant * clear_list(struct participant *list) {
    struct participant *cur = list;
    while (cur != NULL) {
        struct participant *temp = cur;
        cur = cur->next;
        free(temp);
    }
    return NULL;
}
