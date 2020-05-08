#include "mainHeader.hpp"

    Parser::TokenPrimaryType Parser::GetTokenType(std::string& _token){

        if(Parser::_primary_tokens.find(_token) == Parser::_primary_tokens.end()){

            if(Parser::_operators.find(_token) != Parser::_operators.end()){
                    return Parser::OPERATOR;
                }
                   
            if(_token[0] == '"'){
                return Parser::HARDSTRING;
            }
            if(_token[0] == '('){
                return Parser::PARANT;
            }
            if(Parser::IsHardNumber(_token)){
                return Parser::HARDNUMBER;
            }
            return Parser::VARIABLE;
        }

        return Parser::_primary_tokens[_token];
    }

       void Parser::ExtractTokens(std::string& _code){
            //endline parsing
            bool _isInStringValue = false;
            for(size_t index=0;index<_code.size();index++){
                if(_code[index] == '\n'){
                    _code.erase(_code.begin() + index);
                    _code.insert(_code.begin() + index, ' ');
                }else
                if(_code[index] == '"'){
                    _isInStringValue = !_isInStringValue;
                }else
                if(_code[index] == ' ' && _isInStringValue){
                    _code[index] = spaceInStringStructure;
                }
            }

            //token extraction
            std::string _token;
            std::istringstream _tokenStream(_code);
            int _nrBlocks = 0;
            std::unordered_map <int, std::vector<std::pair<Parser::TokenPrimaryType, std::string> > > _extractedBlocks;
            std::stack <int> _blockEndOrder;
            while(std::getline(_tokenStream,_token,' ')){
                // TO DO : Exeption handling

                if(_token.size() == 0) continue;
                //flag split
                if(_token == "{"){
                    _blockEndOrder.push(_nrBlocks);
                    _extractedBlocks.insert(std::make_pair(_nrBlocks,std::vector<std::pair<Parser::TokenPrimaryType,std::string>>()));
                    _nrBlocks++;
                    continue;
                }
                if(_token == "}"){
                    int _curBl = _blockEndOrder.top();
                _blockEndOrder.pop();
                std::string _value = "BL" + std::to_string(_curBl);
                Parser::_blockList.insert(make_pair(_value,_extractedBlocks[_curBl]));
                Parser::TokenPrimaryType _type = Parser::BLOCK;
                if(_blockEndOrder.empty()){
                    Parser::_curTokens.push_back(std::make_pair(_type,_value));
                }else{
                    _extractedBlocks[_blockEndOrder.top()].push_back(std::make_pair(_type,_value));
                }
                continue;
                }
                Parser::TokenPrimaryType _type = Parser::GetTokenType(_token);
                        if(_type == Parser::HARDSTRING){
                            std::replace(_token.begin(),_token.end(),spaceInStringStructure,' ');            
                        }
                        if(!_blockEndOrder.empty()){
                            _extractedBlocks[_blockEndOrder.top()].push_back(std::make_pair(_type,_token));
                        }else{
                            Parser::_curTokens.push_back(std::make_pair(_type,_token));
                        }
            }
    }
    std::string Parser::GetVariableValue(std::string& _varName){
        for(auto _var : Parser::_variables){
            if(_var.first == _varName){
                return _var.second.second;
            }
        }
        return NULL;
    }

    void Parser::Interpret(std::vector<std::pair<TokenPrimaryType, std::string> > _tokens){
        for(int _tokenIndex=0;_tokenIndex < _tokens.size();_tokenIndex++){
                if(_tokens[_tokenIndex].first == Parser::COMMAND){
                    //std::cout<<_tokens[_tokenIndex].second<<"\n";
                     ((void (*)(int*,std::vector<std::pair<TokenPrimaryType, std::string> >&))Parser::_commandsTokens[_tokens[_tokenIndex].second])(&_tokenIndex, _tokens);
                } else
                if(_tokens[_tokenIndex].first == Parser::OPERATOR){
                     std::pair<Parser::TokenPrimaryType, std::string> _declaration = _tokens[_tokenIndex-1];
                     std::pair<Parser::TokenPrimaryType, std::string> _value = _tokens[_tokenIndex+1];
                     std::string _decl = _declaration.second;
                     std::string _val = _value.second;
                    ((void(*)(std::string,std::string))Parser::_operators[_tokens[_tokenIndex].second])(_decl,_val);
                }
        }
    }

    bool Parser::IsHardNumber(std::string& _token){
        for(char _char : _token){
            if(_char >'9' || _char < '0')return false;
        }
        return true;
    }