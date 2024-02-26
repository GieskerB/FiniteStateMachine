#pragma once

#include <string>

#include "Machine.hpp"
#include "State.hpp"

class TuringMachine: public Machine {

private:

    std::istream & operator>>(std::istream& in_stream) override;

public:

	 TuringMachine();

	~TuringMachine() override;

	void addState(const State&) override;

	void addTransition(const State&, const Transition&) override;

	bool accept(const std::string&) override;

};
