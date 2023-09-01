#ifndef INCLUDE_UTIL_TREE_HPP_
#define INCLUDE_UTIL_TREE_HPP_

#include "util/DynArray.hpp"
#include "machine/State.hpp"
#include "machine/DFM_Transition.hpp"

class DFM {

private:

    DynArray<State> states;
    State *currentState;

    bool nextLetter(char letter);
    bool stop();

public:

    DFM();
    DFM(State *initialState);

    void addState(State *state);
    void addStates(DynArray<State> *states);

    void setStates(DynArray<State> *states);

    void setInitialState(State *state);

    bool accept(std::string word);

};



#endif