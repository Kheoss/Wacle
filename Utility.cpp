#include "mainHeader.hpp"

int Utility::StringToInt(std::string _nr){
    int nr =0;

    for(int _index=0;_index<_nr.size();_index++){
        nr*= 10;
        nr += (int)(_nr[_index] - '0');
    }
    return nr;
}

void FileManager::ReadAllFromFile(std::string _fileName,std::string _settings, std::string _varName, std::string _blockName){
    std::ifstream _stream(_fileName);
    std::string _line;

            size_t _varIndex;
            for(_varIndex=0;_varIndex<Parser::_variables.size(); _varIndex++)
                if(Parser::_variables[_varIndex].first == _varName)
                    break;
        if(_settings == "lines"){
            while((std::getline(_stream,_line))){
                Parser::_variables[_varIndex].second.second = _line;
                Parser::Interpret(Parser::_blockList[_blockName]);
            }
            return;
        }
        while((_stream>>_line)){
            Parser::_variables[_varIndex].second.second = _line;
            Parser::Interpret(Parser::_blockList[_blockName]);
        }   
}
void FileManager::GetSubDirectories(std::string _path, std::string _settings, std::string _varName, std::string _blockName){
     
     size_t _varIndex;
            for(_varIndex=0;_varIndex<Parser::_variables.size(); _varIndex++)
                if(Parser::_variables[_varIndex].first == _varName)
                    break;
     
     char path[1000];
     struct dirent *dp;
     
     DIR *dir = opendir(_path.c_str());
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL){
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
           
           Parser::_variables[_varIndex].second.second = std::string(dp->d_name);
 
            strcpy(path, _path.c_str());
            strcat(path, "/");
            strcat(path, dp->d_name);
 
            std::string path_s = (const char*) path;
            //listFilesRecursively(path);
            Parser::Interpret(Parser::_blockList[_blockName]);
        }
    }
    closedir(dir);
}
void FileManager::FileMove(std::string _original, std::string _moved){

    std::string _fileName;
    std::stringstream _stream(_original);
                    while(std::getline(_stream, _fileName, '/')){}

    std::rename(_original.c_str(), (_moved + "/" + _fileName).c_str());
}
