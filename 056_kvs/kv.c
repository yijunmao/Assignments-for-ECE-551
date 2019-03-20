#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function shortens the string to include only the first null terminator
char * strshort(char srcStr[]) {
  //count the number of chars
  int count = 0;
  char * p = srcStr;
  while (*p != '\0') {
    count++;
    p++;
  }

  //malloc a space for the string
  int numChar = count + 1;  //include null terminator
  char * destStr = malloc(numChar * sizeof(*destStr));

  //copy the src string into dest string
  strncpy(destStr, srcStr, numChar);

  //return the string end with null
  return destStr;
}

//function splits the string into two strings: key and value
char ** split(char * curr) {
  // create two strings for key and value
  int lenCurr = strlen(curr) + 1;
  char strKey[lenCurr];
  char strValue[lenCurr];

  for (int i = 0; i < lenCurr; i++) {
    strKey[i] = '\0';
    strValue[i] = '\0';
  }

  //check if the first char is equals sign
  if (curr[0] == '=') {
    fprintf(stderr, "The first character in the string is equals sign! No valid key!\n");
    exit(EXIT_FAILURE);
  }

  //split the string into two
  char * pcurr = curr;
  char * pkey = strKey;
  char * pvalue = strValue;
  int equalCount = 0;

  while (*pcurr != '\n') {
    if ((*pcurr) == '=') {
      equalCount++;

      if (equalCount == 1) {
        pcurr++;
      }

      else if (equalCount > 1) {
        *pvalue = *pcurr;
        pcurr++;
        pvalue++;
      }
    }

    else if (equalCount < 1) {
      *pkey = *pcurr;
      pcurr++;
      pkey++;
    }

    else if (equalCount >= 1) {
      *pvalue = *pcurr;
      pcurr++;
      pvalue++;
    }
  }

  //check if no equal sign
  if (pvalue == strValue) {
    fprintf(stderr, "There is no equal sign in the string!\n");
    exit(EXIT_FAILURE);
  }

  //short string
  char * key = strshort(strKey);
  char * value = strshort(strValue);

  char ** splitted = malloc(2 * sizeof(*splitted));
  splitted[0] = key;
  splitted[1] = value;

  return splitted;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  //open the file and check open status
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Open file failed");
    exit(EXIT_FAILURE);
  }

  //initialize kvarray, curr, sz, and index i
  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  kvarray->numPairs = 0;
  kvarray->kvpair = NULL;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;

  //read the lines of text
  while (getline(&curr, &sz, f) >= 0) {
    //split the string into key and value strings
    char ** splitted = split(curr);
    //realloc memeory to kvpair
    kvarray->numPairs++;
    kvarray->kvpair = realloc(kvarray->kvpair, (i + 1) * sizeof(*(kvarray->kvpair)));
    kvarray->kvpair[i] = NULL;
    kvarray->kvpair[i] = realloc(kvarray->kvpair[i], sizeof(*(kvarray->kvpair[i])));
    //add results to kvpair array
    (kvarray->kvpair)[i]->key = splitted[0];
    (kvarray->kvpair)[i]->value = splitted[1];
    i++;
    //free pointer array splitted
    free(splitted);
  }

  //free curr
  free(curr);

  //close the file
  if (fclose(f) != 0) {
    perror("Close file failed");
    exit(EXIT_FAILURE);
  }

  //return kvarray_t *
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  //free key, value pairs
  //free struct for key, value pairs
  //free kvpair array
  //free kvpair struct
  for (int i = 0; i < pairs->numPairs; i++) {
    free(pairs->kvpair[i]->key);
    free(pairs->kvpair[i]->value);
    free(pairs->kvpair[i]);
  }
  free(pairs->kvpair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->numPairs; i++) {
    char * keyprint = pairs->kvpair[i]->key;
    char * valueprint = pairs->kvpair[i]->value;
    printf("key = '%s' value = '%s'\n", keyprint, valueprint);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->numPairs; i++) {
    if (!strcmp(pairs->kvpair[i]->key, key)) {
      return pairs->kvpair[i]->value;
    }
  }
  return NULL;
}
