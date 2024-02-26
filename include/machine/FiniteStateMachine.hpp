#pragma once

#include "Machine.hpp"

class FiniteStateMachine: public Machine {

private:

	void readFromFile(const std::string&);

	void setupTransitions(const std::vector<std::string>&);

    std::istream & operator>>(std::istream& in_stream) override;

public:

	explicit FiniteStateMachine(const std::string&);

	~FiniteStateMachine() override;

	void addState(const State&) override;

	void addTransition(const State&, const Transition&) override;

	bool accept(const std::string&) override;

};
