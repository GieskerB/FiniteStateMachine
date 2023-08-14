#ifndef INCLUDE_UTIL_STACK_HPP_
#define INCLUDE_UTIL_STACK_HPP_

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
	Stack();

	/*
	 * Deleting the Stack completely
	 */
	~Stack();

	/*
	 * Adding a new element onto the Stack
	 */
	void push(T *element);
	void push(const T &element);

	/*
	 * Removing the top most element from the Stack
	 */
	T* pop();

	/*
	 * simply looking at the top most element of the Stack without removing it
	 */
	T* peak() const;

	/*
	 * Checks if Stack has at least one element stored in it or not
	 */
	bool isEmpty() const;

	/*
	 * Deletes the content of the Stack completely
	 */
	void clear();
};

#endif /* INCLUDE_UTIL_STACK_HPP_ */
