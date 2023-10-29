#pragma once

#include <stdexcept>
#include <cstddef>
#include <string>

namespace std {
class invalid_argument;
} /* namespace std */

namespace std {
struct forward_iterator_tag;
} /* namespace std */

template<typename T>
class DynArray {
private:
	/*
	 * Steps at which the array will grow or shrink
	 */
	constexpr static float GROW_FACTOR = 1.5f;
	constexpr static float SHRINK_AT = 0.25f;
	constexpr static int DEFAULT_SIZE = 10;

	/*
	 * The initialSize defaults to 10 and is used if Array is cleared.
	 * Then it will be set to its initialSize
	 */
	const int initialSize;
	/*
	 * Always keeping track of the true number of Elements in the Array and
	 * the true size of it.
	 */
	int currentSize, maxSize;
	/*
	 * T** <=> T* elements[]: It's an array of pointer to Objects of type T
	 */
	T **elements;

	void grow() {
		this->resizeElements(this->maxSize * DynArray::GROW_FACTOR);
	}
	void shrink() {
		this->resizeElements(this->currentSize);
	}
	void resizeElements(const int newSize) {
		//	T *newElements[newSize];
		T **newElements = new T*[newSize];
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
			DynArray(DEFAULT_SIZE) {
	}
	/*
	 * Creating a new empty DynArray with set size
	 */
	DynArray(int preDefinedSize) :
			initialSize(preDefinedSize), currentSize(0), maxSize(preDefinedSize) {
		this->elements = new T*[this->maxSize];
	}

   // DynArray<T>(const DynArray<T> &dynArray ) = delete;
   // DynArray<T> &operator= (const DynArray<T> &dynArray) = delete;

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
		using value_type = T*;
		using pointer = value_type*;
		using reference = value_type&;

	private:

		pointer m_ptr;

	public:
		Iterator(pointer ptr) :
				m_ptr(ptr) {
		}

		reference operator*() const {
			return *m_ptr;
		}
		pointer operator->() {
			return m_ptr;
		}

		// Prefix increment
		Iterator& operator++() {
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

	/*
	 * Iterator specific methods:
	 */
	DynArray<T>::Iterator begin() {
		return DynArray<T>::Iterator(&this->elements[0]);
	}
	DynArray<T>::Iterator end() {
		// Out of bounce if necessary here
		return DynArray<T>::Iterator(&this->elements[this->currentSize]);
	}

	/*
	 * Simple way to get specific Elements from the DynArray (readOnly)
	 */
	T* getFirst() const {
		return this->get(0);
	}
	T* getLast() const {
		return this->get(this->currentSize - 1);
	}
	T* get(const int index) const {
		if (index < 0 or index >= this->currentSize) {
			throw std::invalid_argument(
					std::to_string(index) + " is out of bounce of size 0 to "
							+ std::to_string(this->currentSize));
		}
		return this->elements[index];
	}

	/*
	 * Setting / Overwriting an element in the DynArray
	 */
	void setFirst(T *newElement) {
		this->set(newElement, 0);
	}
	void setFirst(const T &newElement) {
		this->setFirst(new T(newElement));
	}
	void setLast(T *newElement) {
		this->set(newElement, std::max(this->currentSize - 1, 0));
	}
	void setLast(const T &newElement) {
		this->setLast(new T(newElement));
	}
	void set(T *newElement, const int index) {
		if (index < 0 or index >= this->currentSize) {
			throw std::invalid_argument(
					std::to_string(index) + " is out of bounce of size 0 to "
							+ std::to_string(this->currentSize));
		}
		this->elements[index] = newElement;
	}
	void set(const T &newElement, const int index) {
		this->set(new T(newElement), index);
	}

	/*
	 * Adding a new element to the DynArray at a predefined place
	 */

	void addFirst(T *newElement) {
		this->add(newElement, 0);
	}
	void addFirst(const T &newElement) {
		this->addFirst(new T(newElement));
	}
	void addLast(T *newElement) {
		this->add(newElement, this->currentSize);
	}
	void addLast(const T &newElement) {
		this->addLast(new T(newElement));
	}
	void add(T *newElement, const int index) {
		if (index < 0 or index > this->currentSize) {
			throw std::invalid_argument(
					std::to_string(index) + " is out of bounce of size 0 to "
							+ std::to_string(this->currentSize));
		}
		if (this->currentSize + 1 > this->maxSize) {
			this->grow();
		}
		this->shiftRight(index);
		this->elements[index] = newElement;
		this->currentSize++;
	}
	void add(const T &newElement, const int index) {
		this->add(new T(newElement), index);
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
		delete this->elements[index];
		this->elements[index] = nullptr;
		this->shiftLeft(index);
		if ((--this->currentSize) < this->maxSize * DynArray::SHRINK_AT) {
			this->shrink();
		}
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
		for (int i = 0; i < this->currentSize; i++) {
			delete this->elements[i];
		}
		this->currentSize = 0;
		this->maxSize = this->initialSize;
		this->elements[this->maxSize] = { };
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

};
