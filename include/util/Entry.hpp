#ifndef INCLUDE_UTIL_ENTRY_HPP_
#define INCLUDE_UTIL_ENTRY_HPP_

template<typename T>
class Entry {
private:

	const T *element;
	Entry *pred, *succ;

public:

	Entry();
	Entry(const T *element);
	Entry(const T *element, Entry *predecessor);
	Entry(const T *element, Entry *predecessor, Entry *successor);

	const T* getElement();

	Entry* getPredecessor();
	Entry* getSuccessor();

	bool setPredecessor(Entry *predecessor);
	bool setSuccessor(Entry *successor);
};

#endif /* INCLUDE_UTIL_ENTRY_HPP_ */
