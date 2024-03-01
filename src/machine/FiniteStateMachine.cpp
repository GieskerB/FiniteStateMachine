#include "../../include/machine/FiniteStateMachine.hpp"
#include <stdexcept>


std::istream &FiniteStateMachine::operator>>(std::istream &in_stream) {

    std::string line;
    std::set<std::string> all_non_terminals{};
    std::set<std::string> initial_non_terminal{};
    std::set<std::string> final_non_terminals{};
    std::set<std::string> all_terminals{};

    std::getline(in_stream, line);
    remove_spaces(line);

    int line_counter = 0;
    while (line != "}") {
        if (line.empty() or (line.size() >= 2 and line[0] == '/' and line[1] == '/')) {
            continue; // TODO Wrong to continue
        }
        switch (line_counter) {
            case 0:
                // Read all non-terminal symbols
                all_non_terminals = separate_by_comma(line);
                ++line_counter;
                break;
            case 1:
                // Read the initial non-terminal symbol
                initial_non_terminal = separate_by_comma(line);
                if (initial_non_terminal.size() > 1) {
                    throw std::runtime_error("Only one initial state is allowed for a FSM!\n");
                } else if (!all_non_terminals.contains(*initial_non_terminal.begin())) {
                    throw std::runtime_error("Initial state '" + *initial_non_terminal.begin() +
                                             "' must be an element of the prior defined states!\n");
                }

                ++line_counter;
                break;

            case 2:
                // Read the final non-terminal symbol
                final_non_terminals = separate_by_comma(line);
                for (auto &final_non_terminal: final_non_terminals) {
                    if (!all_non_terminals.contains(final_non_terminal)) {
                        throw std::runtime_error("Final state '" + final_non_terminal +
                                                 "' must be an element of the prior defined states!\n");
                    }
                }

                for (auto &name: all_non_terminals) {
                    add_state(State{name, initial_non_terminal.contains(name),
                                    final_non_terminals.contains(name)});
                }

                ++line_counter;
                break;
            case 3:
                // Read all terminal symbols
                all_terminals = separate_by_comma(line);
                for (auto &terminal: all_terminals) {
                    if (all_non_terminals.contains(terminal)) {
                        throw std::runtime_error(
                                "Temrinal symbole must not have the same name as a non terminal: '" + terminal +
                                "'!\n");
                    }
                    // TODO adding!
                }

                ++line_counter;
                break;

        }

        std::getline(in_stream, line);
        remove_spaces(line);
    }

    return in_stream;
}

std::istream &operator>>(std::istream &is, FiniteStateMachine &fsm) {
    return fsm.operator>>(is);
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

	// get all m_alphabet characters
	setupAlphabet(*inputLines.get(3));

	//Initializing all the m_states
	const int stateNum = allStates.size();
	for (int i = 0; i < stateNum; i++) {
		const std::string name = *allStates.get(i);
		add_state(
				State(name, finalStates.indexOf(name) != -1,
						*initialStates.getFirst() == name));
	}
	setupTransitions(inputLines);
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

FiniteStateMachine::FiniteStateMachine() = default;

FiniteStateMachine::~FiniteStateMachine() = default;

void FiniteStateMachine::add_state(const State &new_state) {
    for (auto &state: m_states) {
        if (state.get_name() == new_state.get_name()) {
            throw std::runtime_error("not allowed to use the same name twice for two different states!\n");
        }
    }

    if (new_state.is_initial() && !m_has_initial_state) {
        p_current_state = &m_states[m_states.size() - 1];
        m_has_initial_state = true;
    } else if (new_state.is_initial() && m_has_initial_state) {
        throw std::runtime_error(
                "FSM only allows one initial state!\n");
    }
}

void FiniteStateMachine::addTransition(const State &from,
                                       const Transition &newTransition) {

}

bool FiniteStateMachine::accept(const std::string &word) {

    return false;
}
