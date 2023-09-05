#ifndef INCLUDE_UTIL_TREE_HPP_
#define INCLUDE_UTIL_TREE_HPP_

#include "util/DynArray.hpp"
#include "machine/State.hpp"
#include "machine/DFM_Transition.hpp"

class DFM {

private:

    // List of all states
    DynArray<State> states;
    // Always the current State. Initialised by the initialState
    State *currentState;

    // Step by Step checking each letter
    bool nextLetter(char letter);
    // Saying when word is done. If currentState is final its accepted else not
    bool stop();

public:

    DFM();
    DFM(State *initialState);

    /*
     * Simple Adder Methods
     */
    void addState(State *state);
    void addStates(DynArray<State> *states);

    /*
     * Simple Setter Methods
     */
    void setStates(DynArray<State> *states);
    void setInitialState(State *state);

    /*
     * Giving a specific word the DFM will check if it belongs to the Language described by this DFM
     */
    bool accept(std::string word);

};



#endif