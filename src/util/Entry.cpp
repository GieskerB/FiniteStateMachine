#ifndef SRC_UTIL_ENTRY_CPP_
#define SRC_UTIL_ENTRY_CPP_

#include "../../include/util/Entry.hpp";

/*
 * Nested Construcors for all occasions
 */

// Empty
template <typename T>
Entry<T>::Entry() : Entry(nullptr) {}

// element only
template <typename T>
Entry<T>::Entry(const T &element) : Entry(element, nullptr) {}

// element and predecessor (for Stack)
template <typename T>
Entry<T>::Entry(const T &element, Entry<T> *predecessor)
    : Entry(element, predecessor, nullptr) {}

// element, predecessort and successor (for Queue and LinkedList)
template <typename T>
Entry<T>::Entry(const T &element, Entry<T> *predecessor, Entry<T> *successor)
    : element(element), pred(predecessor), succ(successor) {}

template <typename T>
const T &Entry<T>::getElement() {
  return this->element;
}

template <typename T>
Entry<T> *Entry<T>::getPredecessor() {
  return this->pred;
}

template <typename T>
Entry<T> *Entry<T>::getSuccessor() {
  return this->succ;
}

template <typename T>
bool Entry<T>::setPredecessor(Entry<T> *predecessor) {
  if (this == predecessor) {
    return false;
  }
  this->pred = predecessor;
  return true;
}

template <typename T>
bool Entry<T>::setSuccessor(Entry<T> *successor) {
  if (this == successor) {
    return false;
  }
  this->succ = successor;
  return true;
}

#endif /* SRC_UTIL_ENTRY_CPP_ */
