#pragma once

#include "Entry.hpp"

/*
   This is a versatile generic Queue class, a fundamental data structure that follows the First-In-First-Out (FIFO) principle. It emulates a queue of items, where the first item added is the first to be removed.

   Key Features:
   - Generics: This Queue class is template-based, allowing it to work with a wide range of data types, making it highly adaptable for various applications.

   Basic Operations:
   - 'enqueue': Adds an m_element to the back of the queue.
   - 'dequeue': Removes and returns the front m_element from the queue.
   - 'is_empty': Checks whether the queue is empty.
   - 'clear': Removes all elements from the queue, effectively emptying the queue.

   How to Use:
   - To employ this Queue, declare an instance with the desired data type (e.g., Queue<int> for integers) and perform 'enqueue', 'dequeue', and 'is_empty' operations as needed.
*/

template<typename T>
class Queue {
private:

	// Usage of shared pointers to make memory management easier.
	// Head and m_tail store pointers to the first and last m_element of the queue.
	// Ares a null pointers by default
	std::shared_ptr<Entry<T>> m_head, m_tail;

public:

	// Default constructor, because no need for initialization of any variables.
	Queue() = default;

	// When deleting a queue first clear its content.
	~Queue() {
		clear();
	}
	// Enqueues a new m_element to the queue
	void enqueue(const T &element) {
		std::shared_ptr<Entry<T>> new_tail = std::make_shared<Entry<T>>(element);
		if (is_empty()) {
            m_head = new_tail;
		}
		else {
			// If it's not empty connect the new m_head to the previous m_head.
            m_tail->set_next_entry(new_tail);
		}
        m_tail = new_tail;
	}

	// Removes the first m_element from the queue and returns it.
	T dequeue() {
		if (is_empty()) { throw std::runtime_error("unable to dequeue form empty queue"); }
		T temp_element = m_head->get_element();
        m_head = m_head->get_next_entry();
		if (is_empty()) {
			m_tail.reset();
		}
		return temp_element;
	}

	// Only looks at the m_head without removing it from the queue.
	T head() const {
		if (is_empty()) { throw std::runtime_error("empty queue has no head"); }
		return m_head->get_element();
	}

	// Check if the queue has no elements stored.
	[[nodiscard]] bool is_empty() const {
		return m_head.get() == nullptr;
	}

	// Removes all the elements from the queue.
	void clear() {
		if (is_empty()) {
			return;
		}
		m_head.reset();
		m_tail.reset();

	}
};
