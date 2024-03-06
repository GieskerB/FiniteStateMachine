#include "../../include/machine/State.hpp"
#include <utility>

/*
 * Private methods:
 */

/*
 * Constructors & Destructor:
 */


State::State(std::string name, bool initial, bool final)
        :  m_name{std::move(name)},
          m_initial{initial}, m_final{final} {
    //std::cout << "Create: " << this->to_string() << "\n";
}


// Copy-Konstruktor
State::State(const State &other)
        :  m_name(other.m_name),
          m_initial(other.m_initial), m_final(other.m_final),
          m_transitions(other.m_transitions) {
    //std::cout << "Copy: " << to_string() << "\n";
}

// Move-Konstruktor
State::State(State &&other) noexcept
        :  m_name(std::move(other.m_name)),
          m_initial(other.m_initial), m_final(other.m_final),
          m_transitions(std::move(other.m_transitions)) {
    std::cout << "Move: " << to_string() << "\n";
}


State::~State() = default;

/*
 * operator overloading
 */

// Kopierzuweisungsoperator
State& State::operator=(const State& other) {
    if (this != &other) {
        m_name = other.m_name;
        m_initial = other.m_initial;
        m_final = other.m_final;
        m_transitions = other.m_transitions; // Kopieren des Vektors
    }
    return *this;
}

// Move-Zuweisungsoperator
State& State::operator=(State&& other) noexcept {
    if (this != &other) {
        m_name = std::move(other.m_name);
        m_initial = other.m_initial;
        m_final = other.m_final;
        m_transitions = std::move(other.m_transitions); // Verschieben des Vektors
    }
    return *this;
}


/*
 * getter
 */

const std::string &State::get_name() const {
    return this->m_name;
}

bool State::is_initial() const {
    return this->m_initial;
}

bool State::is_final() const {
    return this->m_final;
}


const State *State::get_next_state(char letter) const {
    return get_next_state(letter, std::vector<char>{});
}

const State *State::get_next_state(char letter, const std::vector<char> &flags) const {
    auto results = get_next_states(letter, flags);
    return results.empty() ? nullptr : results[0];

}

const State *State::get_next_random_state(char letter) const {
    return get_next_random_state(letter, std::vector<char>{});
}

const State *State::get_next_random_state(char letter, const std::vector<char> &flags) const {
    auto results = get_next_states(letter, flags);
    if (results.empty()) {
        return nullptr;
    }
    int rand_index = std::rand() % results.size();
    return results[rand_index];
}


std::vector<const State *> State::get_next_states(char letter) const {
    return get_next_states(letter, std::vector<char>{});
}

std::vector<const State *> State::get_next_states(char letter, const std::vector<char> &flags) const {
    std::vector<const State *> results{};
    for (const auto &transition: m_transitions) {
        if (transition.is_valid(letter, flags)) {
            results.push_back(transition.get_target_state());
        }
    }
    return results;
}


/*
 * Adding a transition
 */

bool State::add_transition(const Transition &new_transition) {
    bool deterministic{true};
    for (const auto &transition: m_transitions) {
        bool same_target = transition.get_target_state()->get_name() == new_transition.get_target_state()->get_name();
        if (same_target and
            transition.get_letter() == new_transition.get_letter()) {
            throw std::runtime_error("No duplicate Transitions allowed in one state!\n");
        } else if (same_target) {
            deterministic = false;
        }
    }
    this->m_transitions.push_back(new_transition);
    return deterministic;
}

std::string State::to_string() const {

    std::string str = m_name;
    if (m_initial and m_final) {
        str += " <B>: ";
    } else if (m_initial) {
        str += " <I>: ";
    } else if (m_final) {
        str += " <F>: ";
    } else {
        str += " <N>: ";
    }

    for (const auto &transition: m_transitions) {
        str += transition.to_string();
    }

    return '[' + str + ']';
}


