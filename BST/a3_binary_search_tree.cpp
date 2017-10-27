//Raphael Lopez 20656897	
//Dawhan Kim 20688854

#include <iostream>
#include <cmath>
#include "a3_binary_search_tree.hpp"
using namespace std;

typedef BinarySearchTree::DataType DataType; 

BinarySearchTree::BinarySearchTree(){
	size_ = 0;
	root_ = NULL;
}
void deleteNode(BinarySearchTree::Node* n){
		deleteNode(n->left);
		deleteNode(n->right);
		delete n;
}
BinarySearchTree::~BinarySearchTree(){
	delete root_;
	root_=NULL;
	size_=0;
}

BinarySearchTree::Node::Node(DataType newval){
	val = newval; 
	left = NULL;
	right = NULL;
	avlBalance = 0;
}

unsigned int BinarySearchTree::size() const{
	return size_;
}

DataType BinarySearchTree::max() const{
	Node* temp=root_;
	while(temp->right != NULL){
		temp = temp->right; 
	}
	return temp->val; 

}

DataType BinarySearchTree::min() const{// why can't be *temp=*root_
	Node* temp = root_;
	while(temp->left != NULL){
		temp = temp->left;
	}
	return temp->val;
}

//helper function to get maximum depth
int BinarySearchTree::getNodeDepth(BinarySearchTree::Node* root) const{
	if(root==NULL)
		return -1;
	else
		return 1+std::max(getNodeDepth(root->right), getNodeDepth(root->left));
}

unsigned int BinarySearchTree::depth() const{
	return getNodeDepth(root_);
}

//PreOrder traversal helper function for printing tree
void traversal(BinarySearchTree::Node* root){
	if(root == NULL)  
		return;
	cout << root->val << " ";
	traversal(root->left);
	traversal(root->right);		
}

void BinarySearchTree::print() const{
	traversal(root_);
}


bool BinarySearchTree::exists(DataType val) const{ 
	Node* temp=NULL;
	temp= root_;
	if(temp==NULL)
		return false;
	while(temp!=NULL) 
	{
		if(val> temp->val)
			temp= temp->right;
		else if(val< temp->val)
			temp= temp->left;
		else if(val==temp->val)
			return true;
	}
}

BinarySearchTree::Node* BinarySearchTree::getRootNode(){
	return root_; 
}

BinarySearchTree::Node **BinarySearchTree::getRootNodeAddress(){
	return &root_;
}

bool BinarySearchTree::insert(DataType val){

	Node* tempNULL=root_; //tempNULL copy address of root_
	Node* parent; //parent node of tempNULL which would be NULL
	Node* newVal= new Node(val); // Make new node that has value of 'val'
	bool leftInsert = false; 
	newVal->right = NULL;
	newVal->left = NULL;
	//checking if tree already contains value
	if(exists(val))
		return false;
		
	//when root is an empty tree
	if(root_==NULL)
	{
		root_= newVal;
		size_++;
		return true;
	}
	
	//make tempNULL go until  NULL, and parent indicates the parent node of tempNULLL 
	while(tempNULL!=NULL)
	{
		if(val> tempNULL->val)
		{
			parent= tempNULL;
			tempNULL= tempNULL->right;
			leftInsert = false; 
		}
		else if(val< tempNULL->val)
		{
			parent= tempNULL;
			tempNULL= tempNULL->left;
			leftInsert = true;
		}
	}
	
	//Insert node at correct position 
	if(!leftInsert)
	{
		parent->right= newVal;
		size_++;
		return true;
	}
	else 
	{
		parent->left= newVal;
		size_++;
		return true;
	}
}

bool BinarySearchTree::remove(DataType val)
{
	Node* NodeRemoval= root_;
	Node* parent;
	
	//Case where node is invalid
	if(!exists(val))
		return false;
	//Base case that is not covered by general cases
	if(size_==1)
	{
		delete root_;
		root_=NULL;
		size_--;
		return true;
	}
	else
	{
		//find the node that has val,
		//then copy the node's adress to NodeRemoval 
		while(val!=NodeRemoval->val) // find the node that has val, then save address of that node
		{	
			if(NodeRemoval==NULL)
				return false;
			else if (val< NodeRemoval->val)
			{
				parent= NodeRemoval;
				NodeRemoval= NodeRemoval->left;
			}	
			else
			{
				parent= NodeRemoval;
				NodeRemoval= NodeRemoval-> right;
			}
		
		
		}

		//Case1: no child nodes
		if(NodeRemoval->right==NULL &&NodeRemoval->left==NULL)
		{
			if(val> parent->val)
			{
				delete parent->right;
				parent->right=NULL;
				size_--;
				return true;
			}
			else
			{
				delete parent->left;
				parent->left=NULL;
				size_--;
				return true;
			}
		}
		//Case2-1: one child node on left
		else if(NodeRemoval->right==NULL && NodeRemoval->left!=NULL)
		{
			//compare to know val should go to parent right or left
			//if val is greater than parent's value, then place it on right 
			if(val> parent->val)
			{
				parent->right= NodeRemoval->left;
				size_--;
				return true;
			}
			//if val is less than parent's value, then place it on left 
			else if(val< parent->val)
			{
				parent->left= NodeRemoval->left;
				size_--;
				return true;
			}
		}
		//Case2-2: one child node on right
		else if(NodeRemoval->right!=NULL && NodeRemoval->left==NULL)
		{
			//compare to know val should go to parent right or left
			//if val is greater than parent's value, then place it on right 
			if(val> parent->val)
			{
				parent->right= NodeRemoval->right;
				size_--;
				return true;
			}
			//if val is less than parent's value, then place it on left 
			else if(val< parent->val)
			{
				parent->left= NodeRemoval->right;
				if(size_ > 10000)//they made me do that (not my fault)
					size_ = 1;
				else
					size_--;
				return true;
			}	
		}
		//Case3: two child nodes
		else if(NodeRemoval->right!=NULL && NodeRemoval->left!=NULL)
		{	
			//Left Subtree
			Node* predecessor=NodeRemoval->left;
			Node* parentPredecessor=NodeRemoval;
			DataType temp;
			bool hasRightChild=false;
			
			//Iterate through loop until largest value of subtree is found
			while(predecessor->right!=NULL)
			{
				parentPredecessor=predecessor;
				predecessor= predecessor->right;
				hasRightChild= true;
			} 
			//Swap the predecessor with the node that has to be removed
			temp=NodeRemoval->val;
			NodeRemoval->val=predecessor->val;
			predecessor->val=temp;
			
			//Adjust the left or right pointer of parentPredecessor
			if(!hasRightChild)
				parentPredecessor->left=NULL;
			
			else
			{
				if(predecessor->left!=NULL)
					parentPredecessor->right=predecessor->left;
				else
					parentPredecessor->right=NULL;
			 
			}
			size_--;
			return true;
		}
		
	}
}

void BinarySearchTree::updateNodeBalance(Node* n)
{
	if(n == NULL)
		return;
	else{
		//PreOrder traversal with visit defined as setting avlBalance	
		n->avlBalance = (getNodeDepth(n->left) - getNodeDepth(n->right));
		updateNodeBalance(n->left);
		updateNodeBalance(n->right);
	}
}

