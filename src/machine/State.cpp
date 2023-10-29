//#pragma once

#include <memory>
#include <cstdlib>
#include <ctime>
#include "../../include/machine/State.hpp"

State::State(std::string name, bool final, bool initial) :
		name(name), initial(initial), final(final) {

}

State::~State() {

}

bool State::operator== (const State& other) const {
	return this->name == other.name;
}

const std::string& State::getName() const {
	return this->name;
}

bool State::isInitial() const {
	return this->initial;
}

bool State::isFinal() const {
	return this->final;
}

void State::addTransition(Transition *transition) {
	this->transitions.addLast(transition);
}

bool State::hasFollowState(char letter, char flags) {
	return this->getFollowState(letter, flags) != nullptr;
}

State* State::getFollowState(char letter, char flag = '\0') {
	for (int i = 0; i < this->transitions.size(); i++) {
		if (this->transitions.get(i)->isValid(letter, flag)) {
			return this->transitions.get(i)->getFollowState();
		}
	}
	return nullptr;
}

DynArray<State>& State::getFollowStates(char letter, char flag = '\0') {
    std::unique_ptr<DynArray<State>> kartoffel = std::make_unique<DynArray<State>>();
    // MEMORY LEAK
	DynArray<State> *outp = new DynArray<State>();
	for (int i = 0; i < this->transitions.size(); i++) {
		if (this->transitions.get(i)->isValid(letter, flag)) {
			outp->addLast(this->transitions.get(i)->getFollowState());
		}
	}
	return *outp;
}

State* State::getRandomState() {
	int randIndex = std::rand() % this->transitions.size();
	return this->transitions.get(randIndex)->getFollowState();
}

std::string State::toString() {
	return this->name + " " + (this->initial ? "is Init" : "notInit") + " "
			+ (this->final ? "is Fin" : "notFin");
}
