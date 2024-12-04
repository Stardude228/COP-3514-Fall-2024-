/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: Your task is to modify your program for project 7 so that it uses quick sort to sort  */
/* the customers by number of lessons. Use the quick sort library function and implement the comparison function.  */
/*************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro definitions
#define MAX_ENTRIES 200
#define MAX_STR_LEN 100

// Define struct
typedef struct {
    char contact[MAX_STR_LEN];
    int sessions;
    char fullname[MAX_STR_LEN];
} Participant;

// Comparison function for qsort to sort in descending order
int compare_sessions(const void *a, const void *b) {
    const Participant *partA = (const Participant *)a;
    const Participant *partB = (const Participant *)b;
    return partB->sessions - partA->sessions;
}

int main() {
    // Define variables
    FILE *input_data, *output_data;
    Participant participants[MAX_ENTRIES];
    int entry_count = 0;

    // Open input file
    input_data = fopen("customers.csv", "r");
    if (!input_data) {
        perror("Error opening input file");
        return 1; // End program upon error
    }

    // Read participant data from input file using fscanf
    while (fscanf(input_data, "%[^,],%d,%[^\n]\n", // Use required processing method
                  participants[entry_count].contact,
                  &participants[entry_count].sessions,
                  participants[entry_count].fullname) == 3) {
        entry_count++;
    }

    // Close the input file
    fclose(input_data);

    // Sort participants by number of sessions in descending order
    qsort(participants, entry_count, sizeof(Participant), compare_sessions);

    // Open the output file
    output_data = fopen("result.csv", "w");
    if (!output_data) {
        perror("Error creating output file");
        
        // End program after error
        return 1;
    }

    // Write sorted participants to the output file
    for (int i = 0; i < entry_count; i++) {
        fprintf(output_data, "%s, %d,   %s\n",
                participants[i].contact,
                participants[i].sessions,
                participants[i].fullname);
    }

    // Close the output file
    fclose(output_data);

    printf("Sorted results have been written to result.csv\n");
    
    // End program
    return 0;
}
