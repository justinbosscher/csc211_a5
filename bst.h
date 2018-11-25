#include <vector>

#ifndef _bst_h
#define _bst_h

template <typename T> class BST {
public: 

	/*
	Default constructor.
	*/
	BST();

	/*
	Destructor.
	Traverses any subtrees.
	*/
	~BST();

	/*
	Single-instance constructor.
	Given some content of type T,
	creates a new BST node with its content field populated.
	Sets left and right children to nullptr.
	*/
	BST(T content);

	/*
	Vector constructor.
	Given a vector<T> and a comparator function, 
	inserts every element of the vector into a BST.
	The comparator is used to determine a "less-than" relationship.
	The BST object returned by this constructor is the
	root of the binary search tree.
	*/
	BST(std::vector<T> contents, bool comparator(T&, T&));

	/* 
	getter for the content field
	*/
	T getContent();

	/* 
	Performs a binary search on the BST, given a comparator function.
	Returns the content of the BST node if a match is found.
	Throws a std::runtime_error if no matching item can be found.
	This uses a notion of equality based on the "less-than" comparator:
	(a == b) if and only if !(a<b) && !(b<a)
	*/
	T find(T query, bool comparator(T&, T&));

	/* 
	Inserts element x, of type T, into the BST.
	This preserves the BST invariant: 
	a left child is always less than its parent, while
	a right child is always not less than its parent.
	This relies on the "less-than" comparator.
	*/
	void insert(T x, bool comparator(T&, T&));



private:
	T content;
	BST<T> *left, *right;
};


#endif