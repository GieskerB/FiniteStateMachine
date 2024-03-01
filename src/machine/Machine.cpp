#include "../../include/machine/Machine.hpp"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <stdexcept>




std::vector<std::string> Machine::extractNames(const std::string &line) {
    std::vector<std::string> states;
	std::string name;

	const uint32_t len = line.length();

	int lastComma = -1;

	for (uint32_t i = 0; i < len; i++) {
		if (line.at(i) == ',') {
			name = line.substr(lastComma + 1, i - lastComma - 1);
			lastComma = i;
			states.push_back(name);
		}
	}
	name = line.substr(lastComma + 1, len - lastComma - 1);
	states.push_back(name);
	return states;
}

void Machine::checkForMistake(const std::vector<std::string> &initialStates,
		const std::vector<std::string> &allStates) {
	// Stops the program if user made wrong Input
/*	if (initialStates.size() != 1) {
		throw std::invalid_argument(
				"There must be exact one initial-state. currently there are "
						+ std::to_string(initialStates.size()));
	} else if (allStates.indexOf(*initialStates.getFirst()) == -1) {
		throw std::invalid_argument(
				"initial-state '" + *initialStates.getFirst()
						+ "' must be a predefined state.");
	}
 */
}

std::vector<std::string> Machine::getInput(const std::string &fileName) {
	std::ifstream inputFile;
	inputFile.open(fileName);
    std::vector<std::string> inputLines;
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

			inputLines.push_back(line);
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
			m_alphabet.push_back(character);
		}
	}
	character = line.at(len - 1);
	m_alphabet.push_back(character);
}

Machine::Machine() :
        p_current_state(nullptr), deterministic(false), m_has_initial_state(false) {

}

Machine::~Machine() = default;

void remove_spaces(std::string& str) {
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

std::set<std::string> separate_by_comma(const std::string & line) {
    std::set<std::string> sections{};
    const size_t size = line.size();
    int left_index{0}, right_index{0};
    while (right_index < size) {
        if(line[right_index] == ',') {
            sections.insert(line.substr(left_index, right_index - left_index));
            left_index = right_index+1;
        }
        ++right_index;
    }
    sections.insert(line.substr(left_index, right_index - left_index));

    return sections;
}