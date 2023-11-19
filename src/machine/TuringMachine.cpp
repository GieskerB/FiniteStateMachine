#include "../../include/machine/TuringMachine.hpp"

#include <iostream>
#include <stdexcept>




void TuringMachine::readFromFile(const std::string &fileName) {
	DynArray<std::string> inputLines = getInput(fileName);

	// Stores name of all, initial and final states
	// all States
	DynArray<std::string> allStates = this->extractNames(
			*inputLines.getFirst());
	inputLines.removeFirst();
	// final States
	DynArray<std::string> initialStates = this->extractNames(
			*inputLines.getFirst());
	inputLines.removeFirst();
	// initial States
	DynArray<std::string> finalStates = this->extractNames(
			*inputLines.getFirst());
	inputLines.removeFirst();

	// Stops the program if user made wrong Input
	this->checkForMistake(initialStates, allStates);

	//Initializing all the states
	const int stateNum = allStates.size();
	for (int i = 0; i < stateNum; i++) {
		const std::string name = *allStates.get(i);
		this->addState(
				State(name, finalStates.indexOf(name) != -1,
						*initialStates.getFirst() == name));
	}
}

TuringMachine::TuringMachine(const std::string &fileName) : Machine(){
	this->readFromFile(fileName);

}

TuringMachine::~TuringMachine() = default;


void TuringMachine::addState(const State &newState) {
	if (this->states.indexOf(newState) == -1) {
		this->states.addLast(newState);
	} else {
		std::cout << "You can not add the same state twice" << std::endl;
	}
	if (newState.isInitial() && !this->hasInitalState) {
		this->currentState = this->states.getLast();
		this->hasInitalState = true;
	} else if (newState.isInitial() && !this->hasInitalState) {
		throw std::runtime_error(
				"Turing-Machine only allows one initial State.");
	}
}

void TuringMachine::addTransition(const State &from,
		const Transition &newTransition) {

}

bool TuringMachine::accept(const std::string &word) {

	return false;
}
