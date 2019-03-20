#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  //allocate memory for a count_t structure
  //initialize it to represent nothing has been counted yet
  counts_t * counts = malloc(sizeof(*counts));
  /*counts->nameCount = malloc((counts->numNames) * sizeof(*(counts->nameCount)));
  for (int i = 0; i < counts->numNames; i++) {
    (counts->nameCount)[i] = malloc(sizeof(*((counts->nameCount)[i])));
    counts->nameCount[i]->name = malloc(sizeof(*(counts->nameCount[i]->name)));
    counts->nameCount[i]->numCounts = 0;
    }*/
  counts->nameCount = NULL;
  counts->numNames = 0;
  counts->unknown = 0;
  return counts;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  //check if it's an unknown name
  if (name == NULL) {
    (c->unknown)++;
  }

  //define a string with same content as const string name and allocate a space for it
  else {
    int lenName = strlen(name) + 1;

    //first count
    if (c->numNames == 0) {
      c->nameCount = realloc(c->nameCount, sizeof(*(c->nameCount)));
      (c->nameCount)[0] = malloc(sizeof(*((c->nameCount)[0])));
      c->nameCount[0]->name = malloc(lenName * sizeof(*(c->nameCount[0]->name)));

      //put character in the name string into name field
      for (int i = 0; i < lenName; i++) {
        c->nameCount[0]->name[i] = '\0';
      }
      const char * psrc = name;
      char * pdest = c->nameCount[0]->name;
      while (*psrc != '\0') {
        *pdest = *psrc;
        psrc++;
        pdest++;
      }

      c->nameCount[0]->numCounts = 1;
      (c->numNames)++;
    }
    //following counts
    else {
      //if name already exists
      int itr = 0;
      for (int i = 0; i < c->numNames; i++) {
        if (!strcmp(name, c->nameCount[i]->name)) {
          (c->nameCount[i]->numCounts)++;
          break;
        }
        itr++;
      }
      //if name does not exist
      if (itr == c->numNames) {
        (c->numNames)++;
        c->nameCount = realloc(c->nameCount, (c->numNames) * sizeof(*(c->nameCount)));
        c->nameCount[(c->numNames) - 1] = malloc(sizeof(*(c->nameCount[(c->numNames) - 1])));
        c->nameCount[(c->numNames) - 1]->name =
            malloc(lenName * sizeof(*(c->nameCount[(c->numNames) - 1]->name)));
        //put character in the name string into name field
        for (int i = 0; i < lenName; i++) {
          c->nameCount[(c->numNames) - 1]->name[i] = '\0';
        }
        const char * psrc = name;
        char * pdest = c->nameCount[(c->numNames) - 1]->name;
        while (*psrc != '\0') {
          *pdest = *psrc;
          psrc++;
          pdest++;
        }

        c->nameCount[(c->numNames) - 1]->numCounts = 1;
      }
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  //print parts other than unknown
  for (int i = 0; i < c->numNames; i++) {
    //  char * name = c->nameCount[i]->name;
    int numCounts = c->nameCount[i]->numCounts;
    fprintf(outFile, "%s: %d\n", c->nameCount[i]->name, numCounts);
  }
  //print unknown
  if (c->unknown != 0) {
    fprintf(outFile, "<unknown>: %d\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  //free struct one_count and name
  for (int i = 0; i < c->numNames; i++) {
    free(c->nameCount[i]->name);
    free(c->nameCount[i]);
  }
  //free nameCount and struct count
  free(c->nameCount);
  free(c);
}
