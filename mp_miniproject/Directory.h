#include <string>
#include <vector>

class Directory
{
 private:
  std::vector<std::string> path;

 public:
  std::vector<std::string> seperate(std::string input, char seperator);
  std::vector<std::string> iniEnv();
  bool searchProgram(const char * dirName, const char * progName);
};
