#pragma once

#include "Transition.hpp"
#include "../util/DynArray.hpp"
#include <iostream>

/*
 *  Strong and weak ownership: State "owns" all the transition starting from the state itself.
 */

class Transition;

class State {

private:

    // Non-Terminal Symbole. Name is the identifier of a state. Primary used for the user.
    const std::string name;

    // Information about the State
    const bool initial, final;

    // Stores the references to all the transitions going from THIS state to another.
    DynArray<Transition> transitions;

public:

    //Constructors:
    State() = delete;

    State(const std::string &name, bool final = false, bool initial = false);

    // Destructor:
    ~State();

    // Getter Methods
    std::string getName() const;

    bool hasFollowState(char letter, char flags) const;

    const State &getFollowState(char letter, char flags) const;

    const State &getRandomState() const;

    DynArray<State> getFollowStates(char letter, char flag) const;

    bool isInitial() const;

    bool isFinal() const;

    // Adding a new Transitions to the State without adding the same one twice
    void addTransition(const Transition &transition);

    // toString Method
    std::string toString();

};
