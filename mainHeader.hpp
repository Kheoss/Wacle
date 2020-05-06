#define spaceInStringStructure '-'
#include "iostream"
#include "fstream"
#include "string"
#include "Windows.h"
#include "unordered_map"
#include "sstream"
#include "vector"
#include "algorithm"
#include "direct.h"
#include "sys/stat.h"
#include "chrono"
#include "time.h"
#include "thread"

namespace Parser{
  //token primitive Types [commands/params/operator/....]
 enum TokenPrimaryType{
COMMAND,
PARAMETER,
OPERATOR,
VARIABLE,
HARDSTRING,
HARDNUMBER,
BLOCK,
FLAGLIST
};
enum VariableType{
  STRING,
  NUMBER
};
    //expression regulation
  extern std::unordered_map<std::string, TokenPrimaryType> _primary_tokens;
    //parsed tokens
  extern std::vector<std::pair<TokenPrimaryType, std::string> > _curTokens;
    //standard commands  EX : print
  extern std::unordered_map<std::string, void*> _commandsTokens;
    //standard operators
  extern std::unordered_map<std::string, void*>_operators;
    //variables <token, value>
  extern std::vector<std::pair<std::string,std::pair<VariableType, std::string >> > _variables;
    //hard type for casting <type, cast-name>
  extern std::unordered_map<std::string, Parser::VariableType> _variablesNameDeclare;
    //blocks aka functions
  extern std::unordered_map<std::string, std::vector<std::pair<TokenPrimaryType, std::string> > > _blockList;
    //settings/flags lists
  extern std::unordered_map<std::string,std::vector<std::pair<TokenPrimaryType, std::string> >> _flags;
    //parsing 
  void ExtractTokens(std::string&); 
    //token type  
  TokenPrimaryType GetTokenType(std::string&);
  void Interpret(std::vector<std::pair<TokenPrimaryType, std::string> >);
  void ShowTokens();
  std::string GetVariableValue(std::string&);
  bool IsHardNumber(std::string&);
}

//Command : curIndex in cur tokenArray||block

namespace Commands{
  void PrintFunction(int&, std::vector<std::pair<Parser::TokenPrimaryType, std::string> >&);
  void BrutCommandFunction(int&, std::vector<std::pair<Parser::TokenPrimaryType, std::string> >&);
  void CreateDirFunction(int&, std::vector<std::pair<Parser::TokenPrimaryType, std::string> >&);
  void AddFileEventListener(int&, std::vector<std::pair<Parser::TokenPrimaryType, std::string> >&);
  void SetTimeOut(int&, std::vector<std::pair<Parser::TokenPrimaryType, std::string> >&);
  void SetInterval(int&, std::vector<std::pair<Parser::TokenPrimaryType, std::string> >&);
}
namespace Operators{
  void _declareVar(std::string& , std::string&);
  void _assignValueToVar(std::string&, std::string&);
}
namespace FileManager{
  std::string workingDir();
}

namespace EventManagement{
class FileEventTrigger{
    private:
      tm _lastTime;
      bool isFirstFrame;
    public:
    struct tm *_time;
    struct stat attrib;
    std::string _bl;
    std::string _fileName;
        FileEventTrigger(std::string&, std::string&);
        void StartTrigger();
        void Trigger(std::string&);
        bool _timeIsEchivalent(tm, tm);
};

void StartNewEventThread(FileEventTrigger);


class EventManager{
    public:
        void AddEventTrigger(FileEventTrigger);
        void RemoveEventTrigger(int);
        FileEventTrigger *GetEventTrigger(int);

    private:
        std::vector<FileEventTrigger> _triggers;

};

extern EventManager _manager;

}

namespace Utility{

  class Timer{
    public:
      Timer();
      void SetTimeout(int, std::string);
      void SetInterval(int, std::string);
  };

  int StringToInt(std::string);

}