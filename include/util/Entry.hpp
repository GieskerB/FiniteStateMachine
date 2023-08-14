#ifndef INCLUDE_UTIL_ENTRY_HPP_
#define INCLUDE_UTIL_ENTRY_HPP_

/*
 * Generic Entry class for other ADTs like Stack Queue and LinkedList
 */

template<typename T>
class Entry {
private:

	/*
	 * Entry stores a pointer to the element which it will
	 */
	T *element;

	/*
	 * Also having a reference to the previous or next element, if necessary
	 */
	Entry<T> *pred, *succ;

public:
	/*
	 *  Simple constructor-chaining:
	 */
	// Empty default constructor
	Entry();
	// Only storing an element nothing more (maybe for the first element in a ADT)
	Entry(T *element);
	// Element and predecessor: e.g. Stack
	Entry(T *element, Entry<T> *predecessor);
	// All at once: e.g. LinkedList
	Entry(T *element, Entry<T> *predecessor, Entry<T> *successor);
	// Destructor
	~Entry();

	/*
	 * returns stored element in this Entry
	 */
	T* getElement() const;

	/*
	 * Check functions to see if the is a next or previous element
	 */
	bool hasPredecessor() const;
	bool hasSuccessor() const;

	/*
	 * Getter for the neighboring Elements.
	 * Use hasPredecessor() or hasSuccessor() first
	 */
	Entry<T>* getPredecessor() const;
	Entry<T>* getSuccessor() const;

	/*
	 * Getter for the neighboring Elements.
	 * returns true if neighbors was successfully placed
	 */
	bool setPredecessor(Entry<T> *predecessor);
	bool setSuccessor(Entry<T> *successor);
};

#endif /* INCLUDE_UTIL_ENTRY_HPP_ */
