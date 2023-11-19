#pragma once

#include <string>

#include "Machine.hpp"
#include "State.hpp"

class TuringMachine: public Machine {

private:

	void readFromFile(const std::string&) override;

public:

	TuringMachine(const std::string&);

	~TuringMachine() override;

	void addState(const State&) override;

	void addTransition(const State&, const Transition&) override;

	bool accept(const std::string&) override;

};
