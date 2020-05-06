#include "mainHeader.hpp"

int Utility::StringToInt(std::string _nr){
    int nr =0;

    for(int _index=0;_index<_nr.size();_index++){
        nr*= 10;
        nr += (int)(_nr[_index] - '0');
    }
    return nr;
    
}