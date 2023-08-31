
#include "../../include/machine/State.hpp"

State::State() {

}


State::~State() {

}



std::string State::getName() const {

}

bool State::isInitial() const {

}
bool State::isFinal() const {

}

State &State::getFollowState(char letter) {

}
DynArray<State> State::getFollowStates(char letter) {

}

State &State::getRandomState() {

}


