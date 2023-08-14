#ifndef SRC_UTIL_QUEUE_CPP_
#define SRC_UTIL_QUEUE_CPP_

#include "../../include/util/Queue.hpp"

template<typename T>
Queue<T>::Queue() :
		head(nullptr), tail(nullptr) {
}

template<typename T>
Queue<T>::~Queue() {
	this->clear();
}

template<typename T>
void Queue<T>::enqueue(T *element) {
	Entry<T> *newTail = new Entry<T>(element);
	if (this->isEmpty()) {
		this->head = newTail;
		this->tail = newTail;
	} else {
		this->tail->setSuccessor(newTail);
		this->tail = newTail;
	}
}

template<typename T>
void Queue<T>::enqueue(const T &element) {
	this->enqueue(*element);
}

template<typename T>
T* Queue<T>::dequeue() {
	T *element = this->head->getElement();
	Entry<T> *tempEntry = this->head;
	this->head =
			this->head->hasSuccessor() ? this->head->getSuccessor() : nullptr;
	if (this->isEmpty()) {
		this->tail = nullptr;
	}
	delete tempEntry;
	return element;
}

template<typename T>
T* Queue<T>::peak() const {
	return this->head->getElement();
}

template<typename T>
bool Queue<T>::isEmpty() const {
	return this->head == nullptr;
}

template<typename T>
void Queue<T>::clear() {
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

#endif /* SRC_UTIL_QUEUE_CPP_ */
