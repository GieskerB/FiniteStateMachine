#include <iostream>

#include "includes.inc"

int main() {
	std::string name = "Bjarne";

	Queue<std::string> queue = Queue<std::string>();
	queue.enqueue(&name);

	std::string str = *queue.peak();

	std::cout << str << std::endl;

	queue.dequeue();
	std::cout << str << std::endl;


	queue.dequeue();
	std::cout << str << std::endl;

	return 0;
}
