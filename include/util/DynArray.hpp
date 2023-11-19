#pragma once

#include <stdexcept>
#include <cstddef>
#include <string>

#include <memory>

class invalid_argument;
struct forward_iterator_tag;

template<typename T>
class DynArray {
private:
	/*
	 * Steps at which the array will grow or shrink
	 */
	constexpr static float GROW_FACTOR = 1.5f;
	constexpr static float SHRINK_AT = 0.25f;
	constexpr static unsigned int DEFAULT_SIZE = 10;

	/*
	 * The initialSize defaults to 10 and is used if Array is cleared.
	 * Then it will be set to its initialSize
	 */
	unsigned const int initialSize;

	/*
	 * Always keeping track of the true number of Elements in the Array and
	 * the true size of it.
	 */
	unsigned int currentSize, maxSize;
	/*
	 * T** <=> T* elements[]: It's an array of pointer to Objects of type T
	 */

	std::shared_ptr<T> *elements;

	void grow() {
		this->resizeElements(this->maxSize * DynArray::GROW_FACTOR);
	}
	void shrink() {
		this->resizeElements(this->currentSize);
	}
	void resizeElements(const int newSize) {
		std::shared_ptr<T> *newElements = new std::shared_ptr<T>[newSize];
		for (int i = 0; i < this->currentSize; i++) {
			newElements[i] = this->elements[i];
		}
		delete[] this->elements;
		this->maxSize = newSize;
		this->elements = newElements;
	}
	void shiftRight(const int from) {
		for (int i = this->currentSize - 1; i >= from; i--) {
			this->elements[i + 1] = this->elements[i];
		}
	}
	void shiftLeft(const int from) {
		for (int i = from; i < this->currentSize; i++) {
			this->elements[i] = this->elements[i + 1];
		}
	}

public:

	/*
	 * Creating a new empty DynArray
	 */
	DynArray() :
		DynArray(DEFAULT_SIZE) {}
	/*
	 * Creating a new empty DynArray with set size
	 */
	DynArray(int preDefinedSize) :
		initialSize(preDefinedSize), currentSize(0), maxSize(preDefinedSize) {
		this->elements = new std::shared_ptr<T>[preDefinedSize];
	}

	/*
	 * Deleting the DynArray completely
	 */
	~DynArray() {
		this->clear();
		delete[] this->elements;
	}

	class Iterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = value_type *;
		using reference = value_type &;

	private:

		pointer m_ptr;

	public:
		Iterator(pointer ptr) :
			m_ptr(ptr) {}

		reference operator*() const {
			return *m_ptr;
		}
		pointer operator->() {
			return m_ptr;
		}

		// Prefix increment
		Iterator &operator++() {
			m_ptr++;
			return *this;
		}

		// Postfix increment
		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		bool operator==(const Iterator &other) {
			return other.m_ptr == this->m_ptr;
		}
		bool operator!=(const Iterator &other) {
			return other.m_ptr != this->m_ptr;
		}

	};


	DynArray<T>::Iterator begin() {
		return DynArray<T>::Iterator(this->elements[0]);
	}
	DynArray<T>::Iterator end() {
		// Out of bounce if necessary here
		// return DynArray<T>::Iterator(this->elements[this->currentSize - 1].get());
		// return DynArray<T>::Iterator(this->elements + (this->currentSize * sizeof(std::shared_ptr<T>)));
		return DynArray<T>::Iterator(this->elements + (this->currentSize * sizeof(std::shared_ptr<T>)));
	}


	/*
	 * Simple way to get specific Elements from the DynArray (readOnly)
	 */
	T getFirst() const {
		return this->get(0);
	}
	T getLast() const {
		return this->get(this->currentSize - 1);
	}
	T get(const int index) const {
		if (index < 0 or index >= this->currentSize) {
			throw std::invalid_argument(
				std::to_string(index) + "  get is out of bounce of size 0 to "
				+ std::to_string(this->currentSize));
		}
		return *this->elements[index];
	}

	/*
	 * Setting / Overwriting an element in the DynArray
	 */

	void setFirst(const T &newElement) {
		this->set(newElement, 0);
	}

	void setLast(const T &newElement) {
		this->set(newElement, this->currentSize - 1);
	}
	void set(const T &newElement, const int index) {
		if (index < 0 or index >= this->currentSize) {
			throw std::invalid_argument(
				std::to_string(index) + " set is out of bounce of size 0 to "
				+ std::to_string(this->currentSize));
		}
		this->elements[index] = std::make_shared<T>(newElement);
	}

	/*
	 * Adding a new element to the DynArray at a predefined place
	 */

	void addFirst(const T &newElement) {
		this->add(newElement, 0);
	}

	void addLast(const T &newElement) {
		this->add(newElement, this->currentSize);
	}

	void add(const T &newElement, const int index) {
		if (index < 0 or index > this->currentSize) {
			throw std::invalid_argument(
				std::to_string(index) + " is out of bounce of size 0 to "
				+ std::to_string(this->currentSize));
		}
		if (this->currentSize + 1 > this->maxSize) {
			this->grow();
		}
		this->shiftRight(index);
		this->elements[index] = std::make_shared<T>(newElement);
		this->currentSize++;
	}
	/*
	 * Deleting an Element from the DynArray
	 */
	void removeFirst() {
		this->remove(0);
	}
	void removeLast() {
		this->remove(this->currentSize - 1);
	}
	void remove(const int index) {
		if (index < 0 or index > this->currentSize) {
			throw std::invalid_argument(
				std::to_string(index) + " is out of bounce of size 0 to "
				+ std::to_string(this->currentSize));
		}
		this->shiftLeft(index);
		if (this->currentSize - 1 < this->maxSize * DynArray::SHRINK_AT) {
			std::cout << "i was here";
			this->shrink();
		}
		currentSize--;
	}

	/*
	 * Checks if DynArray has at least one element stored in it or not
	 */
	bool isEmpty() const {
		return this->currentSize == 0;
	}

	/*
	 * Deletes the content of the DynArray completely
	 */
	void clear() {
		delete[] this->elements;
		this->elements = new std::shared_ptr<T>[this->initialSize];
		this->currentSize = 0;
		this->maxSize = this->initialSize;
	}
	/*
	 * Returns the current number of elements
	 */
	int size() const {
		return this->currentSize;
	}

	/*
	 * Returns the index of an object if it's in this list.
	 * Otherwise, return -1
	 */
	int indexOf(const T &element) const {
		for (int i = 0; i < this->currentSize; i++) {
			if (*this->elements[i] == element) {
				return i;
			}
		}
		return -1;
	}

	std::string toString() {
		int size = this->size();

		std::string outp = "{";

		for (int i = 0; i < size - 1; i++) {
			outp += std::to_string(this->get(i)) + ", ";
		}
		if (this->isEmpty()) {
			outp += "}";
		}
		else {
			outp += std::to_string(this->get(size - 1)) + "}";
		}

		return outp;
	}

};
