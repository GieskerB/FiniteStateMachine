#include "../../include/machine/FiniteAutomaton.hpp"
#include <stdexcept>
#include <algorithm>
#include <random>

FiniteAutomaton::FiniteAutomaton() = default;

FiniteAutomaton::~FiniteAutomaton() = default;


std::istream &FiniteAutomaton::operator<<(std::istream &in_stream) {

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
                        throw std::runtime_error("Only one initial state is allowed for a FSM!\n");
                    } else if (!all_non_terminals.contains(*initial_non_terminal.begin())) {
                        throw std::runtime_error("Initial target_state '" + *initial_non_terminal.begin() +
                                                 "' must be an element of the prior defined states!\n");
                    }
                    break;

                case 2:
                    // Read the m_final non-terminal symbol
                    final_non_terminals = separate_by_comma(line);
                    for (const auto &final_non_terminal: final_non_terminals) {
                        if (!all_non_terminals.contains(final_non_terminal)) {
                            throw std::runtime_error("Final state '" + final_non_terminal +
                                                     "' must be an element of the prior defined states!\n");
                        }
                    }

                    for (const auto &name: all_non_terminals) {
                        State temp_state{name, initial_non_terminal.contains(name),
                                         final_non_terminals.contains(name)};
                        add_state(temp_state);
                    }
                    break;
                case 3:
                    // Read all terminal symbols
                    all_terminals = separate_by_comma(line);
                    for (auto &terminal: all_terminals) {
                        if (all_non_terminals.contains(terminal)) {
                            throw std::runtime_error(
                                    "Terminal symbole must not have the same m_name as a non terminal: '" + terminal +
                                    "'!\n");
                        }
                        add_letter(terminal);
                    }
                    break;
                case 4:
                    // Opening Bracket for the list of m_transitions
                    if (line != "{") {
                        throw std::runtime_error("Formation error. Expected '{' in line 5!\n");
                    }
                    break;
                default:
                    // Convert each line into a transition

                    const size_t comma_index = line.find(',');
                    const size_t arrow_index = line.find("->");
                    const std::string source_state_name = line.substr(0, comma_index);
                    const std::string input_symbole_name = line.substr(comma_index + 1, arrow_index - comma_index - 1);
                    const std::string target_state_name = line.substr(arrow_index + 2, line.size() - arrow_index - 2);

                    if (source_state_name.empty()) {
                        throw std::runtime_error(
                                "Error in transition " + line + " first argument has length of zero!\n");
                    }
                    if (input_symbole_name.size() != 1) {
                        throw std::runtime_error(
                                "Error in transition " + line + " second argument has length unequal to one!\n");
                    }
                    if (target_state_name.empty()) {
                        throw std::runtime_error(
                                "Error in transition " + line + " third argument has length of zero!\n");
                    }

                    State *source_state{nullptr}, *target_state{nullptr};
                    char input_symbole{'\0'};

                    //for( auto & compare_state: m_states) {
                    for (auto state_iterator{m_states.begin()}; state_iterator != m_states.end(); ++state_iterator) {
                        if (state_iterator->get_name() == source_state_name) {
                            source_state = &*state_iterator;
                        }

                        if (state_iterator->get_name() == target_state_name) {
                            target_state = &*state_iterator;
                        }
                    }
                    for (const char compare_symbole: m_alphabet) {
                        if (compare_symbole == input_symbole_name[0]) {
                            input_symbole = compare_symbole;
                        }
                    }

                    if (source_state == nullptr) {
                        throw std::runtime_error("Error in transition " + line +
                                                 " first argument does not match any previous declared states!\n");
                    }
                    if (input_symbole == '\0') {
                        throw std::runtime_error("Error in transition " + line +
                                                 " second argument does not match any previous declared symobles!\n");
                    }
                    if (target_state == nullptr) {
                        throw std::runtime_error("Error in transition " + line +
                                                 " third argument does not match any previous declared states!\n");
                    }

                    add_transition(*source_state, Transition{input_symbole, *target_state});


            }

            ++line_counter;
        }

        std::getline(in_stream, line);
        remove_spaces(line);
    }

    return in_stream;
}

void FiniteAutomaton::add_state(State &new_state) {
    for (auto &state: m_states) {
        if (state.get_name() == new_state.get_name()) {
            throw std::runtime_error("not allowed to use the same name twice for two different states!\n");
        }
    }
    m_states.push_back(std::move(new_state));

    if (new_state.is_initial()) {
        if (m_initial_state_index.has_value()) {
            throw std::runtime_error(
                    "FSM only allows one initial state!\n");
        } else {
            m_initial_state_index = m_states.size() - 1;
        }
    }
}


void FiniteAutomaton::add_transition(State &from,
                                     const Transition &new_transition) {


    bool deterministic_state = from.add_transition(new_transition);
    if (!deterministic_state and m_deterministic) {
        std::cout << "This FSM is now a non-deterministic machine!\n";
        m_deterministic = false;
    }


}

bool FiniteAutomaton::accept(const std::string &word) {

    const State *current_state{&m_states[m_initial_state_index.value()]};
    for (const auto &letter: word) {
        current_state = current_state->get_next_state(letter);
        if (current_state == nullptr) {
            return false;
        }
    }

    return current_state->is_final();

}

std::string FiniteAutomaton::generate_random_word() {
    std::string result;
    std::default_random_engine re{};
    std::vector<std::string> possible_results;


    const State *current_state{&m_states[m_initial_state_index.value()]};
    const int MAX_ITER = 1e4;
    for (int i{0}; i < MAX_ITER; ++i) {
        if (current_state->is_final()) {
            possible_results.push_back(result);
            std::uniform_real_distribution<double> random_finish_chance_generator{0, 1};
            if (random_finish_chance_generator(re) > 1 / possible_results.size()) {
                break;
            }
        }

        auto *random_transition = current_state->get_random_transition();

        if (random_transition == nullptr) {
            return "<< There was an error generating a word. Path found with an dead end in state " +
                   current_state->get_name() + ">>";
        }

        result.push_back(random_transition->get_letter());
        current_state = random_transition->get_target_state();
    }

    if (possible_results.empty()) {
        return "<< There was an error generating a word. Probably an infinit loop with a final state.>>";
    }

    std::uniform_int_distribution<int> random_index_generator{0, static_cast<int>(possible_results.size() -
                                                                                  1)};  // distribution that maps to the ints 1..6


    result = possible_results[random_index_generator(re)];
    return result;
}


