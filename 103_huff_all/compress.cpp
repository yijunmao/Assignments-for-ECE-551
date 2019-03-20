#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  std::ifstream myFile;
  myFile.open(inFile);
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  if (myFile.is_open()) {
    if (myFile.good()) {
      char c;
      while (myFile.get(c)) {
        // c++ style to read a character is like that
        // fstream in;
        // in.open(filename.txt);
        // char c;
        // in >> c;
        // cout << c << endl;

        // check if the character is in the map
        // using map.find instead of map[] since map is const and map[] may try to modify it and can cause error
        std::map<unsigned, BitString>::const_iterator it = theMap.find((unsigned char)c);
        assert(it != theMap.end());
        // take the corresponding bitstring and write that into output file
        bfw.writeBitString(it->second);
      }
      // explicitly write EOF bitstring
      std::map<unsigned, BitString>::const_iterator it = theMap.find(256);
      assert(it != theMap.end());
      bfw.writeBitString(it->second);
    }
  }
  else {
    std::cerr << "Open file failed!\n";
  }

  //dont forget to lookup 256 for the EOF marker, and write it out.

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
  myFile.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this

  // step 1: count frequency
  uint64_t * counts = readFrequencies(argv[1]);
  assert(counts != NULL);

  // step 2: build tree
  Node * tree = buildTree(counts);
  delete[] counts;

  // step 3: build map (sym, encoding)
  std::map<unsigned, BitString> theMap;
  BitString empty;
  tree->buildMap(empty, theMap);
  delete tree;

  // step 4: write compress output
  writeCompressedOutput(argv[1], argv[2], theMap);

  return EXIT_SUCCESS;
}
