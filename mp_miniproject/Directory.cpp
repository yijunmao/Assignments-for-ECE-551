#include "Directory.h"

#include <dirent.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> Directory::seperate(std::string input, char seperator) {
  size_t prev = 0;
  size_t current = 0;
  std::vector<std::string> ans;

  current = input.find(seperator);

  while (current != std::string::npos) {
    ans.push_back(input.substr(prev, current - prev));
    prev = current + 1;
    current = input.find(seperator, prev);
  }

  if (prev < input.length()) {
    ans.push_back(input.substr(prev, current));
  }

  return ans;
}

std::vector<std::string> Directory::iniEnv() {
  char * ECE551PATH = getenv("PATH");
  std::string str(ECE551PATH);
  //std::cout << "PATH is " << str << std::endl;

  std::vector<std::string> ans = seperate(str, ':');
  /*
  for (typename std::vector<std::string>::iterator it = ans.begin(); it != ans.end(); ++it) {
    std::cout << "Directory is " << *it << std::endl;
  }
  */
  return ans;
}

bool Directory::searchProgram(const char * dirName, const char * progName) {
  DIR * dp = opendir(dirName);
  struct dirent * dirp;
  while ((dirp = readdir(dp)) != NULL) {
    if (strcmp(dirp->d_name, progName) == 0) {
      closedir(dp);
      return true;
    }
  }
  closedir(dp);
  return false;
}
