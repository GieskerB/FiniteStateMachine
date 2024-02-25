#pragma once

#include <string>

#include "../util/Array.hpp"
#include "State.hpp"

class Machine {

protected:

	DynArray<State> states;
	DynArray<char> alphabet;

	// always one State from the states DynArray
	State *currentState;

	bool deterministic, hasInitalState;

	static DynArray<std::string> extractNames(const std::string&);

	static void checkForMistake(const DynArray<std::string>&,
			const DynArray<std::string>&);

	static DynArray<std::string> getInput(const std::string&);

	void setupAlphabet(const std::string&);

	virtual void readFromFile(const std::string&) = 0;

public:

	Machine();

	virtual ~Machine();

	virtual void addState(const State&) = 0;

	virtual void addTransition(const State&, const Transition&) = 0;

	virtual bool accept(const std::string&) = 0;

};
