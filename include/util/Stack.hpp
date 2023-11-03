#pragma once

#include "Entry.hpp"

/*
   This is a versatile generic Stack class, a fundamental data structure that adheres to the Last-In-First-Out (LIFO) principle. It emulates a stack of items, where the last item placed is the first to be removed.

   Key Features:
   - Generics: This Stack class is template-based, meaning it can work with a wide range of data types, making it highly flexible for various applications.

   Basic Operations:
   - 'push': Adds an element to the top of the stack.
   - 'pop': Removes and returns the top element from the stack.
   - 'isEmpty': Checks whether the stack is empty.
   - 'clear': Removes all elements from the stack, effectively emptying the stack.

   How to Use:
   - To employ this Stack, declare an instance with the desired data type (e.g., Stack<int> for integers) and perform 'push', 'pop', and 'isEmpty' operations as needed.
*/
template<typename T>
class Stack {
private:

    // Usage of a shared pointer to make memory management easier.
    // Top stores a pointer to the top most element of the stack.
    // is a null pointer by default
    std::shared_ptr<Entry<T>> top;

public:

    // Default constructor, because no need for initialization of any variables.
    Stack() = default;

    // When deleting a stack first clear its content.
    ~Stack() {
        this->clear();
    }

    // Pushes a new element to the stack.
    void push(const T &element) {
        if (this->isEmpty()) {
            Entry<T> newTopEntry(element);
            this->top = std::make_shared<Entry<T>>(newTopEntry);
        } else {
            // If it's not empty connect the new top element to the old one.
            Entry<T> newTopEntry(element, *this->top);
            this->top = std::make_shared<Entry<T>>(newTopEntry);
        }
    }

    // Removes the top most element from the stack and returns it.
    T pop() {
        if (this->isEmpty()) {
            // In case of illegal usage of pop throw an exception.
            throw std::runtime_error("unable to pop from empty stack");
        }
        T element = this->top->getElement();
        this->top = this->top->getNextEntry();
        return element;
    }

    // Only looks at the top most element without removing it from the stack.
    T peek() const {
        if (this->isEmpty()) {
            throw std::runtime_error("unable to peak into empty stack");
        }
        return this->top->getElement();
    }

    // Check if the stack has no elements stored.
    bool isEmpty() const {
        return this->top.get() == nullptr;
    }

    // Removes all the elements from the stack.
    void clear() {
        if (this->isEmpty()) {
            return;
        }
        this->top.reset();
    }
};
