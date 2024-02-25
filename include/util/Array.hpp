#pragma once

#include <stdexcept>
#include <cstddef>
#include <string>

#include <memory>

class invalid_argument;

struct forward_iterator_tag;

template<typename T>
class Array {
private:
    /*
     * Steps at which the Array will grow or shrink
     */
    constexpr static float GROW_FACTOR = 1.5f;
    constexpr static float SHRINK_AT = 0.25f;
    constexpr static unsigned int DEFAULT_SIZE = 10;

    /*
     * The initial_size defaults to 10 and is used if Array is cleared.
     * Then it will be set to its initial_size
     */
    unsigned int initial_size;

    /*
     * Always keeping track of the true number of Elements in the Array and
     * the true size of it.
     */
    unsigned int current_size, max_size;


    T *elements;


    enum Origin {
        GET, SET, REMOVE, ADD
    };

    void grow() {
        this->resize_elements(this->max_size * Array::GROW_FACTOR);
    }

    void shrink() {
        this->resize_elements(this->current_size);
    }

    void resize_elements(const int newSize) {
        T *newElements = new T[newSize];
        for (int i = 0; i < this->current_size; i++) {
            newElements[i] = this->elements[i];
        }
        delete[] this->elements;
        this->max_size = newSize;
        this->elements = newElements;
    }

    void shiftRight(const int from) {
        for (int i = this->current_size - 1; i >= from; i--) {
            this->elements[i + 1] = this->elements[i];
        }
    }

    void shiftLeft(const int from) {
        for (int i = from; i < this->current_size; i++) {
            this->elements[i] = this->elements[i + 1];
        }
    }

    void out_of_bounce_check(int index, Origin origin) const {
        if (index < 0 or index >= this->current_size) {
            std::string method_name;
            switch (origin) {
                case Origin::GET:
                    method_name = "get";
                    break;
                case Origin::SET:
                    method_name = "set";
                    break;
                case Origin::ADD:
                    method_name = "add";
                    break;
                case Origin::REMOVE:
                    method_name = "remove";
                    break;
            }
            throw std::invalid_argument(
                    std::to_string(index) + " in method [" + method_name + "] is out of bounce of size 0 to "
                    + std::to_string(this->current_size));
        }
    }


public:

    /*
     * Creating a new empty Array
     */
    Array() :
            Array(DEFAULT_SIZE) {}

    /*
     * Creating a new empty Array with set size
     */
    explicit Array(int preDefinedSize) :
            initial_size(preDefinedSize), current_size(0), max_size(preDefinedSize) {
        this->elements = new T[preDefinedSize]{};
    }

    /*
     * Deleting the Array completely
     */
    ~Array() {
        delete[] this->elements;
    }

    class Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type *;
        using reference = value_type &;

    private:

        pointer m_ptr;

    public:
        explicit Iterator(pointer ptr) :
                m_ptr(ptr) {}

        reference operator*() const {
            return *m_ptr;
        }

        pointer operator->() {
            return m_ptr;
        }

        // Prefix increment
        Iterator &operator++() {
            m_ptr++;
            return *this;
        }

        // Postfix increment
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator &other) {
            return other.m_ptr == this->m_ptr;
        }

        bool operator!=(const Iterator &other) {
            return other.m_ptr != this->m_ptr;
        }

    };


    Array<T>::Iterator begin() {
        return Array<T>::Iterator(this->elements[0]);
    }

    Array<T>::Iterator end() {
        // Out of bounce if necessary here
        return Array<T>::Iterator(this->elements[current_size]);
    }


    /*
     * Simple way to get specific Elements from the Array (readOnly)
     */
    T getFirst() const {
        return this->get(0);
    }

    T getLast() const {
        return this->get(this->current_size - 1);
    }

    T get(int index) const {
        this->out_of_bounce_check(index,Origin::GET);
        return this->elements[index];
    }

    T &operator[](int index) {
        this->out_of_bounce_check(index,Origin::GET);
        return &this->elements[index];
    }

    T operator[](int index) const {
        this->out_of_bounce_check(index,Origin::GET);
        return this->elements[index];
    }

    /*
     * Setting / Overwriting an element in the Array
     */

    void setFirst(const T &newElement) {
        this->set(newElement, 0);
    }

    void setLast(const T &newElement) {
        this->set(newElement, this->current_size - 1);
    }

    void set(const T &newElement, const int index) {
        this->out_of_bounce_check(index,Origin::SET);
        this->elements[index] = newElement;
    }

    /*
     * Adding a new element to the Array at a predefined place
     */

    void addFirst(const T &newElement) {
        this->add(newElement, 0);
    }

    void addLast(const T &newElement) {
        this->add(newElement, this->current_size);
    }

    void add(const T &newElement, const int index) {
        this->out_of_bounce_check(index,Origin::ADD);
        if (this->current_size + 1 > this->max_size) {
            this->grow();
        }
        this->shiftRight(index);
        this->elements[index] = newElement;
        this->current_size++;
    }

    /*
     * Deleting an Element from the Array
     */
    void removeFirst() {
        this->remove(0);
    }

    void removeLast() {
        this->remove(this->current_size - 1);
    }

    void remove(const int index) {
        this->out_of_bounce_check(index,Origin::REMOVE);
        this->shiftLeft(index);
        if (this->current_size - 1 < this->max_size * Array::SHRINK_AT) {
            this->shrink();
        }
        current_size--;
    }

    /*
     * Checks if Array has at least one element stored in it or not
     */
    [[nodiscard]] bool isEmpty() const {
        return this->current_size == 0;
    }

    /*
     * Deletes the content of the Array completely
     */
    void clear() {
        delete[] this->elements;
        this->elements = new T[this->initial_size];
        this->current_size = 0;
        this->max_size = this->initial_size;
    }

    /*
     * Returns the current number of elements
     */
    [[nodiscard]] int size() const {
        return this->current_size;
    }

    /*
     * Returns the index of an object if it's in this list.
     * Otherwise, return -1
     */
    int indexOf(const T &element) const {
        for (int i = 0; i < this->current_size; i++) {
            if (*this->elements[i] == element) {
                return i;
            }
        }
        return -1;
    }

    std::string toString() {
        int size = this->size();

        std::string outp = "{";

        for (int i = 0; i < size - 1; i++) {
            outp += std::to_string(this->get(i)) + ", ";
        }
        if (this->isEmpty()) {
            outp += "}";
        } else {
            outp += std::to_string(this->get(size - 1)) + "}";
        }

        return outp;
    }

};
