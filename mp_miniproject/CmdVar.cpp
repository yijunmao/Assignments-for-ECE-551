// I keep track of the variables which have been set by the user using a STL map<string, string>
// The first element in the map is the name of the variable while the second is its value

#include "CmdVar.h"

#include <ctype.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>

void CmdVar::printPrompt() {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("getcwd() error");
  }
  else {
    std::cout << "myShell:" << cwd << " $";
  }
}

// set var_1 2
// set b $var_11var_1
// echo $b you will get 212
void CmdVar::replaceVar() {
  for (std::map<std::string, std::string>::iterator it = varmap.begin(); it != varmap.end(); ++it) {
    size_t index = 0;
    std::string toFind = "$" + it->first;
    // find and replace all the occurences of a variable
    index = content.find(toFind);
    while (index != std::string::npos) {
      content.replace(index, toFind.size(), (it->second));
      index = content.find(toFind, index + (it->second).size());
    }
  }
}

// set var_1 2
// set b $var_11var_1
// echo $b you will get empty
/*void CmdVar::replaceVar() {
  size_t start = 0;
  size_t end = 0;
  std::string replaced = "";
  for (size_t i = 0; i < content.size(); i++) {
    if (content[i] == '$') {
      start = i + 1;
      end = i + 2;
      // is number, alphabet, or underscore
      while (end < content.size() && (isalnum(content[end]) || content[end] == '_')) {
        end++;
      }
      std::string toFind = content.substr(start, end - start);
      if (varmap.find(toFind) != varmap.end()) {
        replaced += varmap[toFind];
      }
      i = end - 1;
    }
    // not encounter dollar sign
    else {
      replaced.push_back(content[i]);
    }
  }
  content = replaced;
  }*/

// parse for the set command
bool CmdVar::parseSet() {
  parsed.clear();
  size_t prev = 0;
  size_t current = 0;
  current = content.find(delimiter);
  int count = 0;
  while ((current != std::string::npos) && (count < 2)) {
    if (current == prev) {
      prev++;
    }
    else {
      parsed.push_back(content.substr(prev, current - prev));
      prev = current + 1;
      count++;
    }
    current = content.find(delimiter, prev);
  }
  if ((count == 2) && (prev < content.size())) {
    parsed.push_back(content.substr(prev, std::string::npos));
    return true;
  }
  return false;
}

// check if it's a valid variable name
bool CmdVar::isValidVar(std::string varname) {
  const char * str = varname.c_str();
  for (size_t i = 0; i < varname.size(); i++) {
    if (!isalnum(str[i])) {
      if (str[i] != '_') {
        return false;
      }
    }
  }
  return true;
}

// insert new variable name and value into the map
void CmdVar::varmapInsert(std::string var, std::string value) {
  varmap[var] = value;
}

// check whether a varaible is in the map by its name
bool CmdVar::varmapSearch(std::string var) {
  if (varmap.find(var) != varmap.end()) {
    return true;
  }
  else {
    return false;
  }
}

// get the variable's value from its name
std::string CmdVar::varmapValue(std::string var) {
  std::map<std::string, std::string>::iterator it = varmap.find(var);
  if (it != varmap.end()) {
    return it->second;
  }
  else {
    return "NOT FOUND";
  }
}

// check if a character is a dight number
bool CmdVar::chkDecimal(std::string number) {
  const char * toCheck = number.c_str();
  size_t i = 0;
  while (toCheck[i] != '\0') {
    if (!isdigit(toCheck[i])) {
      return false;
    }
    i++;
  }
  return true;
}

// update the map
void CmdVar::varmapInc(std::string var) {
  // var found in varmap
  std::map<std::string, std::string>::iterator it = varmap.find(var);
  if (it != varmap.end()) {
    // is decimal
    if (chkDecimal(it->second)) {
      // c++ string to int
      // int plus one
      int value = atoi(it->second.c_str()) + 1;
      // int to c++ string
      std::ostringstream str1;
      str1 << value;
      std::string ans = str1.str();
      // update the value
      it->second = ans;
    }
    // not decimal
    else {
      it->second = "1";
    }
  }
  // var not found in varmap
  else {
    // insert <var, 1> into varmap
    varmapInsert(var, "1");
  }
}

// display the map
void CmdVar::varmapDisplay() {
  for (std::map<std::string, std::string>::iterator it = varmap.begin(); it != varmap.end(); ++it) {
    std::cout << "key is " << it->first << ", value is " << it->second << std::endl;
  }
}
