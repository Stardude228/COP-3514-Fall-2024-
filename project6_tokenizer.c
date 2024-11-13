/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: A tokenizer program converts text */
/* into a sequence of tokens. One simple tokenization method */
/* consists of converting words into numbers. First, the method */
/* identifies all unique words in a corpora, and then assign a */
/* different number to each of these words. */
/*************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 10000
#define MAX_ENTRY_LENGTH 100

// Structure to store words and their indices
typedef struct {
    char text[MAX_ENTRY_LENGTH];
    int index;
} DictionaryEntry;

// Function prototypes
int compareEntries(const void *a, const void *b);
int searchDictionary(DictionaryEntry *entries, int totalEntries, const char *target);
void processInputFile(FILE *inputFile, DictionaryEntry *entries, int *totalEntries);
void outputDictionary(FILE *outputFile, DictionaryEntry *entries, int totalEntries);
void replaceWordsWithIndices(FILE *inputFile, FILE *outputFile, DictionaryEntry *entries, int totalEntries);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");
    if (!inputFile || !outputFile) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    DictionaryEntry entries[MAX_ENTRIES];
    int totalEntries = 0;

    processInputFile(inputFile, entries, &totalEntries);

    qsort(entries, totalEntries, sizeof(DictionaryEntry), compareEntries);

    for (int i = 0; i < totalEntries; i++) {
        entries[i].index = i + 1;
    }

    outputDictionary(outputFile, entries, totalEntries);

    fseek(inputFile, 0, SEEK_SET);
    replaceWordsWithIndices(inputFile, outputFile, entries, totalEntries);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

// Function to compare entries for alphabetical sorting
int compareEntries(const void *a, const void *b) {
    return strcmp(((DictionaryEntry *)a)->text, ((DictionaryEntry *)b)->text);
}

// Function to search for a word in the dictionary
int searchDictionary(DictionaryEntry *entries, int totalEntries, const char *target) {
    for (int i = 0; i < totalEntries; i++) {
        if (strcmp(entries[i].text, target) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to process input file and store unique words in the dictionary
void processInputFile(FILE *inputFile, DictionaryEntry *entries, int *totalEntries) {
    char buffer[MAX_ENTRY_LENGTH];
    int character, bufferIndex = 0;

    while ((character = fgetc(inputFile)) != EOF) {
        if (character == ' ' || character == '.' || character == '\n') {
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';
                if (searchDictionary(entries, *totalEntries, buffer) == -1) {
                    strcpy(entries[*totalEntries].text, buffer);
                    (*totalEntries)++;
                }
                bufferIndex = 0;
            }
        } else {
            buffer[bufferIndex++] = character;
        }
    }
}

// Function to output the dictionary and the number of unique words
void outputDictionary(FILE *outputFile, DictionaryEntry *entries, int totalEntries) {
    fprintf(outputFile, "%d\n", totalEntries);
    for (int i = 0; i < totalEntries; i++) {
        fprintf(outputFile, "%s\n", entries[i].text);
    }
}

// Function to replace words with their indices in the output file
void replaceWordsWithIndices(FILE *inputFile, FILE *outputFile, DictionaryEntry *entries, int totalEntries) {
    char buffer[MAX_ENTRY_LENGTH];
    int character, bufferIndex = 0;

    while ((character = fgetc(inputFile)) != EOF) {
        if (character == ' ' || character == '\n' || character == '.') {
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';
                int wordIndex = searchDictionary(entries, totalEntries, buffer);
                if (wordIndex != -1) {
                    fprintf(outputFile, "%d", entries[wordIndex].index);
                }
                bufferIndex = 0;

                if (character == ' ' || character == '\n') {
                    fputc(' ', outputFile);
                } else if (character == '.') {
                    fputc('\n', outputFile);
                }
            }
        } else {
            buffer[bufferIndex++] = character;
        }
    }
}
