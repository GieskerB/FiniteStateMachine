#pragma once

#include <string>

#include "Machine.hpp"
#include "State.hpp"

class TuringMachine: public Machine {

public:

	 TuringMachine();

	~TuringMachine() override;

    std::istream & operator<<(std::istream& in_stream) override;

	void add_state(State&) override;

	void add_transition(State&, const Transition&) override;

	bool accept(const std::string&) override;

};
