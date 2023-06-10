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
	if (this->head == nullptr) {
		this->head = newTail;
		this->tail = this->head;
	} else {
		newTail->setSuccessor(this->head);
		this->tail = newTail;
	}
}

template<typename T>
void Queue<T>::enqueue(const T &element) {
	this->enqueue(new T(element));
}

template<typename T>
T* Queue<T>::dequeue() {
	T *element = this->head->getElement();
	Entry<T> *tempEntry = this->head;
	tempEntry = this->head;
	this->head = this->head->getSuccessor();
	if (this->head == nullptr) {
		this->tail = nullptr;
	}
	delete tempEntry;
	return element;
}

template<typename T>
T* Queue<T>::peak() {
	return this->head->getElement();
}

template<typename T>
bool Queue<T>::isEmpty() {
	return this->head == nullptr;
}

template<typename T>
void Queue<T>::clear() {
	Entry<T> *temp, *tempEntry = this->head;
	while (tempEntry != nullptr) {
		temp = tempEntry;
		tempEntry = tempEntry->getSuccessor();
		delete temp;
	}
	this->head = nullptr;
	this->tail = nullptr;
}

template<typename T>
int Queue<T>::size() {
	Entry<T> *tempEntry = this->head;
	int size = 0;
	while (tempEntry != nullptr) {
		tempEntry = tempEntry->getSuccessor();
		size++;
	}
	return size;
}

#endif /* SRC_UTIL_QUEUE_CPP_ */
