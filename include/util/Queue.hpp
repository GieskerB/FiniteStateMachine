#pragma once

#include "Entry.hpp"

template<typename T>
class Queue {
private:
	/*
	 * Referencing the head and tail of the Queue
	 */
	Entry<T> *head, *tail;

public:
	/*
	 * Creating a new empty Queue
	 */
	Queue() :
			head(nullptr), tail(nullptr) {
	}

	/*
	 * Deleting the Queue completely
	 */
	~Queue() {
		this->clear();
	}

	/*
	 * Adding a new element into the back of the Queue
	 */
	void enqueue(T *element) {
		Entry<T> *newTail = new Entry<T>(element);
		if (this->isEmpty()) {
			this->head = newTail;
			this->tail = newTail;
		} else {
			this->tail->setSuccessor(newTail);
			this->tail = newTail;
		}
	}
	void enqueue(const T &element) {
		this->enqueue(*element);
	}

	/*
	 * Removing the first element from the Queue
	 */
	T* dequeue() {
		T *element = this->head->getElement();
		Entry<T> *tempEntry = this->head;
		this->head = this->head->getSuccessor();
		if (this->isEmpty()) {
			this->tail = nullptr;
		}
		delete tempEntry;
		return element;
	}

	/*
	 * simply looking at the first element of the Queue without removing it
	 */
	T* peak() const {
		return this->head->getElement();
	}

	/*
	 * Checks if Queue has at least one element stored in it or not
	 */
	bool isEmpty() const {
		return this->head == nullptr;
	}

	/*
	 * Deletes the content of the Queue completely
	 */
	void clear() {
		if (this->isEmpty()) {
			return;
		}

		Entry<T> *temp;
		while (this->head->hasSuccessor()) {
			temp = this->head->getSuccessor();
			delete this->head;
			this->head = temp;
		}
		delete this->head;
		this->head = nullptr;
		this->tail = nullptr;
	}
};
