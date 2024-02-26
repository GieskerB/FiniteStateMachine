#pragma once

#include "Transition.hpp"
#include <iostream>
#include <vector>

/*
 *  Strong and weak ownership: State "owns" all the transition starting from the state itself.
 */

class Transition;

class State {

private:

    // Non-Terminal Symbole. Name is the identifier of a state. Primary used for the user.
    std::string name;

    // Information about the State
    bool initial, final, dummy;

    // Stores the references to all the transitions going from THIS state to another.
    std::vector<Transition> transitions;

    // check if State is a dummy. When true throw exception!
    void check_dummy() const;

public:

    //Standard constructors:
    State();

    // Explicit Constructor:
    explicit State(std::string , bool final = false, bool initial = false);

    // Copy constructor:
    State(const State& );

    // Move constructor:
    State( State&& );

    // Destructor:
    ~State();

    static const State DUMMY;

    // Copy Assignment:
    State& operator=(const State& );

    // Move Assignment:
    State& operator=(State&& ) noexcept ;

    // Getter Methods
    [[nodiscard]] const std::string & getName() const;

    [[nodiscard]] bool hasFollowState(char letter, char flags) const;

    [[nodiscard]] const State &getFollowState(char letter, char flags) const;

    [[nodiscard]] const State &getRandomState() const;

    [[nodiscard]] std::vector<State> getFollowStates(char letter, char flag) const;

    [[nodiscard]] bool isInitial() const;

    [[nodiscard]] bool isFinal() const;

    // Adding a new Transitions to the State without adding the same one twice
    void addTransition(const Transition &transition);

    // toString Method
    std::string toString();

};
