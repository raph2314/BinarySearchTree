//Raphael Lopez 20656897	
//Dawhan Kim 20688854

#ifndef A3_AVL_TREE_HPP
#define A3_AVL_TREE_HPP

#include "a3_binary_search_tree.hpp"

class AVLTree: public BinarySearchTree
{
	Node* root_;
public:
	// Overriden insert and remove functions 
	// Do not modify these definitions
    bool insert(DataType val);
    bool remove(DataType val);

	// Define additional functions and attributes that you need below
	bool singleLeft(Node** toP);
	bool singleRight(Node** toP);
	bool doubleLeftRight(Node** toP);
	bool doubleRightLeft(Node** toP);	
	void balanceTree(Node** toP);

};
#endif

