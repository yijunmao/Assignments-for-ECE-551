#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Read character one by one
// Check if it reaches EOF
// Check if character is a letter
// Transfer all letters to lowercase
// Count its relative position to 'a'
// Increases the corresponding array element by one
int freq_count(FILE * stream, int * arr) {
  int itr_flag = 0;
  int c;
  while ((c = fgetc(stream)) != EOF) {
    if (isalpha(c)) {
      itr_flag = 1;
      c = tolower(c);
      c = c - 'a';
      arr[c] += 1;
    }
  }
  return itr_flag;
}

// Find the key
int find_key(int * arr, char letter) {
  int max_index = 0;
  int max_value = arr[0];
  for (int i = 1; i < 26; i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];
      max_index = i;
    }
  }
  int key = max_index - (letter - 'a');
  if (key < 0) {
    key += 26;
  }
  return key;
}

// Take one command line argument and check argc
// Open the file to be read and check its return value
// Formulate the counting array
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./breaker filename\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Failure when opening file");
    return EXIT_FAILURE;
  }
  int arr[26] = {0};
  int null_flag = freq_count(f, arr);
  if (null_flag > 0) {
    char letter = 'e';
    int key = find_key(arr, letter);
    printf("%d\n", key);
  }
  if (fclose(f) != 0) {
    perror("Closed file failure");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
