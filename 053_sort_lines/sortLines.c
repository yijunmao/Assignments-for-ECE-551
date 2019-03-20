#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

struct data_tag {
  char ** lines;
  size_t count;
};
typedef struct data_tag data_t;

void printresults(char ** lines, size_t sz) {
  for (size_t j = 0; j < sz; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

data_t SortStdin(void) {
  char * curr = NULL;
  size_t sz = 0;
  char ** lines = NULL;
  size_t i = 0;

  while (getline(&curr, &sz, stdin) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }

  free(curr);
  sortData(lines, i);

  data_t datastdin;
  datastdin.lines = lines;
  datastdin.count = i;

  return datastdin;
}

data_t SortFromFile(char * inputfilename) {
  // open file
  FILE * f = fopen(inputfilename, "r");
  if (f == NULL) {
    perror("Open file failed");
    exit(EXIT_FAILURE);
  }

  char * curr = NULL;
  size_t sz = 0;
  char ** lines = NULL;
  size_t i = 0;

  while (getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }

  free(curr);
  sortData(lines, i);

  data_t datafromfile;
  datafromfile.lines = lines;
  datafromfile.count = i;
  //return datafromfile;

  if (fclose(f) != 0) {
    perror("Close file failed");
    exit(EXIT_FAILURE);
  }
  return datafromfile;
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 0) {
    fprintf(stderr, "Usage: programname filename!\n");
    return EXIT_FAILURE;
  }

  else if (argc == 1) {
    data_t datastdin = SortStdin();
    char ** lines = datastdin.lines;
    size_t count = datastdin.count;
    printresults(lines, count);
  }

  else if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      data_t datafromfile = SortFromFile(argv[i]);
      char ** lines = datafromfile.lines;
      size_t count = datafromfile.count;
      printresults(lines, count);
      //free(lines);
      //free(datafromfile.lines);
      //free(&datafromfile);
    }
  }
  return EXIT_SUCCESS;
}
