
#include <cstdlib>
#include <ctime>
#include "../../include/machine/State.hpp"

State::State(std::string name, bool initial, bool final) :
    name(name), initial(initial), final(final), transitions(3) {

}


State::~State() {

}



const std::string &State::getName() const {
    return this->name;
}

bool State::isInitial() const {
    return this->initial;
}

bool State::isFinal() const {
    return this->final;
}

void State::addTransition(Transition &transition) {
    this->transitions.addLast(&transition);
}



bool State::hasFollowState(char letter, char flags) {
    return this->getFollowState(letter, flags) != nullptr;
}

State *State::getFollowState(char letter, char flag = '\0') {
    for (int i = 0; i < this->transitions.size(); i++) {
        if (this->transitions.get(i)->isValid(letter, flag)) {
            return this->transitions.get(i)->getFollowState();
        }
    }
    return nullptr;
}

DynArray<State> State::getFollowStates(char letter, char flag = '\0') {
    DynArray<State> outp;
    for (int i = 0; i < this->transitions.size(); i++) {
        if (this->transitions.get(i)->isValid(letter, flag)) {
            outp.addLast(this->transitions.get(i)->getFollowState());
        }
        return outp;
    }
}

State *State::getRandomState() {
    int randIndex = std::rand() % this->transitions.size();
    return this->transitions.get(randIndex)->getFollowState();
}


