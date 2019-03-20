#include <map>
#include <utility>

#include "Cmd.h"

// Inheritance from class Cmd
// CmdVar is a class which can
class CmdVar : public Cmd
{
 protected:
  // map: key stores variable name, value stores variable value
  std::map<std::string, std::string> varmap;
  //std::vector<std::string> builtin;

 public:
  // default constructor
  CmdVar() : Cmd() {
    //builtin.push_back("set");
    //builtin.push_back("export");
    //builtin.push_back("inc");
    //builtin.push_back("cd");
    //varmap.insert(std::pair<std::string, std::string>("var1", "value1"));
    //varmap.insert(std::pair<std::string, std::string>("var2", "value2"));
  }
  // constructor
  CmdVar(std::map<std::string, std::string> inputmap) : Cmd() {
    //builtin.push_back("set");
    //builtin.push_back("export");
    //builtin.push_back("inc");
    //builtin.push_back("cd");
    varmap = inputmap;
  }

  /*void setBuiltin() {
    builtin.clear();
    builtin.push_back(std::string("set"));
    builtin.push_back(std::string("export"));
    builtin.push_back(std::string("inc"));
    builtin.push_back(std::string("cd"));
    }*/

  //std::vector<std::string> getBuiltin() { return builtin; }
  std::map<std::string, std::string> getVarmap() { return varmap; }
  void varmapInsert(std::string var, std::string value);
  bool varmapSearch(std::string var);
  std::string varmapValue(std::string var);
  bool chkDecimal(std::string number);
  void varmapInc(std::string number);
  void printPrompt();
  void replaceVar();
  bool parseSet();
  bool isValidVar(std::string varname);
  void varmapDisplay();

  //~CmdVar() { builtin = std::vector<std::string>(); }
};
