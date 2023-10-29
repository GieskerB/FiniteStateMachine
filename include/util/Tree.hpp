#pragma once

#include "../../include/util/DynArray.hpp"

template<typename T>

class Tree {

private:

	/*
	 * Tree stores a pointer to the element which it will save
	 */
	T *element;

	/*
	 * Saving a reference to the parent
	 */
	Tree<T> *parent;

	/*
	 * Also saving all references to it children in a DynArray
	 */
	DynArray<Tree> children;

public:

	/*
	 *  Simple constructor-chaining:
	 */
	// Empty default constructor
	Tree() :
			Tree(nullptr, nullptr) {
	}
	// Only storing an element nothing more (maybe for the first element of a Tree)
	Tree(T *value) :
			Tree(value, nullptr) {
	}
	// Initializing a tree with a pointer to its parent
	Tree(Tree<T> *parent) :
			Tree(nullptr, parent) {
	}
	// All at once: parent, and value
	Tree(T *value, Tree<T> *parent) :
			element(value), parent(parent) {
		if (this->parent != nullptr) {
			this->parent->addChild(this);
		}
	}
	// Destructor
	~Tree() {
		delete this->element;
	}

	/*
	 * Simple getter Methods
	 */
	Tree<T>* getParent() const {
		return this->parent;
	}
	DynArray<Tree<T>> getChildren() const {
		return this->children;
	}
	Tree<T> getChild(int index) const {
		return this->children->get(index);
	}

	T* getElement() const {
		return this->element;
	}

	/*
	 * Simple getter Methods
	 */
	void setElement(T *newElement) {
		this->element = newElement;
	}
	void setChild(Tree<T> *child, const int index) {
		this->addChild->set(child, index);
	}
	void setChildren(const DynArray<Tree<T>> &child) {
		this->element = children;
	}

	/*
	 * Simple check Methods
	 */
	bool hasParent() const {
		return this->parent != nullptr;
	}
	bool isLeaf() const {
		return this->children->isEmpty();
	}

	/*
	 * Adding a new Child to the tree without inserting the same tree twice
	 */
	void addChild(Tree<T> *child) {
		this->children.addLast(child);
	}
};
