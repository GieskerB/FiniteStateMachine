#ifndef INCLUDE_MACHINE_STATE_HPP
#define INCLUDE_MACHINE_STATE_HPP


#include "Transition.hpp"
#include "../util/DynArray.hpp"

#include <iostream>

class State {

private:

    // Name like a identifyer only for User
    const std::string name;
    // Frags for each State
    const bool initial, final;
    DynArray<Transition> transitions;

public:

    // Simple constructor default final and initial being false
    State(std::string name, bool final = false, bool initial = false);
    // Deconstructor
    ~State();

    /*
     * Simple Getter Methods
     */
    const std::string &getName() const;
    State *getFollowState(char letter, char flags);
    DynArray<State> getFollowStates(char letter, char flag);

    State *getRandomState();

    /*
     * Simple Check Methods
     */
    bool isInitial() const;
    bool isFinal() const;
    bool hasFollowState(char letter, char flags);

    // Adding a new Transitions to the State without adding the same one twice
    void addTransition(Transition &transition);

};

#endif
