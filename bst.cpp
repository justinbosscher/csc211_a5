#include "bst.h"
#include <string>
#include "dna.h"
#include <stdexcept>
#include <iostream>

template <typename T>
BST<T>::BST() {
	/*
	slightly ugly: because we don't have a parameter of type T,
	we have to call new and dereference the pointer.
	Other constructors should NOT do this.
	*/
	this->content = *(new T);
	this->left = nullptr;
	this->right = nullptr;
} // end BST constructor

/*
Deconstructor
*/
template <typename T>
BST<T>::~BST() {
	// Recursively call delete on left and right subtrees.
	if (this->left != nullptr) delete(this->left);
	if (this->right != nullptr) delete(this->right);
} // end BST deconstructor


/*
Single-instance constructor.
Given some content of type T,
creates a new BST node with its content field populated.
Sets left and right children to nullptr.
*/
template <typename T>
BST<T>::BST(T content) {
	this->content = content;
	this->left = nullptr;
	this->right = nullptr;
} // end BST constructor that takes content


/*
Vector constructor.
Given a vector<T> and a comparator function,
inserts every element of the vector into a BST.
The comparator is used to determine a "less-than" relationship.
The BST object returned by this constructor is the
root of the binary search tree.
*/
template <typename T>
BST<T>::BST(std::vector<T> contents, bool comparator(T&, T&)) {
	// sets content of first node to vector[0] and right and left pointers to null
	this->content = contents[0];
	this->left = nullptr;
	this->right = nullptr;

	/* for loop to iterate through contents of vector; initialize i=1 because v[0]
	will be root
	*/
	for(unsigned int i = 1; i < contents.size(); i++){
			this->insert(contents[i], comparator);
	} // end for loop
} // end BST constructor with vector and comparator


/*
getter for the content field
*/
template <typename T>
T BST <T>::getContent() {
	// simple accessor returns content
	return this->content;
} // end getContent method


/*
Performs a binary search on the BST, given a comparator function.
Returns the content of the BST node if a match is found.
Throws a std::runtime_error if no matching item can be found.
This uses a notion of equality based on the "less-than" comparator:
(a == b) if and only if !(a<b) && !(b<a)
*/
template <typename T>
T BST <T>::find(T query, bool comparator(T&, T&)){

	// if !less && !equal than it must be greater than, so no greater bool needed
	bool less = comparator(query, this->content);
	bool equal = !comparator(query, this->content) && !comparator(this->content, query);

	/* if the value of query is equal to a node, return that node's content;
	if it's less than, move left; if it's greater than, move right: throw error
	if the value cannot be found
	*/
	if(equal){
		return this->content;
	}else if(less && this->left != nullptr){
		return this->left->find(query, comparator);
	}else if(this->right != nullptr){
		return this->right->find(query, comparator);
	}else{
		// throw error if no match
		throw std::runtime_error("No matching item can be found.");
	} // end else throw error
} // end find method


/*
Inserts element x, of type T, into the BST.
This preserves the BST invariant:
a left child is always less than its parent, while
a right child is always not less than its parent.
This relies on the "less-than" comparator.
*/
template <typename T>
void BST <T>::insert(T x, bool comparator(T&, T&)){
	// boolean check for whether the vector has been added
	bool added = false;
	BST *p = this;

	/*
	While loop contintues until vector content
	has een inserted into binary search tree
	*/
	while(!added){
		bool less = comparator(x, p->content);

		/* if less-than and left pointer is null, create BST object and insert
		it into binary search tree, if pointer is not null, move left; if it is
		greater or equal, and the right pointer is null, create and insert BST
		object, if not null, move right;
		*/
		if(less){
			if(p->left == nullptr){
				BST *tmp = new BST(x);
				p->left = tmp;
				added = true;
			}else{
				p = p->left;
			} // end else
			} // end if
			else if(p->right == nullptr){
				BST *tmp = new BST(x);
				p->right = tmp;
				added = true;
			}else{
				p = p->right;
			} // end else if greater or equal but not null
	} // end while loop
}// end insert method


/*
Instantiate this template class for four types.
This is to allow the separation between interface and implementation.
*/
template class BST<int>;
template class BST<double>;
template class BST<std::string>;
template class BST<DNA>;
