#include "mainHeader.hpp"

    std::ifstream in;

    int main(int argc, char **argv) { 
        try{
        in.open(argv[1]);
        in.seekg(0, std::ios::end);
        int length = in.tellg();
        in.seekg(0, std::ios::beg);
    
        std::string buffer(length, ' ');
    
        in.read(&buffer[0], length);
         Parser::ExtractTokens(buffer);
         Parser::Interpret(Parser::_curTokens);
        // std::cout<<FileManager::workingDir();
       // Parser::ShowTokens();

        }catch(std::exception ex){
            std::cout<<"File not found";
        }

        // EventManagement::FileEventTrigger _trigger = EventManagement::FileEventTrigger();
        // EventManagement::_manager.AddEventTrigger(_trigger);
        

        return 0;
    }