#ifndef SRC_UTIL_QUEUE_CPP_
#define SRC_UTIL_QUEUE_CPP_

#include "../../include/util/Queue.hpp";

template <typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr){};

template <typename T>
void Queue<T>::enqueue(const T& element) {
  Entry<T>* newTail = new Entry<E> element;
  if (this->head == nullptr) {
    this->head = newTail;
    this->tail = this->head;
  } else {
    this->tail.setSuccessor(newTail);
    this->tail = newTail;
  }
}

template <typename T>
T& Queue<T>::dequeue() {}

#endif /* SRC_UTIL_QUEUE_CPP_ */