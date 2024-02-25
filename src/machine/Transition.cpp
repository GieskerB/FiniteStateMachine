#include "../../include/machine/State.hpp"
#include "../../include/machine/Transition.hpp"


void Transition::check_dummy() const {
    if (this->dummy) throw std::runtime_error("Invalid use of dummy object.");
}


/*
 * Letter is the input letter, flag0 is what to be written, flag1 is L or R
 * A FSM has no flags
 */
Transition::Transition() : state(nullptr), letter{'\0'}, dummy{true} {}

Transition::Transition(char letter, State &state, char flag0, char flag1) :
        state{&state}, dummy{false}, letter{letter} {
    flags[0] = flag0;
    flags[1] = flag1;
}

Transition::Transition(const Transition &other_transition) {
    this->state = other_transition.state;
    this->letter = other_transition.letter;
    this->dummy = other_transition.dummy;
    this->flags = other_transition.flags;
}

Transition::Transition(Transition &&other_transition)  noexcept {
    this->state = other_transition.state;
    this->letter = other_transition.letter;
    this->dummy = other_transition.dummy;
    this->flags = other_transition.flags;
}

Transition::~Transition() = default;

Transition &Transition::operator=(const Transition &other_transition) {
    this->state = other_transition.state;
    this->letter = other_transition.letter;
    this->dummy = other_transition.dummy;
    this->flags = other_transition.flags;
    return *this;
}

// Move Assignment:
Transition &Transition::operator=(Transition &&) noexcept {

    return *this;
}


const State &Transition::getFollowState() const {
    return *this->state;
}

char Transition::getLetter() const {
    return this->letter;
}

std::array<char, NUM_FLAGS> Transition::getFlags() const {
    return this->flags;
}

bool Transition::isValid(char letter, char flag0) {
    // flag0 is currently used by the TM als the second argument
    // to determine which Transition to pick.
    return letter == this->letter and flag0 == this->flags[0];
}

