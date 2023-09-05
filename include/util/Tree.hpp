#ifndef INCLUDE_UTIL_TREE_HPP_
#define INCLUDE_UTIL_TREE_HPP_

#include "../../include/util/DynArray.hpp"

template<typename T>

class Tree {

private:

    /*
     * Tree stores a pointer to the element which it will save
     */
    T *value;

    /*
     * Saving a reference to the parent
     */
    Tree<T> *parent;

    /*
     * Also saving all references to it childs in a DynArray
     */
    DynArray<Tree> children;

public:

    /*
     *  Simple constructor-chaining:
     */
     // Empty default constructor
    Tree();
    // Only storing an element nothing more (maybe for the first element of a Tree)
    Tree(T *value);
    // Initializing a tree witha pointer to its parent
    Tree(Tree<T> *parent);
    // All at once: parent, and value
    Tree(T *value, Tree<T> *parent);
    // Destructor
    ~Tree();

    /*
     * Simple getter Methods
     */
    Tree<T> *getParent();
    DynArray<Tree<T>> getChildren();
    Tree<T> getChild(int index);
    T *getValue();

    /*
     * Simple getter Methods
     */
    void setValue(T *value);

    /*
     * Simple check Methods
     */
    bool hasParent() const;
    bool isLeaf() const;

    /*
     * Adding a new Child to the tree without inserting the same tree twice
     */
    void addChild(Tree<T> *child);
};


#endif /* INCLUDE_UTIL_TREE_HPP_ */