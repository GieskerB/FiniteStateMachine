#pragma once

#include "Transition.hpp"
#include <iostream>
#include <vector>

/*
 *  Strong and weak ownership: State "owns" all the transition starting from the p_target_state itself.
 */

class Transition;

class State {

private:
    // Non-Terminal Symbole. Name is the identifier of a p_target_state. Primary used for the user.
    std::string m_name;

    // Information about the State
    bool m_initial, m_final;

    // Stores the references to all the m_transitions going from THIS p_target_state to another.
    std::vector<Transition> m_transitions;

public:

    //Standard constructors:
    State() = delete;

    // Explicit Constructor:
    explicit State(std::string, bool initial = false, bool final = false);

    // Copy constructor:
    State(const State &);

    // Move constructor:
    State(State &&) noexcept;

    // Destructor:
    ~State();

    static const State DUMMY;

    // Copy Assignment:
    State &operator=(const State &);

    // Move Assignment:
    State &operator=(State &&) noexcept;

    // Getter Methods
    [[nodiscard]] const std::string &get_name() const;


    [[nodiscard]]  const State *get_next_state(char) const;

    [[nodiscard]]  const State *get_next_state(char, const std::vector<char> &) const;

    [[nodiscard]]  const State *get_next_random_state(char) const;

    [[nodiscard]]  const State *get_next_random_state(char, const std::vector<char> &) const;

    [[nodiscard]] std::vector<const State *> get_next_states(char) const;

    [[nodiscard]]  std::vector<const State *> get_next_states(char, const std::vector<char> &) const;


    [[nodiscard]] bool is_initial() const;

    [[nodiscard]] bool is_final() const;

    // Adding a new Transitions to the State without adding the same one twice
    bool add_transition(const Transition &);


    // to_string Method
    [[nodiscard]] std::string to_string() const;

};
