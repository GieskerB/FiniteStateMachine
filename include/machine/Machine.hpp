#pragma once

#include <string>
#include <set>

#include "State.hpp"

class Machine {

protected:

	std::vector<State> m_states;
    std::vector<char> m_alphabet;

	State *p_initial_state ,*p_current_state;

	bool m_deterministic;

    virtual std::istream& operator>>(std::istream& in_stream) = 0;

public:

	Machine();

	virtual ~Machine();

	virtual void add_state(const State&) = 0;

    void add_letter(const std::string&);

	virtual void add_transition(State&, const Transition&) = 0;

	virtual bool accept(const std::string&) = 0;

};

void remove_spaces(std::string& str);

std::set<std::string> separate_by_comma(const std::string & line);
