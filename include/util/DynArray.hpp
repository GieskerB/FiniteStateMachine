#ifndef INCLUDE_UTIL_DYNARRAY_HPP_
#define INCLUDE_UTIL_DYNARRAY_HPP_

#include "Entry.hpp"

template<typename T>
class DynArray {
private:
	/*
	 * Steps at which the array will grow or shrink
	 */
	constexpr static float growFactor = 1.5f;
	constexpr static float shrinkAt = 0.25f;

	/*
	 * The initalSize defaults to 10 and is used if Array is cleared.
	 * Then it will be set to its initalSize
	 */
	const int initialSize;
	/*
	 * Always keeping track of the true number of Elements in the Array and
	 * the true size of it.
	 */
	int currentSize, maxSize;
	/*
	 * T** <=> *T elements[]: Its a array of pointer to Objects of type T
	 */
	T **elements;

public:

	/*
	 * Creating a new empty DynArray
	 */
	DynArray();
	/*
	 * Creating a new empty DynArray with set size
	 */
	DynArray(int preDefinedSize);
	/*
	 * Deleting the DynArray completely
	 */
	~DynArray();

	/*
	 * Simple way to get specific Elements from the DynArray (readOnly)
	 */
	T *getFirst() const;
	T *getLast() const;
	T *get(const int index) const;

	/*
	 * Setting / Overwriting an element in the DynArray
	 */
	void setFirst(T *newElement);
	void setLast(T *newElement);
	void set(const int index, T *newElement);

	/*
	 * Adding a new element to the DynArray at a predefined place
	 */
	void addFirst(T *newElement);
	void addLast(T *newElement);
	void add(const int index, T *newElement);

	/*
	 * Deleting an Element from the DynArray
	 */
	void removeFirst();
	void removeLast();
	void remove(const int index);

	/*
	 * Checks if DynArray has at least one element stored in it or not
	 */
	bool isEmpty() const;

	/*
	 * Deletes the content of the DynArray completely
	 */
	void clear();
	/*
	 * Returns the current number of elements
	 */
	int size() const;

private:

	void grow();
	void shrink();
	void resizeElements(const int newSize);
	void shiftRight(const int from);
	void shiftLeft(const int from);
};

#endif /* INCLUDE_UTIL_DYNARRAY_HPP_ */
