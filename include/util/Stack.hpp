#pragma once

#include "Entry.hpp"

/*
   This is a versatile generic Stack class, a fundamental data structure that adheres to the Last-In-First-Out (LIFO) principle. It emulates a stack of items, where the last item placed is the first to be removed.

   Key Features:
   - Generics: This Stack class is template-based, meaning it can work with a wide range of data types, making it highly flexible for various applications.

   Basic Operations:
   - 'push': Adds an m_element to the m_top of the stack.
   - 'pop': Removes and returns the m_top m_element from the stack.
   - 'is_empty': Checks whether the stack is empty.
   - 'clear': Removes all elements from the stack, effectively emptying the stack.

   How to Use:
   - To employ this Stack, declare an instance with the desired data type (e.g., Stack<int> for integers) and perform 'push', 'pop', and 'is_empty' operations as needed.
*/
template<typename T>
class Stack {
private:

    // Usage of a shared pointer to make memory management easier.
    // Top stores a pointer to the m_top most m_element of the stack.
    // is a null pointer by default
    std::shared_ptr<Entry<T>> m_top;

public:

    // Default constructor, because no need for initialization of any variables.
    Stack() = default;

    // When deleting a stack first clear its content.
    ~Stack() {
        clear();
    }

    // Pushes a new m_element to the stack.
    void push(const T &element) {
        if (is_empty()) {
            m_top = std::make_shared<Entry<T>>(element);
        } else {
            // If it's not empty connect the new m_top m_element to the old one.
            m_top = std::make_shared<Entry<T>>(element, *m_top);
        }
    }

    // Removes the m_top most m_element from the stack and returns it.
    T pop() {
        if (is_empty()) {
            // In case of illegal usage of pop throw an exception.
            throw std::runtime_error("unable to pop from empty stack");
        }
        T temp_element = m_top->get_element();
        m_top = std::move(m_top->get_next_entry());
        return temp_element;
    }

    // Only looks at the m_top most m_element without removing it from the stack.
    T peek() const {
        if (is_empty()) {
            throw std::runtime_error("unable to peak into empty stack");
        }
        return m_top->get_element();
    }

    // Check if the stack has no elements stored.
    [[nodiscard]] bool is_empty() const {
        return m_top.get() == nullptr;
    }

    // Removes all the elements from the stack.
    void clear() {
        if (is_empty()) {
            return;
        }
        m_top.reset();
    }
};
