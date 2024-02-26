#pragma once

#include "State.hpp"
#include <iostream>
#include <vector>


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
    std::vector<char> flags;

    void check_dummy() const;

public:

    //Standard constructors:
    Transition();

    // Explicit Constructor:
    Transition(char letter, State &state, std::initializer_list<char> flags);

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

    std::vector<char> getFlags() const;

    // Checks if latter (and flag) are the same
    bool isValid(char letter, char flag = 2) const;

    // toString Method
    std::string toString();

};
