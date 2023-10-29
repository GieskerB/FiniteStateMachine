#pragma once

#include "Transition.hpp"
#include "../util/DynArray.hpp"

#include <iostream>

// Pre Declaration
class Transition;

class State {

private:

	// Name like a identifier only for User
	const std::string name;
	// Frags for each State
	const bool initial, final;
	// Pointer because of inheritance
	DynArray<Transition> transitions;

public:

	State() :
			name(""), initial(false), final(false), transitions() {

	}

	// Simple constructor default final and initial being false
	State(std::string name, bool final = false, bool initial = false);
	// Deconstructor
	~State();

	bool operator==(const State&)const;

	/*
	 * Simple Getter Methods
	 */
	const std::string& getName() const;
	State* getFollowState(char letter, char flags);
	DynArray<State>& getFollowStates(char letter, char flag);

	State* getRandomState();

	/*
	 * Simple Check Methods
	 */
	bool isInitial() const;
	bool isFinal() const;
	bool hasFollowState(char letter, char flags);

	// Adding a new Transitions to the State without adding the same one twice
	void addTransition(Transition *transition);

	std::string toString();

};
