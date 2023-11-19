#include <io.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>

#include "includes.inc"

#include "include/machine/FiniteStateMachine.hpp"
#include "include/machine/TuringMachine.hpp"
/*
Machine *initMachine(const std::string &INPUT_FILE_NAME) {
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
	}
	else if (FILE_EXTENSION == ".fsm") {
		machine = new FiniteStateMachine(INPUT_FILE_NAME);
	}
	else {
		machine = nullptr;
		throw std::invalid_argument(
			"incorrect file extension!\n" + INPUT_FILE_NAME
			+ " is currently not supported");
	}

	machine->accept("");

	return machine;
}

*/

/*
 * https://www.tutorialspoint.com/find-out-the-current-working-directory-in-c-cplusplus

std::string getCurrentDir() {
	char buff[FILENAME_MAX]; //create string buffer to hold path
	_getcwd(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}
*/


int main() {

	DynArray<int> dynArray;

	dynArray.addLast(1);
	dynArray.addLast(2);
	dynArray.addLast(3);
	dynArray.addLast(4);
	dynArray.addLast(5);

	for (int i : dynArray) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	for (auto it = dynArray.begin(); it != dynArray.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	/*
	std::srand((unsigned)std::time(nullptr));

	const std::string CURRENT_DIR = getCurrentDir();
	const std::string INPUT_FILE_NAME = "Input.fsm";

	Machine *machine = initMachine(CURRENT_DIR + "\\" + INPUT_FILE_NAME);

	delete machine;
	*/
	return 0;

}
