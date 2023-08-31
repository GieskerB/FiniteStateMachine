#include <iostream>

#include "includes.inc"
#include "include/util/Knot.hpp"
#include "src/util/Knot.cpp"

int main() {
	Knot<int> knot;
	Knot<int> knot2 = Knot<int>(&knot);
	std::cout << knot2.hasParent();
	// std::cout << "Hello,World!";

	// DynArray<int> dynArray;

	// // Test addFirst
	// for (int i = 0; i < 10; ++i) {
	// 	dynArray.addFirst(new int(i));
	// }

	// // Test addLast
	// for (int i = 10; i < 20; ++i) {
	// 	dynArray.addLast(new int(i));
	// }

	// // Test get and set
	// for (int i = 0; i < dynArray.size(); ++i) {
	// 	std::cout << *dynArray.get(i) << " ";
	// }
	// std::cout << std::endl;

	// dynArray.set(5, new int(99));
	// std::cout << "After set: " << *dynArray.get(5) << std::endl;

	// // Test remove
	// dynArray.remove(8);
	// std::cout << "After remove: ";
	// for (int i = 0; i < dynArray.size(); ++i) {
	// 	std::cout << *dynArray.get(i) << " ";
	// }
	// std::cout << std::endl;

	// // Test add at specific index
	// dynArray.add(3, new int(100));
	// std::cout << "After add at index 3: ";
	// for (int i = 0; i < dynArray.size(); ++i) {
	// 	std::cout << *dynArray.get(i) << " ";
	// }
	// std::cout << std::endl;

	// // Test removeFirst and removeLast
	// dynArray.removeFirst();
	// dynArray.removeLast();
	// std::cout << "After removeFirst and removeLast: ";
	// for (int i = 0; i < dynArray.size(); ++i) {
	// 	std::cout << *dynArray.get(i) << " ";
	// }
	// std::cout << std::endl;

	// // Test clear and isEmpty
	// dynArray.clear();
	// std::cout << "Is empty: " << (dynArray.isEmpty() ? "Yes" : "No")
	// 	<< std::endl;

	return 0;
}
