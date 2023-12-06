#include "../../include/machine/State.hpp"
#include "../../include/machine/Transition.hpp"


/*
 * Letter is the input letter, flag0 is what to be written, flag1 is L or R
 * A FSM has no flags
 */
Transition::Transition(char letter, const State &state, char flag0, char flag1):
    state{state}, letter{letter}
{
    flags[0] = flag0;
    flags[1] = flag1;
}

Transition::~Transition() {

}


const State& Transition::getFollowState() const {
	return this->state;
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

