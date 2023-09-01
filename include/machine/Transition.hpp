#ifndef INCLUDE_MACHINE_TRANSITION_HPP
#define INCLUDE_MACHINE_TRANSITION_HPP

#include "State.hpp"

class Transition {

private:

    State *state;

    char letter;

    char flag1, flag2, flag3;


protected:

    Transition(char letter, State *state, char flag1, char flag2, char flag3);

public:


    State *getFollowState()const;

    char getLetter()const;

    virtual bool isValid(char letter, char flag)const;

};


#endif