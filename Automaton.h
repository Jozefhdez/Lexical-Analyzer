#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <string>
#include <vector>
#include "State.h"
#include <map>

class Automaton {
private:
    State* S;
    std::string alphabet;
    std::map<State*, std::string> types;

public:
    Automaton(State* S, std::string alphabet, std::map<State*, std::string> types) {
        this->S = S;
        this->alphabet = alphabet;
        this->types = types;
    }

    bool validate(const std::string& symbol) {
        for (int i = 0; i < alphabet.length(); i++){
            if (symbol == std::string(1, alphabet[i])){
                return true;
            }
        }
        return false;
    }

    std::vector<std::pair<std::string, std::string>> tokens(const std::string& word) {
        if (word.empty()) {
            std::cout << "Empty string" << std::endl;
            return std::vector<std::pair<std::string, std::string>>();
        }
        State* initialState = S;
        State* currentState = S;
        State* pastState = S;
        std::string token_tmp = "";
        std::vector<std::pair<std::string, std::string>> tokens;

        for (size_t i = 0; i < word.length(); i++) {
            std::string symbol = word.substr(i, 1);

            if(symbol != " "){
                if(validate(symbol)){
                    pastState = currentState;
                    currentState = currentState->getNextState(symbol);
                    if(currentState == nullptr){
                        tokens.push_back(std::make_pair(token_tmp, type(pastState, token_tmp)));
                        currentState = initialState->getNextState(symbol);
                        token_tmp = symbol;
                    } 
                    else{
                        token_tmp += symbol;
                    }
                }
                else{
                    return std::vector<std::pair<std::string, std::string>>();
                }
            }
            else{
                continue;
            }
        }
        tokens.push_back(std::make_pair(token_tmp, type(currentState, token_tmp)));
        return tokens;
    } 

    std::string type(State* state, std::string symbol){
        if(types[state] == "Operator" || types[state] == "Parenthesis"){
            if(symbol == "+") {
                return "Sum";
            } else if(symbol == "-") {
                return "Substract";
            } else if(symbol == "*") {
                return "Product";
            } else if(symbol == "/") {
                return "Division";
            } else if(symbol == "=") {
                return "Assignment";
            } else if(symbol == "(") {
                return "Left parenthesis";
            } else if(symbol == ")") {
                return "Right parenthesis";
            } else {
                return "Identifier";
            }
        }
        else {
            return types[state];
        }
    }

};

#endif
