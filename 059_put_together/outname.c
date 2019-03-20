#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  //compute the inputName length
  size_t lenInputName = strlen(inputName);

  //initialize the outname string, the final character for null terminator
  const char * append = ".counts";
  size_t lenOutputName = lenInputName + 8;
  char outputName[lenOutputName];
  for (size_t i = 0; i < lenOutputName; i++) {
    outputName[i] = '\0';
  }

  //fill in the outName char array
  const char * pin = inputName;
  const char * pappend = append;
  char * pout = outputName;

  while ((*pin) != '\0') {
    *pout = *pin;
    pin++;
    pout++;
  }

  while ((*pappend) != '\0') {
    *pout = *pappend;
    pappend++;
    pout++;
  }

  //allocate memory for the string of output file name
  char * outName = malloc(lenOutputName * sizeof(*outName));

  //fill in the allocated memeory
  for (size_t i = 0; i < lenOutputName; i++) {
    outName[i] = outputName[i];
  }

  return outName;
}
