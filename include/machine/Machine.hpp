#pragma once

#include <string>
#include <set>
#include <optional>

#include "State.hpp"

class Machine {

protected:

	std::vector<State> m_states;
    std::vector<char> m_alphabet;

    std::optional<std::size_t> m_initial_state_index;


	bool m_deterministic{false};


public:

	Machine();

	virtual ~Machine();

	virtual void add_state( State&) = 0;

    void add_letter(const std::string&);

    virtual std::istream& operator<<(std::istream& in_stream) = 0;

	virtual void add_transition(State&, const Transition&) = 0;

	virtual bool accept(const std::string&) = 0;

    virtual std::string generate_random_word () = 0;

};

void remove_spaces(std::string& str);

std::set<std::string> separate_by_comma(const std::string & line);
