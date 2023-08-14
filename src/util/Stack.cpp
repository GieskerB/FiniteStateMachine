#ifndef SRC_UTIL_STACK_CPP_
#define SRC_UTIL_STACK_CPP_

#include "../../include/util/Stack.hpp"

template<typename T>
Stack<T>::Stack() :
		top(nullptr) {
}

template<typename T>
Stack<T>::~Stack() {
	this->clear();
}

template<typename T>
void Stack<T>::push(T *element) {
	Entry<T> *newTop = new Entry<T>(element);
	if (this->isEmpty()) {
		this->top = newTop;
	} else {
		newTop->setPredecessor(this->top);
		this->top = newTop;
	}
}

template<typename T>
void Stack<T>::push(const T &element) {
	this->push(*element);
}

template<typename T>
T* Stack<T>::pop() {
	Entry<T> *oldTop = this->top;
	// Setting the new top Element to null if oldTop was the last
	this->top = (oldTop->hasPredecessor()) ? oldTop->getPredecessor() : nullptr;
	T *elem = oldTop->getElement();
	delete oldTop;
	return elem;
}

template<typename T>
T* Stack<T>::peak() const {
	return this->top->getElement();
}

template<typename T>
bool Stack<T>::isEmpty() const {
	return this->top == nullptr;
}

template<typename T>
void Stack<T>::clear() {
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

#endif /* SRC_UTIL_STACK_CPP_ */
