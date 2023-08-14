#ifndef INCLUDE_UTIL_DYNARRAY_CPP_
#define INCLUDE_UTIL_DYNARRAY_CPP_

#include "../../include/util/DynArray.hpp"

template<typename T>
DynArray<T>::DynArray() :
		DynArray(10) {
}

template<typename T>
DynArray<T>::DynArray(int preDefinedSize) :
		initialSize(preDefinedSize), currentSize(0), maxSize(preDefinedSize) {
	this->elements = new T*[this->maxSize];
}

template<typename T>
DynArray<T>::~DynArray() {
	this->clear();
	delete[] this->elements;
}

template<typename T>
T* DynArray<T>::getFirst() const {
	return this->get(0);
}

template<typename T>
T* DynArray<T>::getLast() const {
	return this->get(this->currentSize - 1);
}

template<typename T>
T* DynArray<T>::get(const int index) const {
	if (index < 0 or index >= this->currentSize) {
		throw nullptr;
	}
	return this->elements[index];
}

template<typename T>
void DynArray<T>::setFirst(T *newElement) {
	this->set(0, newElement);
}

template<typename T>
void DynArray<T>::setLast(T *newElement) {
	this->set(this->currentSize - 1, newElement);
}

template<typename T>
void DynArray<T>::set(const int index, T *newElement) {
	if (index < 0 or index >= this->currentSize) {
		throw nullptr;
	}
	this->elements[index] = newElement;
}

template<typename T>
void DynArray<T>::addFirst(T *newElement) {
	this->add(0, newElement);
}

template<typename T>
void DynArray<T>::addLast(T *newElement) {
	this->add(this->currentSize, newElement);
}

template<typename T>
void DynArray<T>::add(const int index, T *newElement) {
	if (index < 0 or index > this->currentSize) {
		throw nullptr;
	}
	if (this->currentSize + 1 > this->maxSize) {
		this->grow();
	}
	this->shiftRight(index);
	this->elements[index] = newElement;
	this->currentSize++;
}

template<typename T>
void DynArray<T>::removeFirst() {
	this->remove(0);
}

template<typename T>
void DynArray<T>::removeLast() {
	this->remove(this->currentSize - 1);
}

template<typename T>
void DynArray<T>::remove(const int index) {
	if (index < 0 or index > this->currentSize) {
		throw nullptr;
	}
	delete this->elements[index];
	this->elements[index] = nullptr;
	this->shiftLeft(index);
	if ((--this->currentSize) < this->maxSize * DynArray::shrinkAt) {
		this->shrink();
	}
}

template<typename T>
bool DynArray<T>::isEmpty() const {
	return this->currentSize == 0;
}

template<typename T>
void DynArray<T>::clear() {
	for (int i = 0; i < this->currentSize; i++) {
		delete this->elements[i];
	}
	this->currentSize = 0;
	this->maxSize = this->initialSize;
	this->elements[this->maxSize] = { };
}

template<typename T>
int DynArray<T>::size() const {
	return this->currentSize;
}

template<typename T>
void DynArray<T>::grow() {
	this->resizeElements(this->maxSize * DynArray::growFactor);
}
template<typename T>
void DynArray<T>::shrink() {
	this->resizeElements(this->currentSize);
}

template<typename T>
void DynArray<T>::resizeElements(const int newSize) {
//	T *newElements[newSize];
	T **newElements = new T*[newSize];
	for (int i = 0; i < this->currentSize; i++) {
		newElements[i] = this->elements[i];
	}
	delete[] this->elements;
	this->maxSize = newSize;
	this->elements = newElements;
}

template<typename T>
void DynArray<T>::shiftRight(const int from) {
	for (int i = this->currentSize - 1; i >= from; i--) {
		this->elements[i + 1] = this->elements[i];
	}
}
template<typename T>
void DynArray<T>::shiftLeft(const int from) {
	for (int i = from; i < this->currentSize; i++) {
		this->elements[i] = this->elements[i + 1];
	}
}

#endif /* INCLUDE_UTIL_DYNARRAY_CPP_ */
