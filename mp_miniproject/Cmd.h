#include <string>
#include <vector>

class Cmd
{
 protected:
  std::string content;
  char delimiter;
  std::vector<std::string> parsed;

 public:
  Cmd() : delimiter(' ') {}
  bool chkSpaces();
  bool checkSlash();
  std::string deslash(std::string input);
  std::vector<std::string> parse();
  void display();
  void printPrompt();
  std::string read();
  bool checkExit();
  std::string getCmd() const { return content; }
  std::vector<std::string> getParsed() const { return parsed; }
  void getFileName(const char * dirName);
  int run();

  ~Cmd() {}
};
