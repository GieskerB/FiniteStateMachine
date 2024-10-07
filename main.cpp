
#include "includes.inc"

#include <iostream>
#include <fstream>

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

/**
 * Prints the introduction to the programm and let the user decide which kind of state machine he wants to use.
 *
 * @return
 */
MachineType intro() {
    int user_input{0};
    Machine* machine;
    std::cout << "Welcome to the Finite Automaton (FA) and Turing Machine (TM) Simulator!\n"
                 "\n"
                 "In this program, you can simulate the behavior of two fundamental models of computation: the DEA and the TM. These models are widely used in computer science and theoretical computer science to describe and analyze algorithms and languages.\n"
                 "A FA is a mathematical model of computation that recognizes languages defined by regular expressions. It consists of a finite set of states, a finite set of input symbols (the alphabet), a transition function, an initial state, and a set of accepting (or final) states.\n"
                 "A TM, on the other hand, is a more powerful model of computation that can simulate any algorithmic process. It consists of an infinite tape divided into cells, a read/write head that moves left or right along the tape, a finite set of states, a transition function, an initial state, and a set of accepting states.\n"
                 "\n";
    do {
        std::cout << "Please select which model you would like to simulate:\n"
                     "\n"
                     "1. Turing Machine (TM)\n"
                     "2. Finite Automaton (FA)\n"
                     "Enter the number corresponding to your choice and press Enter:\n"
                     "===";
        std::cin >> user_input;
    } while (std::cin and not(user_input == 1 or user_input == 2));

    if (user_input == 1) {
        return MachineType::TURING_MACHINE;
    } else {
        return MachineType::FINITE_AUTOMATON;
    }
}

int input_machine(Machine* machine ) {
    int user_input{0};
    do {
        std::cout << "How would you like to input the machine:\n"
                     "\n"
                     "1. Load it from a text file?\n"
                     "2. Enter it manually via the console?\n"
                     "Enter the number corresponding to your choice and press Enter:\n"
                     "===";
        std::cin >> user_input;
    } while (std::cin and not(user_input == 1 or user_input == 2));

    if (!std::cin) {
        std::cerr << "Invalid Input!\n";
        return 1;
    }

    std::cout << "Starting with input!\n";
    try {
        if (user_input == 1) {
            std::string file_name = "input";
            if(instanceof<TuringMachine>(machine)) {
                file_name += ".tm";
            } else if (instanceof<FiniteAutomaton>(machine)) {
                file_name +=  ".fa";
            } else {
                std::cerr << "Invalid state machine type detected!\n";
                return 1;
            }


            std::ifstream file(file_name);
            if(!file.good()) {
                file.open("../" + file_name);
                if(file.bad()) {
                    std::cerr << "Input file does not exists!\n";
                    file.close();
                    return 2;
                }
            }
            *machine << file;
            file.close();
        } else {
            std::cout << "Remember to follow the syntax from the README!\n";
            *machine << std::cin;
        }
    } catch (std::runtime_error &e) {
        std::cerr << e.what();
        return 2;
    }
    std::cout << "Input was successful!\n";
    return 0;
}

int do_action(Machine* machine) {
    int user_input_int{0};
    std::string user_input_string{};

    try {
        do {
            std::cout << "What would you like to do next?\n"
                         "\n"
                         "1. Test if the machine accepts a given word.\n"
                         "2. Generate a random word. (!WARNING! Infinit Loop)\n"
                         "3. Add a new State.\n"
                         "4. Add a new Transition.\n"
                         "5. Exit the programm.\n"
                         "Enter the number corresponding to your choice and press Enter:\n"
                         "===";
            std::cin >> user_input_int;
            if (user_input_int == 1) {
                std::cout << "Which word would you like to test?\n"
                             "===";
                std::cin >> user_input_string;
                if (machine->accept(user_input_string)) {
                    std::cout << ">>> Accepted!\n";
                } else {
                    std::cout << ">>> Not accepted!\n";
                }
            } else if (user_input_int == 2) {
                std::cout << "One random word is:\n"
                             ">>> " << machine->generate_random_word() << "\n";

            } else if (user_input_int == 3) {
            } else if (user_input_int == 4) {
            }
        } while (user_input_int != 5);
    } catch (std::runtime_error &e) {
        std::cerr << e.what();
        return 2;
    }


    return 0;
}

int main() {
    const MachineType machine_type = intro();

    if (!std::cin) {
        std::cerr << "Invalid Input!\n";
        return 1;
    }

    Machine* machine;
    switch (machine_type.m_index) {
        case 0:
            machine = new FiniteAutomaton();
            break;
        case 1:
            machine = new TuringMachine();
            break;
        default:
            // Do nothing
            break;
    }

    // If error_code == 0 its false. Otherwise, true.
    if(int error_code = input_machine(machine)) {
        delete machine;
        return error_code;
    }

    if(int error_code = do_action(machine)) {
        delete machine;
        return error_code;
    }

    return 0;
}
