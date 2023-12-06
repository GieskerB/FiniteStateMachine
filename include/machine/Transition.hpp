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
    const State &state;

    // This is the letter that will be checked / writing when using this Transition
    char letter;

    // Different Flags useful for different type of machines. Necessary for storing extra information.
    std::array<char, NUM_FLAGS> flags;

public:

    // Constructors:
    Transition() = delete;

    Transition(char letter, const State &state, char flag0 = DEF_FLAG, char flag1 = DEF_FLAG);

    // Destructors:
    ~Transition();


    // Getter Methods
    const State &getFollowState() const;

    char getLetter() const;

    std::array<char, NUM_FLAGS> getFlags() const;

    // Checks if latter (and flag) are the same
    bool isValid(char letter, char flag = DEF_FLAG);

    // toString Method
    std::string toString();

};
