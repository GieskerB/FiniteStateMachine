
#include "includes.inc"

#include <iostream>
#include <fstream>

int main() {
    FiniteStateMachine fsm;

    std::ifstream file{"../Input.fsm"};

    file >> fsm;

    std::cout << "Test word\n===";

    std::string input;
    std::cin >> input;

    fsm.accept(input);


	return 0;
}
