//#pragma once

#include <utility>

#include "../../include/machine/State.hpp"

/*
 * Private methods:
 */


void State::check_dummy() const {
    if (this->dummy) throw std::runtime_error("Invalid use of dummy object.");
}

/*
 * Constructors & Destructor:
 */

State::State() : initial{false}, final{false}, dummy{true} {}

State::State(std::string name, bool initial, bool final) :
        name{std::move(name)}, initial{initial}, final{final}, dummy{false} {
    std::cout << this->toString() << "is alive now\n";
}

State::State(const State &other_state) : name{other_state.name}, initial{other_state.initial}, final{other_state.final},
                                         dummy{other_state.dummy}, transitions{other_state.transitions} {
    std::cout << this->toString() << "copied successfully\n";
}

State::State(State &&other_state) : name{other_state.name}, initial{other_state.initial}, final{other_state.final},
                                    dummy{other_state.dummy}, transitions{other_state.transitions} {
    std::cout << this->toString() << "moved successfully\n";
}

State::~State() {
    std::cout << this->toString() << "is dead now\n";
}

/*
 * operator overloading
 */

State& State::operator=(const State& other_state) {
    this->name = other_state.name;
    this->initial = other_state.initial;
    this->final = other_state.final;
    this->dummy = other_state.dummy;
    this->transitions = other_state.transitions;
    return *this;
}

State& State::operator=(State&& other_state)  noexcept {
    this->name = other_state.name;
    this->initial = other_state.initial;
    this->final = other_state.final;
    this->dummy = other_state.dummy;
    this->transitions = other_state.transitions;
    return *this;
}


/*
 * getter
 */
const std::string &State::getName() const {
    return this->name;
}

bool State::isInitial() const {
    return this->initial;
}

bool State::isFinal() const {
    return this->final;
}

/*
 * Successor methods:
 */

bool State::hasFollowState(char letter, char flags) const {
    return false;
}

const State &State::getFollowState(char letter, char flag = '\0') const {
    for (int i = 0; i < this->transitions.size(); i++) {
        if (this->transitions[i].isValid(letter, flag)) {
            return this->transitions[i].getFollowState();
        }
    }
}


const State &State::getRandomState() const {
    int randIndex = std::rand() % this->transitions.size();
    return this->transitions[randIndex].getFollowState();
}

Array<State> State::getFollowStates(char letter, char flag = '\0') const {
    Array<State> outp{};
    for (int i = 0; i < this->transitions.size(); i++) {
        if (this->transitions[i].isValid(letter, flag)) {
            outp.addLast(this->transitions[i].getFollowState());
        }
    }
    return outp;
}

/*
 * Adding a transition
 */

void State::addTransition(const Transition &transition) {
    this->transitions.addLast(transition);
}






std::string State::toString() {

    std::string internalValues;
    if (dummy) {
        internalValues = "Dummy";
    } else {
        internalValues = this->name + ": ";
        internalValues += (this->initial ? "is Init" : "notInit");
        internalValues += " ";
        internalValues += (this->final ? "is Fin" : "notFin");
        internalValues += " Number of Transitions: ";
        internalValues += std::to_string(this->transitions.size());
    }

    return "State:[" + internalValues + "]";
}


