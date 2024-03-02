#include "../../include/machine/FiniteStateMachine.hpp"
#include <stdexcept>

FiniteStateMachine::FiniteStateMachine() = default;

FiniteStateMachine::~FiniteStateMachine() = default;


std::istream &FiniteStateMachine::operator>>(std::istream &in_stream) {

    std::string line;
    std::set<std::string> all_non_terminals{};
    std::set<std::string> initial_non_terminal{};
    std::set<std::string> final_non_terminals{};
    std::set<std::string> all_terminals{};

    std::getline(in_stream, line);
    remove_spaces(line);

    unsigned int line_counter = 0;
    while (line != "}") {
        if (!(line.empty() or (line.size() >= 2 and line[0] == '/' and line[1] == '/'))) {

            switch (line_counter) {
                case 0:
                    // Read all non-terminal symbols
                    all_non_terminals = separate_by_comma(line);
                    break;
                case 1:
                    // Read the m_initial non-terminal symbol
                    initial_non_terminal = separate_by_comma(line);
                    if (initial_non_terminal.size() > 1) {
                        throw std::runtime_error("Only one m_initial p_target_state is allowed for a FSM!\n");
                    } else if (!all_non_terminals.contains(*initial_non_terminal.begin())) {
                        throw std::runtime_error("Initial p_target_state '" + *initial_non_terminal.begin() +
                                                 "' must be an element of the prior defined states!\n");
                    }

                    break;

                case 2:
                    // Read the m_final non-terminal symbol
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

                    break;
                case 3:
                    // Read all terminal symbols
                    all_terminals = separate_by_comma(line);
                    for (auto &terminal: all_terminals) {
                        if (all_non_terminals.contains(terminal)) {
                            throw std::runtime_error(
                                    "Temrinal symbole must not have the same m_name as a non terminal: '" + terminal +
                                    "'!\n");
                        }
                        add_letter(terminal);
                    }
                    break;
                case 4:
                    // Opening Bracket for the list of m_transitions
                    if (line != "{") {
                        throw std::runtime_error("Formation error. Exprected '{' in line 5!\n");
                    }
                    break;
                default:
                    // Convert each line into a transition

                    const size_t comma_index = line.find(',');
                    const size_t arrow_index = line.find("->");
                    const std::string source_state_name = line.substr(0, comma_index);
                    const std::string input_symbole_name = line.substr(comma_index + 1, arrow_index - comma_index - 1);
                    const std::string target_state_name = line.substr(arrow_index + 2, line.size() - arrow_index - 2);

                    if(source_state_name.empty()) {
                        throw std::runtime_error("Error in transition " + line + " first argument has length of zero!\n");
                    }
                    if(input_symbole_name.size() != 1) {
                        throw std::runtime_error("Error in transition " + line + " second argument has length unequal to one!\n");
                    }
                    if(target_state_name.empty()) {
                        throw std::runtime_error("Error in transition " + line + " third argument has length of zero!\n");
                    }

                    State source_state{}, target_state{};
                    char input_symbole{'\0'};

                    for(auto & compare_state: m_states) {
                        if(compare_state.get_name() == source_state_name) {
                            source_state = compare_state;
                        }

                        if(compare_state.get_name() == target_state_name) {
                            target_state = compare_state;
                        }
                    }

                    for (auto & compare_symbole: m_alphabet) {
                        if(compare_symbole == input_symbole_name[0]) {
                            input_symbole = compare_symbole;
                        }
                    }

                    if(source_state.is_dummy()) {
                        throw std::runtime_error("Error in transition " + line + " first argument does not match any previous declared states!\n");
                    }
                    if(input_symbole == '\0') {
                        throw std::runtime_error("Error in transition " + line + " second argument does not match any previous declared symobles!\n");
                    }
                    if(target_state.is_dummy()) {
                        throw std::runtime_error("Error in transition " + line + " third argument does not match any previous declared states!\n");
                    }

                   add_transition(source_state, Transition{input_symbole, target_state});


            }

            ++line_counter;
        }

        std::getline(in_stream, line);
        remove_spaces(line);
    }

    return in_stream;
}

std::istream &operator>>(std::istream &is, FiniteStateMachine &fsm) {
    return fsm.operator>>(is);
}

void FiniteStateMachine::add_state(const State &new_state) {
    for (auto &state: m_states) {
        if (state.get_name() == new_state.get_name()) {
            throw std::runtime_error("not allowed to use the same name twice for two different states!\n");
        }
    }
    m_states.push_back(new_state);
    if (new_state.is_initial() && p_initial_state == nullptr) {
        p_initial_state = &m_states[m_states.size() - 1];
    } else if (new_state.is_initial() &&  p_initial_state != nullptr) {
        std::cout << new_state.get_name();
        throw std::runtime_error(
                "FSM only allows one initial state!\n");
    }
}


void FiniteStateMachine::add_transition(State &from,
                                        const Transition &new_transition) {


    bool deterministic_state = from.add_transition(new_transition);
    if(!deterministic_state and m_deterministic) {
        std::cout << "This FSM is now a non-deterministic machine!\n";
        m_deterministic = false;
    }



}

bool FiniteStateMachine::accept(const std::string &word) {

    State* next_state{nullptr};
    p_current_state = p_initial_state;
    for(const auto& state: m_states) {
        std::cout << state.to_string() << '\n';
    }
    for(auto& letter: word) {
        p_current_state->get_next_state(letter);
    }

}
