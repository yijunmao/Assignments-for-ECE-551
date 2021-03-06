#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void sortFromFile(char * filename) {
  // open file
  std::ifstream input(filename);
  if (input.fail()) {
    std::cerr << "File does not exist or some other error!" << std::endl;
    exit(EXIT_FAILURE);
  }
  // read lines from file
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input, line)) {
    // getlines reads a line from a stream and puts it in a string
    // adds the newly read line into a vector
    lines.push_back(line);
  }
  // std::cout << lines.size();
  // sort strings
  std::sort(lines.begin(), lines.end());
  // print the results
  for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    std::cout << *it << '\n';
  }
  // close the file
  input.close();
}

void sortStdin(void) {
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(std::cin, line)) {
    lines.push_back(line);
  }
  // sort strings
  std::sort(lines.begin(), lines.end());
  // print the results
  for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    std::cout << *it << '\n';
  }
}

//std::getline
int main(int argc, char ** argv) {
  if (argc == 0) {
    std::cout << "Usage: programname filename!" << std::endl;
    return EXIT_FAILURE;
  }

  else if (argc == 1) {
    sortStdin();
  }

  else if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      sortFromFile(argv[i]);
    }
  }
  return EXIT_SUCCESS;
}
