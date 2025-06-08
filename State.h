#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <unordered_map>

class State {
public:
    std::string name;
    bool isFinal;
    bool isDeathState;
    std::unordered_map<std::string, State*> transitions;

    State(std::string name, bool isFinal, bool isDeathState) 
        : name(name), isFinal(isFinal), isDeathState(isDeathState) {}

    void addTransition(const std::string& symbol, State* state) {
        transitions[symbol] = state;
    }

    State* getNextState(const std::string& symbol) {
        return transitions.count(symbol) ? transitions[symbol] : nullptr;
    }

    std::string toString() const {
        return name + "," + (isFinal ? "true" : "false") + "," + (isDeathState ? "true" : "false");
    }
};

#endif 