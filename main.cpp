
#include "includes.inc"

#include <iostream>
#include <fstream>

bool testing_input_machine_choice( std::string &test) {
    if (test == "1" or test == "Finite State Machine" or test == "FSM") {
        test = "1";
        return true;
    }
    if (test == "2" or test == "Turing Machine" or test == "TM") {
        test = "2";
        return true;
    }
    return false;
}

bool testing_input_input_choice( std::string &test) {
    if (test == "1" or test == "text file") {
        test = "1";
        return true;
    }
    if (test == "2" or test == "console") {
        test = "2";
        return true;
    }
    return false;
}

int main() {

    Machine* fsm;
    fsm = new FiniteStateMachine();

    std::ifstream file {"../Input.fsm"};

    *fsm << file;

    std::cout << fsm->accept("abbababa");

    /*

    bool is_turing_machine;
    Machine *machine;
    std::string user_input{0};
    std::cout << "Welcome to the Finite State Machine (FSM) and Turing Machine (TM) Simulator!\n"
                 "\n"
                 "In this program, you can simulate the behavior of two fundamental models of computation: the DEA and the TM. These models are widely used in computer science and theoretical computer science to describe and analyze algorithms and languages.\n"
                 "A Finite State Machine (FSM) is a mathematical model of computation that recognizes languages defined by regular expressions. It consists of a finite set of states, a finite set of input symbols (the alphabet), a transition function, an initial state, and a set of accepting (or final) states.\n"
                 "A Turing Machine (TM), on the other hand, is a more powerful model of computation that can simulate any algorithmic process. It consists of an infinite tape divided into cells, a read/write head that moves left or right along the tape, a finite set of states, a transition function, an initial state, and a set of accepting states.\n"
                 "\n";
    do {
        std::cout << "Please select which model you would like to simulate:\n"
                     "\n"
                     "1. Finite State Machine (FSM)\n"
                     "2. Turing Machine (TM)\n"
                     "Enter the number / name / abbreviation corresponding to your choice and press Enter:\n"
                     "=== ";
        std::cin >> user_input;
    } while (!testing_input_machine_choice(user_input));

    std::cout << user_input;

    if (user_input == "1") {
        machine = new FiniteStateMachine();
        is_turing_machine = false;
    } else {
        machine = new TuringMachine();
        is_turing_machine = true;
    }
    user_input.clear();
    do {
        std::cout << "How would you like to input the machine:\n"
                     "\n"
                     "1. Load it from a text file?\n"
                     "2. Enter it manually via the console?\n"
                     "Enter the number / source corresponding to your choice and press Enter:\n"
                     "=== ";
        std::cin >> user_input;
    } while (!testing_input_input_choice(user_input));

    std::cout << "fjasdflhkaskd";

    if(user_input == "1") {
        std::string file_name = "Input";
        file_name+= is_turing_machine ? ".tm" : ".fsm";
        std::ifstream file(file_name);

        FiniteStateMachine fsm{};

        std::cout << file_name;

        file >> fsm;

        //file >> * machine;
        //file >> * dynamic_cast<FiniteStateMachine* > (machine);
    } else {

    }



     */
    return 0;
}
