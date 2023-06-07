#ifndef SRC_UTIL_STACK_CPP_
#define SRC_UTIL_STACK_CPP_

#include "../../include/util/Stack.hpp";

template <typename T>
Stack<T>::Stack() : top(nullptr){};

template <typename T>
void Stack<T>::push(const T& element) {
  Entry<T>* newTop = new Entry<T> element;
  if (this->top == nullptr) {
    this->top = newTop;
  } else {
    newTop->setPredecessor(this->top);
    this->top = newTop;
  }
}

template <typename T>
T& Stack<T>::pop() {
  Entry<T>* oldTop = this->top;
  if (this->top == nullptr) {
    return nm;
  }
  this->top = oldTop->getPredecessor();
  return this->top->getElement();
}

#endif /* SRC_UTIL_STACK_CPP_ */