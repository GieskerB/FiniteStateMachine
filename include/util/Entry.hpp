#pragma once

/*
 * Generic Entry class for other ADTs like Stack Queue and LinkedList
 */

template<typename T>
class Entry {
private:

	/*
	 * Entry stores a pointer to the element which it will save
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
	Entry() :
			Entry(nullptr) {
	}
	// Only storing an element nothing more (maybe for the first element in a ADT)
	Entry(T *element) :
			Entry(element, nullptr) {
	}
	// Element and predecessor: e.g. Stack
	Entry(T *element, Entry<T> *predecessor) :
			Entry(element, predecessor, nullptr) {
	}
	// All at once: e.g. LinkedList
	Entry(T *element, Entry<T> *predecessor, Entry<T> *successor) :
			element(element), pred(predecessor), succ(successor) {
	}
	// Destructor
	~Entry() {
		delete this->element;
	}

	/*
	 * returns stored element in this Entry
	 */
	T* getElement() const {
		return this->element;
	}

	/*
	 * Check functions
	 */
	bool hasPredecessor() const;
	bool hasSuccessor() const;
	/*
	 * Getter for the neighboring Elements.
	 * Use hasPredecessor() or hasSuccessor() first
	 */
	Entry<T>* getPredecessor() const {
		return this->pred;
	}
	Entry<T>* getSuccessor() const {
		return this->succ;
	}

	/*
	 * Getter for the neighboring Elements.
	 * returns true if neighbors was successfully placed
	 */
	bool setPredecessor(Entry<T> *predecessor) {
		if (this == predecessor) {
			return false;
		}
		this->pred = predecessor;
		return true;
	}
	bool setSuccessor(Entry<T> *successor) {
		if (this == successor) {
			return false;
		}
		this->succ = successor;
		return true;
	}
};

template<typename T>
bool Entry<T>::hasSuccessor() const {
    return !this->succ == nullptr;
}

template<typename T>
bool Entry<T>::hasPredecessor() const {
    return !this->pred == nullptr;
}
