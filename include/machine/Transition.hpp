#pragma once

#include "State.hpp"

// Pre Declaration
class State;

/*
 * This is the abstract Base class for all the different Transitions in the various Automatons / Machines
 */
class Transition {

protected:

	// Target of the Transition
	State *state;

	// This is the letter that will be checked / writing when using this Transition
	char letter;

	// Different Flags maybe useful for different Transitions when needing extra information
	char flag1, flag2, flag3;

public:

	/*
	 * simple linear Transition Constructor.
	 */
	Transition(char letter, State *state, char flag1, char flag2, char flag3);

	~Transition();

	/*
	 * Simple getter Methods
	 */
	State* getFollowState() const;
	char getLetter() const;

	// Abstract / virtual Method need to be implanted separately to make it fit for each Automaton / Machine
	bool isValid(char letter, char flag);

};
