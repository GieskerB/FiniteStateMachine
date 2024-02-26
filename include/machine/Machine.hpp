#pragma once

#include <string>

#include "State.hpp"

class Machine {

protected:

	std::vector<State> m_states;
    std::vector<char> alphabet;

	// always one State from the m_states DynArray
	State *currentState;

	bool deterministic, hasInitalState;

	static std::vector<std::string> extractNames(const std::string&);

	static void checkForMistake(const std::vector<std::string>&,
			const std::vector<std::string>&);

	static std::vector<std::string> getInput(const std::string&);

	void setupAlphabet(const std::string&);

    virtual std::istream& operator>>(std::istream& in_stream)= 0;

public:

	Machine();

	virtual ~Machine();

	virtual void addState(const State&) = 0;

	virtual void addTransition(const State&, const Transition&) = 0;

	virtual bool accept(const std::string&) = 0;

};

void remove_spaces(std::string& str);


std::vector<std::string> split_at_comma(std:: string& str);
