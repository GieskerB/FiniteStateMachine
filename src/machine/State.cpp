#include "../../include/machine/State.hpp"
#include <utility>

/*
 * Private methods:
 */

const State State::DUMMY{};


void State::check_dummy() const {
    if (this->m_dummy) throw std::runtime_error("Invalid use of m_dummy object!\n");
}

/*
 * Constructors & Destructor:
 */

State::State() : m_initial{false}, m_final{false}, m_dummy{true} {}

State::State(std::string name, bool initial, bool final) :
        m_name{std::move(name)}, m_initial{initial}, m_final{final}, m_dummy{false} {
    std::cout <<"Create: " << this->to_string() << "\n";
}

State::State(const State &other_state) : m_name{other_state.m_name}, m_initial{other_state.m_initial},
                                         m_final{other_state.m_final},
                                         m_dummy{other_state.m_dummy}, m_transitions{other_state.m_transitions} {
    std::cout <<"Copy: " << this->to_string() << "\n";
}

State::State(State &&other_state) noexcept: m_name{other_state.m_name}, m_initial{other_state.m_initial},
                                            m_final{other_state.m_final},
                                            m_dummy{other_state.m_dummy}, m_transitions{other_state.m_transitions} {
    std::cout <<"Move: " << this->to_string() << "\n";
}

State::~State() {
    std::cout <<"Dead: " << this->to_string() << "\n";
}

/*
 * operator overloading
 */

State &State::operator=(const State &other_state) = default;

State &State::operator=(State &&other_state) noexcept {
    this->m_name = other_state.m_name;
    this->m_initial = other_state.m_initial;
    this->m_final = other_state.m_final;
    this->m_dummy = other_state.m_dummy;
    this->m_transitions = other_state.m_transitions;
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


State State::get_next_state(char letter) const {
    return get_next_state(letter, std::vector<char>{});
}

State State::get_next_state(char letter, const std::vector<char> &flags) const {
    auto results = get_next_states(letter, flags);
    return results.empty() ? State::DUMMY : results[0];

}

State State::get_next_random_state(char letter) const {
    return get_next_random_state(letter, std::vector<char>{});
}

State State::get_next_random_state(char letter, const std::vector<char> &flags) const {
    auto results = get_next_states(letter, flags);
    if (results.empty()) {
        return State::DUMMY;
    }
    int rand_index = std::rand() % results.size();
    return results[rand_index];
}


std::vector<State> State::get_next_states(char letter) const {
    return get_next_states(letter, std::vector<char>{});
}

std::vector<State> State::get_next_states(char letter, const std::vector<char> &flags) const {
    std::vector<State> results{};
    for (const auto &transition: this->m_transitions) {
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
        bool same_target = transition.get_target_state().get_name() == new_transition.get_target_state().get_name();
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

    std::string str;
    if (m_dummy) {
        str = "Dummy";
    } else {
        str = m_name;
        if(m_initial and m_final) {
            str+= " <B>: ";
        } else if(m_initial) {
            str+= " <I>: ";
        }else if(m_final) {
            str+= " <F>: ";
        }else  {
            str+= " <N>: ";
        }

        for(const auto& transition: m_transitions) {
            str += transition.to_string();
        }
    }

    return '[' + str + ']';
}

bool State::is_dummy() const {
    return m_dummy;
}


