#pragma once

#include "Machine.hpp"

class FiniteStateMachine: public Machine {

public:

	FiniteStateMachine();

	~FiniteStateMachine() override;

    std::istream & operator<<(std::istream& in_stream) override;

    void add_state(State&) override;

	void add_transition(State&, const Transition&) override;

	bool accept(const std::string&) override;

};