#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}

uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  // open the file

  std::ifstream f(fname);

  if (f.is_open()) {
    // initialize an array and integer encoded for character
    uint64_t * freqArr = new uint64_t[257];

    for (int i = 0; i < 257; i++) {
      freqArr[i] = 0;
    }
    char c;

    // read character out of the file one by one
    while (f.get(c)) {
      freqArr[(unsigned char)c]++;
    }

    freqArr[256]++;

    // close the file
    f.close();

    // return the array
    return freqArr;
  }

  else {
    perror("Open file failed!\n");
    exit(EXIT_FAILURE);
  }
}
