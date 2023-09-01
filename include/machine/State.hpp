#ifndef INCLUDE_MACHINE_STATE_HPP
#define INCLUDE_MACHINE_STATE_HPP


#include "Transition.hpp"
#include "../util/DynArray.hpp"

#include <iostream>

class State {

private:

    const std::string name;
    const bool initial;
    const bool final;
    DynArray<Transition> transitions;

public:

    State(std::string name, bool initial, bool final);
    ~State();

    const std::string &getName() const;

    bool isInitial() const;
    bool isFinal() const;

    void addTransition(Transition &transition);

    bool hasFollowState(char letter, char flags);

    State *getFollowState(char letter, char flags);
    DynArray<State> getFollowStates(char letter, char flag);

    State *getRandomState();
};

#endif
