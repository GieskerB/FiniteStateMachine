#pragma once

#include "State.hpp"
#include <array>
#include <iostream>

#define DEF_FLAG '\0'
#define NUM_FLAGS 2

/*
 *  Strong and weak ownership: Transition does not "own" the state it points to. This is accomplished by using a
 *  reference to the state instead of a member variable or pointer.
 */

class State;

class Transition {

private:

    static constexpr int NUM = 2;

protected:

    // Reference to the "target" of the transitions
    State *state;

    // This is the letter that will be checked / writing when using this Transition
    char letter;

    bool dummy;

    // Different Flags useful for different type of machines. Necessary for storing extra information.
    std::array<char, NUM_FLAGS> flags;

    void check_dummy() const;

public:

    //Standard constructors:
    Transition();

    // Explicit Constructor:
    Transition(char letter, State &state, char flag0 = DEF_FLAG, char flag1 = DEF_FLAG);

    // Copy constructor:
    Transition(const Transition& );

    // Move constructor:
    Transition( Transition&& ) noexcept;

    // Destructor:
    ~Transition();

    // Copy Assignment:
    Transition& operator=(const Transition& );

    // Move Assignment:
    Transition& operator=(Transition&& ) noexcept ;


    static const Transition DUMMY;

    // Getter Methods
    const State &getFollowState() const;

    char getLetter() const;

    std::array<char, NUM_FLAGS> getFlags() const;

    // Checks if latter (and flag) are the same
    bool isValid(char letter, char flag = DEF_FLAG);

    // toString Method
    std::string toString();

};
