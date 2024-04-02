#pragma once

#include "Machine.hpp"

class FiniteAutomaton: public Machine {

public:

	FiniteAutomaton();

	~FiniteAutomaton() override;

    std::istream & operator<<(std::istream& in_stream) override;

    void add_state(State&) override;

	void add_transition(State&, const Transition&) override;

	bool accept(const std::string&) override;

    std::string generate_random_word() override;
};