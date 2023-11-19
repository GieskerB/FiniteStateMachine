#pragma once

#include "Entry.hpp"

/*
   This is a versatile generic Queue class, a fundamental data structure that follows the First-In-First-Out (FIFO) principle. It emulates a queue of items, where the first item added is the first to be removed.

   Key Features:
   - Generics: This Queue class is template-based, allowing it to work with a wide range of data types, making it highly adaptable for various applications.

   Basic Operations:
   - 'enqueue': Adds an element to the back of the queue.
   - 'dequeue': Removes and returns the front element from the queue.
   - 'isEmpty': Checks whether the queue is empty.
   - 'clear': Removes all elements from the queue, effectively emptying the queue.

   How to Use:
   - To employ this Queue, declare an instance with the desired data type (e.g., Queue<int> for integers) and perform 'enqueue', 'dequeue', and 'isEmpty' operations as needed.
*/

template<typename T>
class Queue {
private:

	// Usage of shared pointers to make memory management easier.
	// Head and tail store pointers to the first and last element of the queue.
	// Ares a null pointers by default
	std::shared_ptr<Entry<T>> head, tail;

public:

	// Default constructor, because no need for initialization of any variables.
	Queue() = default;

	// When deleting a queue first clear its content.
	~Queue() {
		this->clear();
	}

	// Enqueues a new element to the queue
	void enqueue(const T &element) {
		std::shared_ptr<Entry<T>> newTail = std::make_shared<Entry<T>>(element);
		if (this->isEmpty()) {
			this->head = newTail;
			this->tail = newTail;
		}
		else {
			// If it's not empty connect the new head to the previous head.
			this->tail->setNextEntry(*newTail);
			this->tail = newTail;
		}
	}

	// Removes the first element from the queue and returns it.
	T dequeue() {
		if (this->isEmpty) { throw std::runtime_error("unable to dequeue form empty queue"); }
		T element = this->head->getElement();
		this->head = this->head->getNextEntry();
		if (this->isEmpty()) {
			this->tail.reset();
		}
		return element;
	}

	// Only looks at the head without removing it from the queue.
	T peek() const {
		if (this->isEmpty) { throw std::runtime_error("unable to peek form empty queue"); }
		return this->head->getElement();
	}

	// Check if the queue has no elements stored.
	bool isEmpty() const {
		return this->head.get() == nullptr;
	}

	// Removes all the elements from the queue.
	void clear() {
		if (this->isEmpty()) {
			return;
		}
		this->head.reset();
		this->tail.reset();

	}
};
