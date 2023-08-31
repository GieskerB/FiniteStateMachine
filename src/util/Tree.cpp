#ifndef INCLUDE_UTIL_TREE_CPP_
#define INCLUDE_UTIL_TREE_CPP_

#include "../../include/util/Tree.hpp"

template<typename T>
Tree<T>::Tree() : Tree(nullptr, nullptr) {}

template<typename T>
Tree<T>::Tree(T *value) : Tree(value, nullptr) {}

template<typename T>
Tree<T>::Tree(Tree<T> *parent) : Tree(nullptr, parent) {}

template<typename T>
Tree<T>::Tree(T *value, Tree<T> *parent) {
    this->value = value;
    this->parent = parent;
    if (parent != nullptr) {
        parent->addChild(this);
    }
}
template<typename T>
Tree<T> *Tree<T>::getParent() {
    return parent;
}

template<typename T>
DynArray<Tree<T> > Tree<T>::getChildren() {
    return children;
}
template<typename T>
DynArray<Tree<T> > Tree<T>::getChild(int index) {
    return children->get(index);
}


template<typename T>
T *Tree<T>::getValue() {
    return value;
}

template<typename T>
bool Tree<T>::hasParent() const {
    return parent != nullptr;
}

template<typename T>
bool Tree<T>::isLeaf() const {
    return children->isEmpty();
}

template<typename T>
void Tree<T>::addChild(Tree<T> *child) {
    children.addLast(child);
}

template<typename T>
void Tree<T>::setValue(T *value) {
    this->value = value;
}



#endif /* INCLUDE_UTIL_TREE_CPP_ */