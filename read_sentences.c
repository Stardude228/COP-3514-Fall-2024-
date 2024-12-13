#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int read_line(char str[], int n);
int compare_strings(const void *p, const void *q);

int main() {
  char input_buffer[1001];
  int length = 0;
  char *sentence = NULL;
  char *sentences[50];
  int num_sentences = 0;

  printf("Please type a sentence: ");
  read_line(input_buffer, 1000);

  length = strlen(input_buffer);
  printf("Allocating %d bytes to hold the sentence\n\n", length + 1);

  sentence = malloc(length + 1);
  if (sentence == NULL) {
    printf("malloc failed");
    return 0;
  }

  strcpy(sentence, input_buffer);
  printf("Original sentence: %s\n", sentence);

  char *token = strtok(sentence, " ");
  while (token != NULL && num_sentences < 50) {
    sentences[num_sentences++] = token;
    token = strtok(NULL, " ");
  }

  qsort(sentences, num_sentences, sizeof(char *), compare_strings);

  printf("Sorted words:\n");
  for (int i = 0; i < num_sentences; i++) {
    printf("%s\n", sentences[i]);
  }
  
  free(sentence);
  return 0;
}

int read_line(char str[], int n) {
  int ch, i = 0;

  while ((ch = getchar()) != '\n') {
    if (i < n)
      str[i++] = ch;
  }
  str[i] = '\0';
  return i;
}

int compare_strings(const void *p, const void *q) {
  return strcmp(*(char **)p, *(char **)q);
}
