#ifndef INCLUDE_MACHINE_TRANSITION_HPP
#define INCLUDE_MACHINE_TRANSITION_HPP

#include "State.hpp"

/*
 * This is the abstract Base class for all the differents Transitions in the various Automatons / Machines
 */
class Transition {

private:

    // Target of the Transition
    State *state;

    // This is the letter that wioll be checkt / writting when using this Transition
    char letter;

    // Different Flags maybe usefull for different Transitions when needing extra information
    char flag1, flag2, flag3;


protected:

    /*
     * simple linear Transition Constructor.
     */
    Transition(char letter, State *state, char flag1, char flag2, char flag3);

public:

    /*
     * Simple getter Methods
     */
    State *getFollowState()const;
    char getLetter()const;

    // Abstract / virtuals Method need to be impleneted seperatly to make it fit for each Automaton / Machine
    virtual bool isValid(char letter, char flag)const;

};


#endif