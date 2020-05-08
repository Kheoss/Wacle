#include "mainHeader.hpp"

std::unordered_map<std::string, Parser::TokenPrimaryType> Parser::_primary_tokens = {
  std::make_pair("print",Parser::COMMAND),
  std::make_pair("BrutCommand", Parser::COMMAND),
  std::make_pair("MakeDir",Parser::COMMAND),
  std::make_pair("=", Parser::OPERATOR),
  std::make_pair("FileEvent",Parser::COMMAND),
  std::make_pair("SetTimeOut",Parser::COMMAND),
  std::make_pair("SetInterval",Parser::COMMAND),
  std::make_pair("ReadFile", Parser::COMMAND),
  std::make_pair("GetSubDirectories",Parser::COMMAND),
  std::make_pair("MoveFile",Parser::COMMAND)
};
std::unordered_map<std::string, void*> Parser::_commandsTokens = {
    std::make_pair("print", (void*)Commands::PrintFunction),
    std::make_pair("BrutCommand", (void*)Commands::BrutCommandFunction),
    std::make_pair("MakeDir", (void*)Commands::CreateDirFunction),
    std::make_pair("FileEvent", (void*)Commands::AddFileEventListener),
    std::make_pair("SetTimeOut", (void*)Commands::SetTimeOut),
    std::make_pair("SetInterval", (void*)Commands::SetInterval),
    std::make_pair("ReadFile", (void*)Commands::ReadAFile),
    std::make_pair("GetSubDirectories", (void*)Commands::GetSubDirs),
    std::make_pair("MoveFile", (void*)Commands::FileMove)
};
std::vector<std::pair<std::string, std::pair<Parser::VariableType ,std::string >> > Parser::_variables;
std::unordered_map<std::string, void*> Parser::_operators = {
    std::make_pair(":",(void*)Operators::_declareVar),
    std::make_pair("=",(void*)Operators::_assignValueToVar)
};

std::vector<std::pair<Parser::TokenPrimaryType,std::string>> Parser::_curTokens;
std::unordered_map<std::string, std::vector<std::pair<Parser::TokenPrimaryType, std::string> > > Parser::_blockList;
std::unordered_map<std::string,std::vector<std::pair<Parser::TokenPrimaryType, std::string> >> Parser::_flags;
std::unordered_map<std::string, Parser::VariableType> Parser::_variablesNameDeclare = {
    std::make_pair("string", Parser::STRING),
    std::make_pair("number", Parser::NUMBER)
};

std::string FileManager::workingDir(){
    char _buffer[256];
    GetCurrentDirectoryA(256,_buffer);
    return std::string(_buffer);
}
