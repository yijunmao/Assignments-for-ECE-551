#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 12

int check_special(char * str) {
  for (int i = 0; i < 10; i++) {
    if ((int)str[i] > 255 || (int)str[i] < 0) {
      fprintf(stderr, "There are non printable characters in the string!\n");
      return 1;
    }
  }
  return 0;
}

void rotate(char array[10][11], char * line, int line_count) {
  for (int i = 0; i < 10; i++) {
    array[i][9 - line_count] = line[i];
  }
}

void printout(char array[10][11]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", array[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: filename\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("Open file failed");
    return EXIT_FAILURE;
  }

  char line[LINE_SIZE];
  for (int i = 0; i < LINE_SIZE; i++) {
    line[i] = '\0';
  }

  int line_count = 0;

  char rotatedMatrix[10][11];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 11; j++) {
      rotatedMatrix[i][j] = '\0';
    }
  }

  while (fgets(line, LINE_SIZE, f) != NULL) {
    line_count += 1;
    if (line_count > 10) {
      fprintf(stderr, "There are too many lines!\n");
      return EXIT_FAILURE;
    }
    else {
      char * p = strchr(line, '\n');
      if (p == NULL) {
        fprintf(stderr, "The line is too long!\n");
        return EXIT_FAILURE;
      }
      else if (p != (line + 10)) {
        fprintf(stderr, "The line is too short!\n");
        return EXIT_FAILURE;
      }
      else {
        int IsSpecial = check_special(line);
        if (IsSpecial == 1) {
          fprintf(stderr, "There are unprintable characters in the file!\n");
          return EXIT_FAILURE;
        }
        else {
          rotate(rotatedMatrix, line, line_count - 1);
        }
      }
    }
  }

  if (fclose(f) != 0) {
    perror("File close failed");
    return EXIT_FAILURE;
  }

  if (line_count != 10) {
    fprintf(stderr, "There are too few lines\n");
    return EXIT_FAILURE;
  }
  else {
    printout(rotatedMatrix);
  }
  return EXIT_SUCCESS;
}
