#include <io.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>

#include <filesystem>

#include <string_view>
#include <memory>

/*
 * 1. Fehler Management -> exceptions (nachrichten)
 * 1b. assertions
 * 2. Pointer... (smartpointer)
 * 3. keine Shadowcopy -> delete copy const und = operator
 * 4. MinGw updaten (cygwin)
 */

#include "include/machine/FiniteStateMachine.hpp"
#include "include/machine/TuringMachine.hpp"

Machine* initMachine(const std::string &INPUT_FILE_NAME) {
	int nameIndex = INPUT_FILE_NAME.length() - 1;
	while (nameIndex >= 0 && INPUT_FILE_NAME.at(nameIndex) != '.') {
		nameIndex--;
	}
	if (nameIndex < 0) {
		throw std::invalid_argument(
				"incorrect filename!\nIt must have an file extension.");
	}
	const std::string FILE_EXTENSION = INPUT_FILE_NAME.substr(nameIndex,
			INPUT_FILE_NAME.length() - nameIndex);

	Machine *machine;
	if (FILE_EXTENSION == ".tm") {
		machine = new TuringMachine(INPUT_FILE_NAME);
	} else if (FILE_EXTENSION == ".fsm") {
		machine = new FiniteStateMachine(INPUT_FILE_NAME);
	} else {
		machine = nullptr;
		throw std::invalid_argument(
				"incorrect file extension!\n" + INPUT_FILE_NAME
						+ " is currently not supported");
	}

	machine->accept("");

	return machine;
}


int main(int argc, char** argv) {
	//Hello
	std::srand((unsigned) std::time(nullptr));

    std::string_view a;

	//const std::filesystem::path CURRENT_DIR = std::filesystem::current_path();
    //const std::string pathStr =CURRENT_DIR.string();
    //Machine *machine = initMachine(pathStr + "\\" + INPUT_FILE_NAME);

    const std::string INPUT_FILE_NAME = "Input.fsm";
    Machine *machine = initMachine(INPUT_FILE_NAME);

	delete machine;

	return 0;
}
