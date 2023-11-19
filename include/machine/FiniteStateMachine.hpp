#pragma once

#include "Machine.hpp"

class FiniteStateMachine: public Machine {

private:

	void readFromFile(const std::string&) override;

	void setupTransitions(const DynArray<std::string>&);

public:

	FiniteStateMachine(const std::string&);

	~FiniteStateMachine() override;

	void addState(const State&) override;

	void addTransition(const State&, const Transition&) override;

	bool accept(const std::string&) override;

};
