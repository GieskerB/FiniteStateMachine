#pragma once

#include "Entry.hpp"

template<typename T>
class Stack {
private:
	/*
	 * Only having a reference to the top most element of the Stack
	 */
	Entry<T> *top;

public:
	/*
	 * Creating a new empty Stack
	 */
	Stack() :
			top(nullptr) {
	}

	/*
	 * Deleting the Stack completely
	 */
	~Stack() {
		this->clear();
	}

	/*
	 * Adding a new element onto the Stack
	 */
	void push(T *element) {
		Entry<T> *newTop = new Entry<T>(element);
		if (this->isEmpty()) {
			this->top = newTop;
		} else {
			newTop->setPredecessor(this->top);
			this->top = newTop;
		}
	}
	void push(const T &element) {
		this->push(*element);
	}

	/*
	 * Removing the top most element from the Stack
	 */
	T* pop() {
		Entry<T> *oldTop = this->top;
		this->top = oldTop->getPredecessor();
		T *elem = oldTop->getElement();
		delete oldTop;
		return elem;
	}

	/*
	 * simply looking at the top most element of the Stack without removing it
	 */
	T* peak() const {
		return this->top->getElement();
	}

	/*
	 * Checks if Stack has at least one element stored in it or not
	 */
	bool isEmpty() const {
		return this->top == nullptr;
	}

	/*
	 * Deletes the content of the Stack completely
	 */
	void clear() {
		if (this->isEmpty()) {
			return;
		}
		Entry<T> *temp;
		while (this->top->hasPredecessor()) {
			temp = this->top->getPredecessor();
			delete this->top;
			this->top = temp;
		}
		delete this->top;
		this->top = nullptr;
	}
};
