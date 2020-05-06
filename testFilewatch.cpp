#include <sys/stat.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include<thread>
#include <chrono>
#include <vector>

class FileEventTrigger{
    private:
      tm _lastTime;
      bool isFirstFrame;
    public:
    struct tm *_time;
    struct stat attrib;
        FileEventTrigger();
        void StartTrigger();
        void Trigger();
        bool _timeIsEchivalent(tm, tm);
};
void StartNewEventThread(FileEventTrigger _trigger){
        _trigger.StartTrigger();
}
bool FileEventTrigger::_timeIsEchivalent(tm a, tm b){
    if(a.tm_hour != b.tm_hour)return false;
    if(a.tm_min != b.tm_min)return false;
    if(a.tm_sec != b.tm_sec)return false;
    if(a.tm_mday != b.tm_mday)return false;

    return true;
}
void FileEventTrigger::Trigger(){
    std::cout<<"File Modified";
}
void FileEventTrigger::StartTrigger(){  
     while(true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        stat("sampleCode.fcl", &attrib);
        _time = gmtime(&(attrib.st_mtime));
        if(isFirstFrame){
            _lastTime = *_time;
            isFirstFrame = false;
            continue;
        }
        if(!_timeIsEchivalent(*_time, _lastTime)){
            _lastTime = *_time;
            Trigger();
        }

     }
}
FileEventTrigger::FileEventTrigger(){
    isFirstFrame = true;
}
class EventManager{
    public:
        void AddEventTrigger(FileEventTrigger);
        void RemoveEventTrigger(int);
        FileEventTrigger *GetEventTrigger(int);

    private:
        std::vector<FileEventTrigger> _triggers;

};

void EventManager::AddEventTrigger(FileEventTrigger _trigger){
    _triggers.push_back(_trigger);
    std::thread t(StartNewEventThread,_trigger);
    t.join();
}

int main() {
    EventManager _manager = EventManager();
    FileEventTrigger _trigger = FileEventTrigger();
    _manager.AddEventTrigger(_trigger);
}