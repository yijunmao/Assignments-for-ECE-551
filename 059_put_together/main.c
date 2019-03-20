#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

int strCount(char * str) {
  char * p = str;
  int count = 0;
  while (*p != '\0') {
    count++;
    p++;
  }
  return count;
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  //create counts
  counts_t * counts = createCounts();

  //open a file and check your open status
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Open file failed");
    exit(EXIT_FAILURE);
  }

  //getline to read that line
  char * curr = NULL;
  size_t sz = 0;

  while (getline(&curr, &sz, f) >= 0) {
    //compare the string with key field in kvpairs
    int itr = 0;
    for (int i = 0; i < kvPairs->numPairs; i++) {
      //modify the raw string
      stripNewline(curr);
      int unnullCount = strCount(curr);
      char curr_modified[unnullCount + 1];
      strncpy(curr_modified, curr, unnullCount + 1);

      //if find a matched key
      if (!strcmp(curr_modified, kvPairs->kvpair[i]->key)) {
        const char * name = kvPairs->kvpair[i]->value;
        addCount(counts, name);
        break;
      }
      itr++;
    }
    //if no matched key is found
    if (itr == kvPairs->numPairs) {
      const char * name = NULL;
      addCount(counts, name);
    }
  }
  //free the line
  free(curr);

  //close the file
  if (fclose(f) != 0) {
    perror("File close error");
    exit(EXIT_FAILURE);
  }

  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "Not correct number of input files!\n");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      perror("Open file failed");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);

    //close f
    if (fclose(f) != 0) {
      perror("Close file failed");
      return EXIT_FAILURE;
    }

    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
