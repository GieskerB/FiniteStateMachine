#include "../../include/machine/TuringMachine.hpp"
#include <stdexcept>
#include <algorithm>

std::istream & TuringMachine::operator>>(std::istream &in_stream) {

    std::string line;
    std::getline(in_stream, line);

    line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

    int line_counter = 0;
    while(line != "}") {
        if(line.empty() or (line.size() >= 2 and line[0] == '/' and line[1] == '/')) {
            continue;
        }
        switch (line_counter) {
            case 0:
                // Read all non-terminal symbols
                break;
        }
    }

    return in_stream;
}

/*
void TuringMachine::readFromFile(const std::string &fileName) {
	DynArray<std::string> inputLines = getInput(fileName);

	// Stores name of all, initial and final m_states
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

	//Initializing all the m_states
	const int stateNum = allStates.size();
	for (int i = 0; i < stateNum; i++) {
		const std::string name = *allStates.get(i);
		this->addState(
				State(name, finalStates.indexOf(name) != -1,
						*initialStates.getFirst() == name));
	}
}
 */

TuringMachine::TuringMachine() : Machine(){

}

TuringMachine::~TuringMachine() = default;


void TuringMachine::addState(const State &newState) {
/*
	if (this->m_states.indexOf(newState) == -1) {
		this->m_states.addLast(newState);
	} else {
		std::cout << "You can not add the same state twice" << std::endl;
	}
 */
	if (newState.isInitial() && !this->hasInitalState) {
		this->currentState = &this->m_states[m_states.size()-1];
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
