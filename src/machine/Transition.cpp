#include "../../include/machine/Transition.hpp"

void Transition::check_dummy() const {
    if (this->m_dummy) throw std::runtime_error("Invalid use of m_dummy object.");
}


/*
 * Letter is the input m_letter, flag0 is what to be written, flag1 is L or R
 * A FSM has no m_flags
 */
Transition::Transition() : p_target_state(nullptr), m_letter{'\0'}, m_dummy{true} {}

Transition::Transition(char letter, State &state) :
        p_target_state{&state}, m_letter{letter}, m_dummy{false}, m_flags{} {

}

Transition::Transition(char letter, State &state, std::initializer_list<char> flags) :
        p_target_state{&state}, m_letter{letter}, m_dummy{false}, m_flags{flags} {

}

Transition::Transition(const Transition &other_transition) {
    this->p_target_state = other_transition.p_target_state;
    this->m_letter = other_transition.m_letter;
    this->m_dummy = other_transition.m_dummy;
    this->m_flags = other_transition.m_flags;
}

Transition::Transition(Transition &&other_transition) noexcept {
    this->p_target_state = other_transition.p_target_state;
    this->m_letter = other_transition.m_letter;
    this->m_dummy = other_transition.m_dummy;
    this->m_flags = other_transition.m_flags;
}

Transition::~Transition() = default;

Transition &Transition::operator=(const Transition &other_transition) = default;

// Move Assignment:
Transition &Transition::operator=(Transition &&) noexcept {

    return *this;
}


const State &Transition::get_target_state() const {
    return *this->p_target_state;
}

char Transition::get_letter() const {
    return this->m_letter;
}

bool Transition::is_valid(char letter, const std::vector<char>& flags) const {
    bool do_flags_match{m_flags.size() == flags.size()};
    for(int i{0}; do_flags_match and i < m_flags.size(); i++) {
        if(flags[i] != m_flags[i]) {
            do_flags_match = false;
        }
    }
    return  do_flags_match and letter == this->m_letter;
}

std::string Transition::to_string() const{

    std::string str;
    if (m_dummy) {
        str = "Dummy";
    } else {
        str = m_letter;
        if(!m_flags.empty()) {
            str += "( ";
            for(const auto & flag: m_flags) {
                str+= flag;
                str+= ' ';
            }
            str += ')';
        }
        str += "->" + p_target_state->get_name();
    }

    return '[' + str + ']';

}





