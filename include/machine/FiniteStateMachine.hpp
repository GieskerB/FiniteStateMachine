#pragma once

#include "Machine.hpp"

class FiniteStateMachine: public Machine {

private:

	void readFromFile(const std::string&);

	void setupTransitions(const std::vector<std::string>&);


public:

    std::istream & operator>>(std::istream& in_stream) override;

	FiniteStateMachine();

	~FiniteStateMachine() override;

	void add_state(const State &new_state) override;

	void addTransition(const State&, const Transition&) override;

	bool accept(const std::string&) override;

};

std::istream& operator>>(std::istream& is, FiniteStateMachine& fsm);
