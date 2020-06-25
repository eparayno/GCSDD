/*  ---------------------------------------------------------------------------
	SEARCHTREE.CPP
	BinarySearchTree for Comparable
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	SearchTree class: Like a regular binary search tree (retains all
	functionality but instead holds Node pointers which contain Node as nested
	struct, which contains Comparable pointer which encapsulates a char.
	This is the header file for the SearchTree class.
		-- Contains default constructor, deep copy constructor, and destructor.
		-- allows for assignment of one tree to another through deep copy
		-- allows for checking equality and inequality between two trees
		-- allows for insertion of Comparable* item
		-- allows for removal of Comparable item
		-- contains method for removal and deallocation of data from tree
	Assumptions:
		-- Follows properties of trees
		-- Nodes and corresponding intialized as null
		-- user must use driver to utilize methods in SearchTree
		-- in <<, each node will be represented by one line
	*/

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include "SearchTree.h"
#include <iostream>
#include <algorithm>

/*	-----------------------------Constructor-------------------------------
Default constructor for class SearchTree
Precondition:	None
Postcondition:	Creates default constructor, with root set to nullptr */
SearchTree::SearchTree() {}

/*	---------------------------Copy Constructor----------------------------
Copy constructor that takes the tree to be copied as a parameter and
assigns	its values to this SearchTree through deep copy.
	Precondition:	None
	Postcondition:	Creates default constructor, with root set to nullptr */
SearchTree::SearchTree(const SearchTree& sourceTree) {
	Node* subTreeRoot = sourceTree.root;
	deepCopyTreeHelper(root, subTreeRoot);
}
/*	----------------------------deepCopyTreeHelper------------------------------
Recursively creates deep copy of tree using pointers that track two trees. Will
copy character data, position, and occurence.
	Precondition:	Called by deepCopyTree function.
	Postcondition:	Creates two identical trees that are separate from each other */
void SearchTree::deepCopyTreeHelper(Node*& copySubTree, Node*& sourceSubTree) {
	if (sourceSubTree == NULL) {
		copySubTree = NULL;
	} else {
		copySubTree = new Node;
		copySubTree->itemPtr = sourceSubTree->itemPtr;
		copySubTree->itemCount = sourceSubTree->itemCount;

		deepCopyTreeHelper(copySubTree->leftChildNodePtr, sourceSubTree->leftChildNodePtr);
		deepCopyTreeHelper(copySubTree->rightChildNodePtr, sourceSubTree->rightChildNodePtr);
	}
}

/*	------------------------------Destructor-------------------------------
Conventional destructor.
	Precondition:	None. No longer in scope of Search Tree.	
	Postcondition:	Removes and deallocates all data from the SearchTree.*/
SearchTree::~SearchTree() {
	makeEmpty();
}

/*	--------------------------------insert--------------------------------
Takes a comparable pointer and attempts to insert into tree. If root is empty,
will create new node containing comparable data, and sets it to root of tree.
Else, it will pass the comparable item along with root subtree into
insertHelper method, which will recursively find appropriate node location for
char encapsulated in Comparable and insert it at that location. Location will
be determined in order of insertion and ASCII ascending order.
Precondition:	itemPtr must contain appropriate ASCII value.
Postcondition:	itemPtr is set as Node* itemPtr variable and placed in
				Search Tree based on ASCII ordering.*/
bool SearchTree::insert(Comparable* itemPtrInput) {
	if (root == NULL) {
		root = new Node; // creates new root node with values
		root->itemPtr = itemPtrInput;
		root->itemCount++;
		return true;
	} else {
		return insertHelper(root, itemPtrInput);
	}
}

/*	-------------------------------retrieve -------------------------------
Takes comparable parameter and tries to find and retrieve Comparable
pointer in the tree which encapsulates a character value that matches the
one of Comparable passed as parameter.
Precondition:	itemPtr must contain appropriate ASCII value
Postcondition:	If the tree being searched is empty	or if the Comparable is
				not found in the tree, the method will return a nullptr.*/
const Comparable* SearchTree::retrieve(const Comparable& key) const {
	if (root != NULL) {
		return retrieveHelper(root, key);
	} else {
		return nullptr;
	}
}

/*	-----------------------------retrieveHelper--------------------------------
Recursively traverses through tree until it finds the node* that contains they
comparable key that was passed as a parameter. Will return null if not found.
Precondition:	Called by retrieve function.
Postcondition:	prints out a frequency table with each unique character taking
			up one line. Sum of all frequency should be the count of
			characters in entire text file.*/
Comparable* SearchTree::retrieveHelper(Node* subTree, const Comparable& key) const {
	if (subTree == NULL) {
		return nullptr;
	} else if ((*subTree->itemPtr) == key) {
		return subTree->itemPtr;
	} else if (*subTree->itemPtr < key) {
		retrieveHelper(subTree->rightChildNodePtr, key);
	} else {
		retrieveHelper(subTree->leftChildNodePtr, key);
	}
}

/*	-------------------------------height----------------------------------
Takes a comparable key and find's its location on the tree. The method will
find the node in the tree and then set that as the subTree passed to a
method that will find its maxheight (its distance from the leaf end of the
tree).
Precondition:	Must be a value that exists in the tree, to find actual
				height.
Postcondition:	An int will be returned. A Comparable value that exists at
the leaf will return 0, as a root that only contains itself also a 0, as
a root with at least one child should be a positive neumber (indicative of
maximum height starting at 0) and value that doesn't exist in the tree will
return -1.*/
int SearchTree::height(const Comparable& key) const {
	if (root == NULL) {
		return -1; // returns -1 if empty tree
	} else {
		int depthOfNode = heightHelper(root, key);
		if (depthOfNode == -1) {
			return -1;
		}
		else {
			return heightHelper(root, key);
		}
	}
}

/*	-----------------------------heightHelper--------------------------------
Recursively searches through tree until it finds the node* pointing to key.
If it was found, it sends that subTree into the maxHeight helper to count
how far away it is from its leaf. Recall, there can be multiple leafs, but
the max is what counts.
Precondition:	Called by height function.
Postcondition:	returns int that counts how far it is from the bottom of
				tree*/
int SearchTree::heightHelper(Node* subTree, const Comparable& key) const {
	if (*subTree->itemPtr == key) {
		return maxHeightHelper(subTree) - 1;
	} else {
		if (retrieveHelper(subTree->leftChildNodePtr, key) != NULL ) {
			heightHelper(subTree->leftChildNodePtr, key);
		} else if (retrieveHelper(subTree->rightChildNodePtr, key) != NULL) {
			heightHelper(subTree->rightChildNodePtr, key);
		} else {
			return -1;
		}
	}
}

/*	--------------------------maxheightHelper------------------------------
Takes a subTree and finds its max distance from leaf.
Precondition:	Called by height function.
Postcondition:	Returns int that describes its distance from leaf. If the node
				is a leaf, then it is 0. If it is a root, it will return the
				distance away from the leaf.*/
int SearchTree::maxHeightHelper(Node* subTree) const {
	if (subTree == NULL) {
		return 0;
	} else {
		int leftSideMaxDepth = maxHeightHelper(subTree->leftChildNodePtr);
		int rightSideMaxDepth = maxHeightHelper(subTree->rightChildNodePtr);
		
		//helps determine where the max height is relative to subtree
		if (leftSideMaxDepth > rightSideMaxDepth) { 
			return 1 + leftSideMaxDepth;
		} else {
			return 1 + rightSideMaxDepth;
		}
	}
}

/*	-----------------------------insertHelper----------------------------------
Recursively finds location of where the node is to be inserted in the tree. The
Node is inserted if not found in the tree or increments count if it already
exists.
Precondition:	Called by insert function.
Postcondition:	If the value to be deleted was the last occurence, decrement
				item Count and return fasle. If it was not found, return
				false. */
bool SearchTree::insertHelper(Node*& subTree, Comparable* itemPtrInput) {

	if (subTree == NULL) {
		subTree = new Node; // create new node & add data 
		subTree->itemPtr = itemPtrInput;
		subTree->itemCount++;
		return true;
	} 
	
	if (*subTree->itemPtr == *itemPtrInput) {
		subTree->itemCount++; // icrement if node exists
		return false;
	} 
	
	if (*subTree->itemPtr > *itemPtrInput ) {
		return insertHelper(subTree->leftChildNodePtr, itemPtrInput);
	} else { 
		return insertHelper(subTree->rightChildNodePtr, itemPtrInput);
	} 	

}


/*	-----------------------------makeEmpty--------------------------------------
Recursively removes and deallocates each node on the tree starting from root.
Precondition:	Called by destructor function.
Postcondition:	All data from tree is deallocated */
void SearchTree::makeEmpty() {
	makeEmptyHelper(root);
}

/*	-----------------------------makeEmptyHelper-------------------------------
Recursively removes and deallocates each node on the tree starting from subTree.
Precondition:	Called by makeEmpty function.
Postcondition:	All data from tree is deallocated */
void SearchTree::makeEmptyHelper(Node*& subTree) {
	if (subTree == NULL) {
		return;
	}
	if (subTree->leftChildNodePtr != NULL) {
		makeEmptyHelper(subTree->leftChildNodePtr);
	}
	if (subTree->rightChildNodePtr != NULL) {
		makeEmptyHelper(subTree->rightChildNodePtr);
	}

	delete subTree;
	subTree = NULL;
}

/*	---------------------------------==------------------------------------
Checks if two trees are equal. They are only equal if they have the same
data, same structure (same children), and same number of occurences for
each comparable.
Precondition:	Must have two trees that contain node pointers, pointing to
				comparable pointers that encapsulates char.
Postcondition:	Returns true if they meet the criteria of equal trees
stated above. False otherwise. */
SearchTree& SearchTree::operator=(SearchTree& treeToBeCopied) {
	if (this == &treeToBeCopied) {
		return *this;
	}

	// Will empty tree and then create deep copy.
	this->makeEmptyHelper(this->root); 
	this->root = NULL;
	this->deepCopyTreeHelper(this->root, treeToBeCopied.root);
	return *this;
}

/*	----------------------------------<<--- -------------------------------
Overloaded operator that prints unique characters with its corresponding
frequency count.
Precondition:	Should be a nonempty tree to get an actual table.
Postcondition:	Each node in the SearchTree should be should be represented
				as one line, with its corresponding frequency. .*/
ostream& operator<<(ostream& output, SearchTree& treeToBePrinted) {
	if (treeToBePrinted.root == NULL) {
		output << "Empty tree.";
	} else {
		treeToBePrinted.printTree(output, treeToBePrinted.root); 
	}
	return output;
}

/*	------------------------------printTree------------------------------------
Recursively traverses through tree in inorder traversal (to print out ASCII
in ascending order). Each node will take up a line containing the character
that was encapsulated in comparable along with its frequency.
Precondition:	Called by << function.
Postcondition:	prints out a frequency table with each unique character taking
				up one line. Sum of all frequency should be the count of
				characters in entire text file.*/
void SearchTree::printTree(ostream& output, Node*& subTree) {
	if (subTree != NULL) {
		// inorder traversal (left, mid, right)
		printTree(output, subTree->leftChildNodePtr);
		output << *subTree->itemPtr; // encapuslated char
		output << " "; 
		output << subTree->itemCount; // corresponding count
		output << endl;
		printTree(output, subTree->rightChildNodePtr);
	}
}

/*	---------------------------------!=------------------------------------
Checks if two trees are not equal. They are not equal if in any case they
have the different data, structure, or number occurence. This is checked by
returning the negation of == operator.
Precondition:	Must have two trees that contain node pointers, pointing to
				comparable pointers that encapsulates char.
Postcondition:	Returns false if they meet the criteria of equal trees
				stated above. True otherwise. */	
bool SearchTree::operator!=(SearchTree& treeToBePrinted) {
	return !areEqual(root, treeToBePrinted.root);
}

/*	-------------------------------remove----------------------------------
Takes a key as parameter. Passes the paremeter into removeHelper function
along with root to recursively find location of the Node containing the
Comparable pointer and remove it.
Precondition:	None.
Postcondition:	If the value to be deleted was the last occurence, the
Node is removed from the tree and method returns true. If more than 1
occurence is left in itemCount of the particular node, then we decrement
item Count and return fasle. If it was not found, return false. */
bool SearchTree::remove(const Comparable& key) {
	return removeHelper(root, key);
}

/*	-----------------------------removeHelper------------------------------
Recursive algorithm that will search for node location of node containing key.
If it exists and contains more than 1 occurence, decrement item count. If it
is the last occurence, will delete that node by calling delete.
Precondition:	Called by remove function.
Postcondition:	will have successfully decremented or removed node from
				tree.*/
bool SearchTree::removeHelper(Node*& currNode, const Comparable& key) {
	if (currNode == NULL) {
		return false;
	} else if ((*currNode->itemPtr) == key) {
		if (currNode->itemCount == 1) {
			delete(currNode);	// deletes node since it is itemCount is 1
		} else {
			currNode->itemCount--; // decrement item count
		}
		return true;
	} else if ((*currNode->itemPtr) > key) {
		return removeHelper(currNode->leftChildNodePtr, key);
	} else {
		return removeHelper(currNode->rightChildNodePtr, key);
	}
}

/*	-----------------------------deleteNode------------------------------
Will perform different algorithm depeneding on how many children it has.
Follows conventional binary tree deletion.
Precondition:	Called by remove function.
Postcondition:	will have successfully removed node from tree.*/
void SearchTree::deleteNode(Node*& subTree){
		if (root->leftChildNodePtr == nullptr && root->rightChildNodePtr == nullptr) { 
			delete root;
			root = nullptr;
		} else if (root->leftChildNodePtr == nullptr || root->rightChildNodePtr == nullptr) {
			Node* tmp = root;
			root = root->leftChildNodePtr == nullptr ? root->rightChildNodePtr : root->leftChildNodePtr;
			delete tmp;
		} else {
			root->itemPtr = findAndDeleteMostLeft(root->rightChildNodePtr);
		}
	}

/*	--------------------------findAndDeleteMostLeft------------------------
Finds and deletes the lowest value of the right subtree as this is
a convention for deletion of a node that contains more than 1 child.
Recursive function that calls itself until successful.
Precondition:	Called by delete function.
Postcondition:	will have deleted lowest value of right subtree.*/
Comparable* SearchTree::findAndDeleteMostLeft(Node*& subTree) {
	if (root->leftChildNodePtr == nullptr) {
		Comparable* item = root->itemPtr; //will set it to root & delete
		Node* tmp = root;
		root = root->rightChildNodePtr;
		delete tmp;
		return item;
	} else {
		return findAndDeleteMostLeft(root->leftChildNodePtr);
    }
}

/*	---------------------------------==------------------------------------
	Checks if two trees are equal. They are only equal if they have the same
	data, same structure (same children), and same number of occurences for
	each comparable.
	Precondition:	Must have two trees that contain node pointers, pointing to
					comparable pointers that encapsulates char.
	Postcondition:	Returns true if they meet the criteria of equal trees
	stated above. False otherwise. */
bool SearchTree::operator==(SearchTree& treeToBePrinted) {
	return areEqual(root, treeToBePrinted.root); 
}

/*	-----------------------------areEqual----------------------------------
Checks if the rest of subtree is equal in character value, count, and
structure. Recursive function.
Precondition:	Called by == function.
Postcondition:	Return false if any value, count, or structure differs
				between two trees.*/
bool SearchTree::areEqual(Node* originalSubTree, Node* subTree) const {
	if (subTree == nullptr && originalSubTree == nullptr) {
		return true; // true because they are both empty.
	} else if (subTree == nullptr && originalSubTree != nullptr) {
		return false; 
	} else if (subTree != nullptr && originalSubTree == nullptr) {
		return false;
	} else {
		if (*originalSubTree->itemPtr == *subTree->itemPtr &&
			originalSubTree->itemCount == subTree->itemCount &&
			areEqual(originalSubTree->leftChildNodePtr, subTree->leftChildNodePtr) &&
			areEqual(originalSubTree->rightChildNodePtr, subTree->rightChildNodePtr)) {
				return true; // will only return true if the entire tree is identical
		}
	}
	return false;

}
