//Raphael Lopez 20656897	
//Dawhan Kim 20688854

#include <iostream>
#include <cmath>
#include "a3_avl_tree.hpp"
using namespace std;
typedef AVLTree::DataType DataType;

bool AVLTree::singleLeft(Node** toP)
{
	Node* parent = *toP;
	Node* child = parent->right;
	parent->right = child->left;
	child->left = parent;
	*toP = child; 
	return true;
}
bool AVLTree::singleRight(Node** toP)
{
	Node* parent = *toP;
	Node* child = parent->left;
	parent->left = child->right;
	child->right = parent;
	*toP = child; 
	return true;	
}
bool AVLTree::doubleLeftRight(Node** toP)
{
	Node* parent = *toP;
	Node* child = (*toP)->left;
	Node* grandChild = child->right; 
	child->right = grandChild->left;
	grandChild->left = child;
	parent->left = grandChild->right;
	grandChild->right = parent; 
	*toP = grandChild; 
	return true;
	
}
bool AVLTree::doubleRightLeft(Node** toP)
{
	Node* parent = *toP;
	Node* child = (*toP)->right;
	Node* grandChild = child->left; 
	child->left = grandChild->right;
	grandChild->right = child;
	parent->right = grandChild->left;
	grandChild->left = parent;
	*toP = grandChild;
	return true;
	
}


void AVLTree::balanceTree(Node** toP)
{
	//End condidition to the recursive call
	if(!*toP)
		return;
		
	//PostOrder visits to the tree's nodes
	balanceTree(&(*toP)->left);
	balanceTree(&(*toP)->right);

	//Parent node's avlBalance is at least 2
	if((*toP)->avlBalance > 1){
		//Left child's avlBalance is negative
		if(((*toP)->left)->avlBalance < 0)
			doubleLeftRight(toP);
		//Left child's avlBalance is positive
		else
			singleRight(toP);
	}
	//Parent node's avlBalance is at least -2
	else if((*toP)->avlBalance < -1){
		//Right child's avlBalance is negative
		if(((*toP)->right)->avlBalance > 0)
				doubleRightLeft(toP);
		//Right child's avlbalance is positive
		else
			singleLeft(toP);
	}
	//After each call, update avlBalance at each node 
	updateNodeBalance(getRootNode());	

	
}

bool AVLTree::insert(DataType val)
{
	if(!(BinarySearchTree::insert(val)))
		return false;
	
	//Pass the root node into the updateNodeBalance() function
	Node** toP = BinarySearchTree::getRootNodeAddress();	
	updateNodeBalance(*toP);
	
	//Verify that the tree contains at least 3 nodes and hence require balancing
	unsigned int depth = BinarySearchTree::depth();
	if(depth > 1)
		balanceTree(toP);
	return true; 
}



bool AVLTree::remove(DataType val)
{
	if(!(BinarySearchTree::remove(val)))
		return false;
		
	//Pass the root node into the updateNodeBalance() function
	Node** toP = BinarySearchTree::getRootNodeAddress();
	updateNodeBalance(*toP);
	
	//Verify that the tree contains at least 3 nodes and hence require balancing
	unsigned int depth = BinarySearchTree::depth();
	if(depth>1)
		balanceTree(toP);
	return true; 
}

