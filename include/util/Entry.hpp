#pragma once

#include <memory>
#include <stdexcept>

/*
The Entry class is a generic container designed to manage elements in a linked list. It is intended to work with different data types using C++ templates.

Key Features:
- Generics: This Entry class is template-based, allowing it to store elements of various data types.
- Linked List: It represents an element in a linked list and maintains a reference to the next Entry in the list.

Constructor Options:
- The Entry class can be constructed with two variations:
1. An Entry with only an element, where it stores the element.
2. An Entry with both an element and a reference to the next Entry in line.

Access and Modification:
- It provides methods to access and manipulate the element and the next Entry in the list.
- 'getElement': Returns the element stored in the Entry.
- 'hasNextEntry': Checks if there is a next Entry in the list.
- 'getNextEntry': Retrieves the shared pointer to the next Entry.
- 'setNextEntry': Sets the next Entry in the list.

Usage:
- The Entry class is used in the creation of linked data structures such as stack and queues.

*/
template<typename T>
class Entry {
private:

    // Usage of shared pointers to make memory management easier.
	// Element stores a pointer to the value that the data structure are managing.
	const std::shared_ptr<T> element;

	// nextEntry stores a pointer to the following entry in the data structure.
	std::shared_ptr<Entry<T>> nextEntry;

public:

	// Default Constructor is useless in this context
	Entry() = delete;

	// Simple storing a value without the pointer to a next entry.
	Entry(const T &element) :
		element(std::make_shared<T>(element)) {}
	// storing the element and pointer to the next entry.
	Entry(const T &element, const Entry<T> &nextEntry) :
		element(std::make_shared<T>(element)),
		nextEntry(std::make_shared<Entry<T>>(nextEntry)) {}

    // Default destructor, because no need for destruction of any pointers.
	~Entry() = default;

    // Returns the element store the user wants to be stored in the datastructures
	T getElement() const {
		return *this->element;
	}

    // Check if the current Entry points to a next one
	bool hasNextEntry() const {
		return this->nextEntry.get() != nullptr;
	}

    // Returning the std::shared_pointer to the next entry
	std::shared_ptr<Entry<T>> getNextEntry() const {
		return this->nextEntry;
	}

    // Overwrites the next Entry with a new one.
	void setNextEntry(const Entry<T> &newNextEntry) {
		this->nextEntry = std::make_shared<Entry<T>>(newNextEntry);
	}
};
