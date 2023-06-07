#ifndef INCLUDE_UTIL_STACK_HPP_
#define INCLUDE_UTIL_STACK_HPP_

#include "Entry.hpp"

template <typename T>
class Stack {
 private:
  Entry<T>* top;

 public:
  Stack();

  void push(const T& element);
  T& pop();

  bool isEmpty();
};

#endif /* INCLUDE_UTIL_STACK_HPP_ */
