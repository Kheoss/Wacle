#include "mainHeader.hpp"

bool EventManagement::FileEventTrigger::_timeIsEchivalent(tm a, tm b){
    if(a.tm_hour != b.tm_hour)return false;
    if(a.tm_min != b.tm_min)return false;
    if(a.tm_sec != b.tm_sec)return false;
    if(a.tm_mday != b.tm_mday)return false;

    return true;
}
void EventManagement::StartNewEventThread(EventManagement::FileEventTrigger _trigger){
        _trigger.StartTrigger();
}
void EventManagement::FileEventTrigger::Trigger(std::string& _action){
    Parser::Interpret(Parser::_blockList[_action]);
} 
void EventManagement::FileEventTrigger::StartTrigger(){  
     while(true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        stat(_fileName.c_str(), &attrib);
        _time = gmtime(&(attrib.st_mtime));
        if(isFirstFrame){
            _lastTime = *_time;
            isFirstFrame = false;
            continue;
        }
        if(!_timeIsEchivalent(*_time, _lastTime)){
            _lastTime = *_time;
            Trigger(_bl);
        }

     }
}
EventManagement::FileEventTrigger::FileEventTrigger(std::string& _b, std::string& _file){
    this->_bl = _b;
    this->_fileName = _file;
    isFirstFrame = true;
}


void EventManagement::EventManager::AddEventTrigger(EventManagement::FileEventTrigger _trigger){
    _triggers.push_back(_trigger);
    std::thread t(StartNewEventThread,_trigger);
    t.join();
}
EventManagement::EventManager EventManagement::_manager = EventManagement::EventManager();