#include "../../include/machine/TuringMachine.hpp"
#include <stdexcept>
#include <algorithm>

std::istream & TuringMachine::operator<<(std::istream &in_stream) {

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
TuringMachine::TuringMachine() : Machine(){

}

TuringMachine::~TuringMachine() = default;


void TuringMachine::add_state( State &newState) {
    /*
	if (newState.is_initial() && m_initial_state_index == -1) {
        m_initial_state_index = m_states.size()-1;
	} else if (newState.is_initial() && m_initial_state_index != -1) {
		throw std::runtime_error(
				"Turing-Machine only allows one m_initial State.");
	}
     */
}

void TuringMachine::add_transition(State &from,
                                   const Transition &newTransition) {

}

bool TuringMachine::accept(const std::string &word) {

	return false;
}

std::string TuringMachine::generate_random_word() {
    std::string result;
    return result;
}
