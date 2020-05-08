#include "mainHeader.hpp"

Utility::Timer::Timer(){}

void Utility::Timer::SetTimeout(int _timeOut, std::string _block){
     std::thread t([_timeOut,_block](){
         std::this_thread::sleep_for(std::chrono::milliseconds(_timeOut));
         Parser::Interpret(Parser::_blockList[_block]);
    });
    t.join();
}
void Utility::Timer::SetInterval(int _timeOut, std::string _block){
     std::thread t([_timeOut,_block](){
         while(true){   
         std::this_thread::sleep_for(std::chrono::milliseconds(_timeOut));
         Parser::Interpret(Parser::_blockList[_block]);
         }
    });
    t.join();
}