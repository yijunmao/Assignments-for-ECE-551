#include <stdlib.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "CmdVar.h"
#include "Directory.h"

// global environment variable from outside
extern char ** environ;

int main() {
  int status = 0;
  std::map<std::string, std::string> inputmap;
  // put environment variables into the map

  do {
    CmdVar cmdObj(inputmap);
    //cmdObj.setBuiltin();
    // printPrompt
    cmdObj.printPrompt();
    // read user input into content field
    cmdObj.read();
    // check empty input or just includes spaces
    if ((cmdObj.getCmd()).length() == 0 || cmdObj.chkSpaces()) {
      status = 1;
      continue;
    }
    // check exit
    if (cmdObj.checkExit()) {
      break;
    }
    // check variable name in map and replace it with its value
    cmdObj.replaceVar();
    // parse content
    std::vector<std::string> parsed = cmdObj.parse();

    Directory dirObj;
    std::vector<std::string> path = dirObj.iniEnv();

    // no slash
    if (!cmdObj.checkSlash()) {
      // check if is buildin cmd
      if (strcmp("set", parsed[0].c_str()) == 0) {
        // parsed by space twice
        if (cmdObj.parseSet()) {
          parsed = cmdObj.getParsed();
          // second argument is valid variable
          if (cmdObj.isValidVar(parsed[1])) {
            cmdObj.varmapInsert(parsed[1], parsed[2]);
            // second argument is PATH
            // put it into environment variable list
            if (strcmp(parsed[1].c_str(), "PATH") == 0) {
              setenv(parsed[1].c_str(), parsed[2].c_str(), 1);
            }
          }
          // invalid second argument
        }
        status = 1;
      }
      else if (strcmp("export", parsed[0].c_str()) == 0) {
        // has two arguments
        if (parsed.size() == 2) {
          // variable in varmap
          if (cmdObj.varmapSearch(parsed[1])) {
            std::string value = cmdObj.varmapValue(parsed[1]);
            setenv(parsed[1].c_str(), value.c_str(), 1);
          }
        }
        status = 1;
      }
      else if (strcmp("inc", parsed[0].c_str()) == 0) {
        // has two arguments
        if (parsed.size() == 2) {
          // variable valid
          if (cmdObj.isValidVar(parsed[1])) {
            // var in or not in varmap
            cmdObj.varmapInc(parsed[1]);
          }
        }
        status = 1;
      }
      else if (strcmp("cd", parsed[0].c_str()) == 0) {
        // has two arguments
        if (parsed.size() == 2) {
          if (chdir(parsed[1].c_str()) == -1) {
            perror("Change directory failed");
          }
        }
        status = 1;
      }
      else {
        const char * progName = (parsed[0]).c_str();
        // search each directory in PATH variable
        std::vector<std::string>::iterator it;
        for (it = path.begin(); it != path.end(); ++it) {
          const char * dirName = (*it).c_str();
          // find the program
          if (dirObj.searchProgram(dirName, progName)) {
            cmdObj.getFileName(dirName);
            status = cmdObj.run();
            break;
          }
        }
        // program not found
        if (it == path.end()) {
          cmdObj.getFileName(NULL);
          status = 1;
          std::cout << "Command " << cmdObj.getCmd() << " not found" << std::endl;
        }
      }
    }

    // slash in program name
    else {
      cmdObj.getFileName(NULL);

      status = cmdObj.run();
    }

    inputmap = cmdObj.getVarmap();
    //cmdObj.varmapDisplay();

  } while (status == 1);

  return 0;
}
