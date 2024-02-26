#include "../../include/machine/FiniteStateMachine.hpp"
#include <stdexcept>
#include <algorithm>

std::istream & FiniteStateMachine::operator>>(std::istream &in_stream) {

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

void FiniteStateMachine::readFromFile(const std::string &fileName) {
	std::vector<std::string> inputLines = getInput(fileName);
/*
	// Stores name of all, initial and final m_states
	// all States
	std::vector<std::string> allStates = Machine::extractNames(
			*inputLines.getFirst());
	// final States
	std::vector<std::string> initialStates = Machine::extractNames(
			*inputLines.get(1));
	// initial States
	std::vector<std::string> finalStates = Machine::extractNames(
			*inputLines.get(2));

	// Stops the program if user made wrong Input
	Machine::checkForMistake(initialStates, allStates);

	// get all alphabet characters
	this->setupAlphabet(*inputLines.get(3));

	//Initializing all the m_states
	const int stateNum = allStates.size();
	for (int i = 0; i < stateNum; i++) {
		const std::string name = *allStates.get(i);
		this->addState(
				State(name, finalStates.indexOf(name) != -1,
						*initialStates.getFirst() == name));
	}
	this->setupTransitions(inputLines);
*/
}

void FiniteStateMachine::setupTransitions(
		const std::vector<std::string> &inputLines) {
	// All transitions are in line 5 to length -2
	const int LEN = inputLines.size();
	if (inputLines[4] != "{" or inputLines[LEN - 1] != "}") {
		throw std::invalid_argument("Transitions are not surrounded in {}");
	}
	for (int i = 5; i < LEN - 1; i++) {
		const std::string TRANSITION = inputLines[i];
		const int TRANS_LEN = TRANSITION.length();
		// Split the Transition into its 3 main components:
		int lastJ = 0;
		char letter = 0;
		std::string stateNameFrom, stateNameTo;
		for (int j = lastJ; j < TRANS_LEN; j++) {
			if (TRANSITION.at(j) == ',') {
				stateNameFrom = TRANSITION.substr(lastJ, j - lastJ);
				lastJ = j + 1;
			} else if (TRANSITION.at(j) == '-'
					and TRANSITION.at(j + 1) == '>') {
				if (j - lastJ == 1) {
					letter = TRANSITION.at(lastJ);
				} else {
					throw std::invalid_argument(
							"Second argument of transition must be 1 letter only");
				}
				lastJ = j + 2;
			}
		}
		stateNameTo = TRANSITION.substr(lastJ, TRANS_LEN - lastJ);

		std::cout << stateNameFrom << letter << stateNameTo << std::endl;

	}

}

FiniteStateMachine::FiniteStateMachine(const std::string &fileName) :
		Machine() {
	this->readFromFile(fileName);

}

FiniteStateMachine::~FiniteStateMachine() = default;

void FiniteStateMachine::addState(const State &newState) {
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

void FiniteStateMachine::addTransition(const State &from,
		const Transition &newTransition) {

}

bool FiniteStateMachine::accept(const std::string &word) {

	return false;
}
