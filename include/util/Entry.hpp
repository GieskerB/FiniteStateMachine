#ifndef INCLUDE_UTIL_ENTRY_HPP_
#define INCLUDE_UTIL_ENTRY_HPP_

/*
 * Generic Entry class for other ADTs like Stack Queue and LinkedList
 */

template<typename T>
class Entry {
private:
	T *element;
	Entry<T> *pred, *succ;

public:
	Entry();
	Entry(T *element);
	Entry(T *element, Entry<T> *predecessor);
	Entry(T *element, Entry<T> *predecessor, Entry<T> *successor);
	~Entry();

	T* getElement();

	bool hasPredecessor();
	bool hasSuccessor();

	Entry<T>* getPredecessor();
	Entry<T>* getSuccessor();

	bool setPredecessor(Entry<T> *predecessor);
	bool setSuccessor(Entry<T> *successor);
};

#endif /* INCLUDE_UTIL_ENTRY_HPP_ */
