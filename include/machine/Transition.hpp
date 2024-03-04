#pragma once

#include "State.hpp"
#include <iostream>
#include <vector>


/*
 *  Strong and weak ownership: Transition does not "own" the p_target_state it points to. This is accomplished by using a
 *  reference to the p_target_state instead of a member variable or pointer.
 */

class State;

class Transition {

protected:

    // Reference to the "target" of the m_transitions
    State *p_target_state;

    // This is the m_letter that will be checked / writing when using this Transition
    char m_letter;

    // Different Flags useful for different type of machines. Necessary for storing extra information.
    std::vector<char> m_flags;

public:

    //Standard constructors:
    Transition() = delete;
    // Explicit Constructors:

    Transition(char letter, State &state);
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
    const State * get_target_state() const;

    char get_letter() const;

    // Checks if latter (and flag) are the same
    [[nodiscard]] bool is_valid(char letter, const std::vector<char> &flags) const;

    // to_string Method
    std::string to_string() const;

};
