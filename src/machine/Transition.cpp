

#include "../../include/machine/State.hpp"

Transition::Transition(char letter, State *state, char flag1, char flag2,
		char flag3) {

	this->letter = letter;
	this->state = state;

	this->flag1 = flag1;
	this->flag2 = flag3;
	this->flag3 = flag3;
}

Transition::~Transition() {

}


State* Transition::getFollowState() const {
	return this->state;
}

char Transition::getLetter() const {
	return this->letter;
}

bool Transition::isValid(char letter, char flag) {
	return false;
}
