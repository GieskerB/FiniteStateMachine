#include "../../include/machine/Machine.hpp"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

#include "../../include/util/DynArray.hpp"

DynArray<std::string> Machine::extractNames(const std::string &line) {
	DynArray<std::string> states;
	std::string name;

	const uint32_t len = line.length();

	int lastComma = -1;

	for (uint32_t i = 0; i < len; i++) {
		if (line.at(i) == ',') {
			name = line.substr(lastComma + 1, i - lastComma - 1);
			lastComma = i;
			states.addLast(name);
		}
	}
	name = line.substr(lastComma + 1, len - lastComma - 1);
	states.addLast(name);
	return states;
}

void Machine::checkForMistake(const DynArray<std::string> &initialStates,
		const DynArray<std::string> &allStates) {
	// Stops the program if user made wrong Input
	if (initialStates.size() != 1) {
		throw std::invalid_argument(
				"There must be exact one initial-state. currently there are "
						+ std::to_string(initialStates.size()));
	} else if (allStates.indexOf(*initialStates.getFirst()) == -1) {
		throw std::invalid_argument(
				"initial-state '" + *initialStates.getFirst()
						+ "' must be a predefined state.");
	}
}

DynArray<std::string> Machine::getInput(const std::string &fileName) {
	std::ifstream inputFile;
	inputFile.open(fileName);
	DynArray<std::string> inputLines;
	if (inputFile.is_open()) {
		std::string line;
		while (getline(inputFile, line)) {
			// If line is Empty or starts with a "//" skip it
			if (line.length() == 0
					|| (line.length() >= 2 && line.at(0) == '/'
							&& line.at(1) == '/')) {
				continue;
			}
			// removes all spaces form the string
			line.erase(std::remove_if(line.begin(), line.end(), isspace),
					line.end());

			inputLines.addLast(line);
		}
		inputFile.close();
	} else {
        throw std::runtime_error("File could not be opened!");
    }
	inputFile.close();
	return inputLines;
}

void Machine::setupAlphabet(const std::string &line) {
	const uint32_t len = line.length();

	char character;
	for (uint32_t i = 0; i < len; i++) {
		if (line.at(i) == ',') {
			character = line.at(i - 1);
			alphabet.addLast(character);
		}
	}
	character = line.at(len - 1);
	alphabet.addLast(character);
}

Machine::Machine() :
		currentState(nullptr), deterministic(false), hasInitalState(false) {

}

Machine::~Machine() = default;
