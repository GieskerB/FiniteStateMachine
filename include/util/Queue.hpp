#ifndef INCLUDE_UTIL_QUEUE_HPP_
#define INCLUDE_UTIL_QUEUE_HPP_

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
	Queue();

	/*
	 * Deleting the Queue completely
	 */
	~Queue();

	/*
	 * Adding a new element into the back of the Queue
	 */
	void enqueue(T *element);
	void enqueue(const T &element);

	/*
	 * Removing the first element from the Queue
	 */
	T* dequeue();

	/*
	 * simply looking at the first element of the Queue without removing it
	 */
	T* peak() const;

	/*
	 * Checks if Queue has at least one element stored in it or not
	 */
	bool isEmpty() const;

	/*
	 * Deletes the content of the Queue completely
	 */
	void clear();
};

#endif /* INCLUDE_UTIL_QUEUE_HPP_ */
