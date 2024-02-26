#pragma once

#include <memory>
#include <stdexcept>

/*
The Entry class is a generic container designed to manage elements in a linked list. It is intended to work with different data types using C++ templates.

Key Features:
- Generics: This Entry class is template-based, allowing it to store elements of various data types.
- Linked List: It represents an m_element in a linked list and maintains a reference to the next Entry in the list.

Constructor Options:
- The Entry class can be constructed with two variations:
1. An Entry with only an m_element, where it stores the m_element.
2. An Entry with both an m_element and a reference to the next Entry in line.

Access and Modification:
- It provides methods to access and manipulate the m_element and the next Entry in the list.
- 'get_element': Returns the m_element stored in the Entry.
- 'has_next_entry': Checks if there is a next Entry in the list.
- 'get_next_entry': Retrieves the shared pointer to the next Entry.
- 'set_next_entry': Sets the next Entry in the list.

Usage:
- The Entry class is used in the creation of linked data structures such as stack and queues.

*/
template<typename T>
class Entry {
private:

    // Usage of shared pointers to make memory management easier.
	// m_element stores a pointer to the value that the data structure are managing.
	const std::shared_ptr<T> m_element;

	// m_next_entry stores a pointer to the following entry in the data structure.
	std::shared_ptr<Entry<T>> m_next_entry;

public:

	// Default Constructor is useless in this context
	Entry() = delete;

	// Simple storing a value without the pointer to a next entry.
	explicit Entry(const T &element) :
            m_element(std::make_shared<T>(element)) {}
	// storing the m_element and pointer to the next entry.
	Entry(const T &element, const Entry<T> &next_entry) :
            m_element(std::make_shared<T>(element)),
            m_next_entry(std::make_shared<Entry<T>>(next_entry)) {}

    // Default destructor, because no need for destruction of any pointers.
	~Entry() = default;

    // Returns the m_element store the user wants to be stored in the datastructures
	T get_element() const {
		return *m_element;
	}

    // Check if the current Entry points to a next one
	[[nodiscard]] bool has_next_entry() const{
        return m_next_entry.get() != nullptr;
    }

    // Returning the std::shared_pointer to the next entry
	std::shared_ptr<Entry<T>> get_next_entry() const {
		return m_next_entry;
	}

    // Overwrites the next Entry with a new one.
	void set_next_entry(const std::shared_ptr<Entry<T>> &next_entry) {
        m_next_entry = next_entry;
	}
};