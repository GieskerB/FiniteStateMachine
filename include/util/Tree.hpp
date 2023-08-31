#ifndef INCLUDE_UTIL_TREE_HPP_
#define INCLUDE_UTIL_TREE_HPP_

#include "../../include/util/DynArray.hpp"

template<typename T>

class Tree {

private:
    T *value;
    Tree<T> *parent;
    DynArray<Knot> children;

public:
    Tree();
    Tree(T *value);
    Tree(Tree<T> *parent);
    Tree(T *value, Tree<T> *parent);

    Tree<T> *getParent();
    DynArray<Tree<T>> getChildren();
    DynArray<Tree<T>> getChild(int index);
    T *getValue();

    bool hasParent() const;
    bool isLeaf() const;

    void addChild(Tree<T> *child);
    void setValue(T *value);
};


#endif /* INCLUDE_UTIL_TREE_HPP_ */