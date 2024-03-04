#include "../../include/machine/Transition.hpp"


Transition::Transition(char letter, State &state) :
        p_target_state{&state}, m_letter{letter},  m_flags{} {

}

Transition::Transition(char letter, State &state, std::initializer_list<char> flags) :
        p_target_state{&state}, m_letter{letter}, m_flags{flags} {

}

// Copy-Konstruktor
Transition::Transition(const Transition &other) = default;

// Move-Konstruktor
Transition::Transition(Transition &&other) noexcept
        : p_target_state(other.p_target_state),
          m_letter(other.m_letter),
          m_flags(std::move(other.m_flags)) {}


Transition::~Transition() = default;

// Kopierzuweisungsoperator
Transition& Transition::operator=(const Transition& other) {
    if (this != &other) {
        p_target_state = other.p_target_state;
        m_letter = other.m_letter;
        m_flags = other.m_flags; // Kopieren des Vektors
    }
    return *this;
}

// Move-Zuweisungsoperator
Transition& Transition::operator=(Transition&& other) noexcept {
    if (this != &other) {
        p_target_state = other.p_target_state;
        m_letter = other.m_letter;
        m_flags = std::move(other.m_flags); // Verschieben des Vektors
    }
    return *this;
}


const State *Transition::get_target_state() const {
    return this->p_target_state;
}

char Transition::get_letter() const {
    return this->m_letter;
}

bool Transition::is_valid(char letter, const std::vector<char> &flags) const {
    bool do_flags_match{m_flags.size() == flags.size()};

    for (int i{0}; do_flags_match and i < m_flags.size(); i++) {
        if (flags[i] != m_flags[i]) {
            do_flags_match = false;
        }
    }
    return do_flags_match and letter == this->m_letter;
}

std::string Transition::to_string() const {

    std::string str{m_letter};
    if (!m_flags.empty()) {
        str += "( ";
        for (const auto &flag: m_flags) {
            str += flag;
            str += ' ';
        }
        str += ')';
    }
    str += "->" + p_target_state->get_name();


    return '[' + str + ']';

}





