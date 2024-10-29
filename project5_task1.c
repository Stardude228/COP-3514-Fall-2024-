/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: Write a C program that splits  */
/* a two-word string into two strings each containing one word. */
/*************************************/

#include <stdio.h>
#define MAX_LENGTH 1000

// Reads a line of input and stores it in 'buffer'
void read_input(char *buffer) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        *buffer++ = (char)ch;
    }
    *buffer = '\0'; // Null-terminate the string
}

// Separates the input into two words and stores them in 'first' and 'second'
void split_words(char *input, char *first, char *second) {
    // Move past leading spaces
    while (*input == ' ') {
        input++;
    }

    // Extract first word
    while (*input != ' ' && *input != '\0') {
        *first++ = *input++;
    }
    *first = '\0'; // Null-terminate first word

    // Move past spaces between words
    while (*input == ' ') {
        input++;
    }

    // Extract second word
    while (*input != ' ' && *input != '\0') {
        *second++ = *input++;
    }
    *second = '\0'; // Null-terminate second word
}

int main() {
    char input[MAX_LENGTH];
    char first_word[MAX_LENGTH];
    char second_word[MAX_LENGTH];

    printf("Enter input: ");
    read_input(input); // Get input from the user

    split_words(input, first_word, second_word); // Split input into words

    // Display results
    printf("Word #1: %s\n", first_word);
    printf("Word #2: %s\n", second_word);

    return 0;
}
