/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: Write a C program that splits  */
/* a two-word string into two strings each containing one word. */
/*************************************/

#include <stdio.h>
#define MAX_LENGTH 1000

// Processes input, extracts two words directly, and stores them in 'word1' and 'word2'
void process_input(char *word1, char *word2) {
    char *ptr = word1;
    int ch;
    int word_count = 0;

    // Read input directly into 'word1' until we hit a space, then switch to 'word2'
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch == ' ' && word_count == 0) {
            *ptr = '\0';  // End first word
            ptr = word2;  // Switch to second word
            word_count++;
        } else if (ch != ' ' || word_count == 1) {
            *ptr++ = (char)ch;  // Continue reading second word
        }
    }
    *ptr = '\0'; // Null-terminate last word
}

int main() {
    char first[MAX_LENGTH];
    char second[MAX_LENGTH];

    printf("Enter input: ");
    process_input(first, second);  // Process input and split into words

    printf("Word #1: %s\n", first);
    printf("Word #2: %s\n", second);

    return 0;
}