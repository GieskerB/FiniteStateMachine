//#pragma once

#include "../../include/machine/State.hpp"


State::State(const std::string&  name, bool initial, bool final) :
        name{name}, initial{initial}, final{final} {
    std::cout << this->toString() << "is alive now\n";
}

State::~State() {
    std::cout << this->toString() << "wird zerstört" << std::endl;
}

std::string State::getName() const {
    return this->name;
}

bool State::isInitial() const {
    return this->initial;
}

bool State::isFinal() const {
    return this->final;
}

void State::addTransition(const Transition& transition) {
    this->transitions.addLast(transition);
}

bool State::hasFollowState(char letter, char flags) const {
   // return this->getFollowState(letter, flags) != nullptr;
   return false;
}

const State& State::getFollowState(char letter, char flag = '\0') const {
    for (int i = 0; i < this->transitions.size(); i++) {
        if (this->transitions.get(i).isValid(letter, flag)) {
            return this->transitions.get(i).getFollowState();
        }
    }
}

const State& State::getRandomState() const {
    int randIndex = std::rand() % this->transitions.size();
    return this->transitions.get(randIndex).getFollowState();
}

DynArray<State> State::getFollowStates(char letter, char flag = '\0') const{
    DynArray<State> outp = DynArray<State>();
    for (int i = 0; i < this->transitions.size(); i++) {
        if (this->transitions.get(i).isValid(letter, flag)) {
            outp.addLast(this->transitions.get(i).getFollowState());
        }
    }
    return outp;
}


std::string State::toString() {
    std::string internalValues = this->name + ": ";
    internalValues = (this->initial ? "is Init" : "notInit");
    internalValues += " ";
    internalValues += (this->final ? "is Fin" : "notFin");
    internalValues += " Number of Transitions: ";
    internalValues += std::to_string(this->transitions.size());

    std::string output = "State:[" + internalValues + "]";


    return output;
}
