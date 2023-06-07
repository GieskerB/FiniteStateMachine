#ifndef INCLUDE_UTIL_QUEUE_HPP_
#define INCLUDE_UTIL_QUEUE_HPP_

#include "Entry.hpp"

template <typename T>
class Queue {
 private:
  Entry<T>*head, tail;

 public:
  Queue();

  void enqueue(const T& element);
  T& dequeue();
  T& head();

  bool isEmpty();
  void clear();
  int size();
};

#endif /* INCLUDE_UTIL_QUEUE_HPP_ */
