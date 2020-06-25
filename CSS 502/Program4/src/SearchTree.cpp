/*  ---------------------------------------------------------------------------
    SEARCHTREE.CPP
    Binary Search Tree for Comparable
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    SearchTree class: Like a regular binary search tree (retains all
    functionality but instead holds Node pointers, which contains Comparable
    which has the following derived classes: Customers, Items.
        -- Contains default constructor, deep copy constructor, and destructor.
        -- allows for retrieval, insertion, and removal of Comparable* item
    Assumptions:
        -- Follows properties of trees
        -- Nodes and corresponding data initialized as null
        -- user must use driver to utilize methods in SearchTree
        -- In <<, each node will be represented by one line	*/

#include "SearchTree.h"

/*	-----------------------------Constructor-------------------------------
 Description: Default constructor for class SearchTree
 Pre-condition:	None
 Post-condition:	Creates default constructor, with root set to nullptr */
SearchTree::SearchTree() {}

/*	------------------------------Destructor-------------------------------
Description: Conventional destructor. Calls clear to recursively clear tree.
Pre-condition:	None. No longer in scope of Search Tree.
Post-condition:	Removes and deallocates all data from the SearchTree.*/
SearchTree::~SearchTree() {

    makeEmpty(root);

}

/*	-------------------------------remove----------------------------------
Description: Takes a Comparable as parameter. Passes the paremeter into removeHelper
                function to find location of the Node containing the
                Comparable pointer and remove it.
Pre-condition:	None.
Post-condition:	Calls remove helper, which has different implementation
                between the different subclasses*/
bool SearchTree::remove(Comparable*& comparable) {

    return removeHelper(root, comparable);

}

/*	--------------------------------add--------------------------------
Description: Takes a comparable pointer and attempts to insert into tree.
                If root is empty, will create new node containing comparable
                data, and sets it to root of tree. Else, it will pass the
                comparable item into insertHelper method, which will
                recursively find appropriate node location.
Pre-condition:	itemPtr must be a derived class of Comparable
Post-condition:	Returns true if it was added to the tree*/
bool SearchTree::add(Comparable*& nodeData) {

    if (root == nullptr) {
        root = new Node;
        root->nodeData = nodeData; // new node inserted into root.
        return true;
    }
    else {
        return addHelper(root, nodeData);
    }

}

/*	-----------------------------deleteNode------------------------------
Description: Will perform different algorithm depeneding on how many children
                it has. Follows conventional binary tree deletion.
Precondition:	Called by remove function.
Postcondition:	Will have successfully removed node from tree.*/
void SearchTree::deleteNode(Node*& node) {
    if (node->right == nullptr && node->left == nullptr) {
        delete node;
        node = nullptr;
        return;
    }

    if (node->left == nullptr) {
        Node* temp = node;
        node = node->right;
        delete temp;
        return;
    }

    if (node->right == nullptr) {
        Node* temp = node;
        node = node->left;
        delete temp;
        return;
    }

    node->nodeData = findAndDeleteSmallest(node->right);
}

/*	--------------------------findAndDeleteMostLeft------------------------
Description: Finds and deletes the lowest value of the right subtree as this is
                a convention for deletion of a node that contains more than 1 child.
Pre-condition:	Called by delete function.
Post-condition:	will have deleted lowest value of right subtree.*/
Comparable* SearchTree::findAndDeleteSmallest(Node*& node) {

    if (node->left == nullptr) {
        Node* temp = node;
        node = node->right;
        Comparable* val = temp->nodeData;
        delete temp;
        return val;
    }

    return findAndDeleteSmallest(node->left);
}

/*	-------------------------------getComparable-------------------------------
Description: Takes comparable as a parameter and tries to find and retrieve
                pointer to the Comparable item stored in the of nodes in the tree.
                Will return root if at root, or call recursive function to find
                in the tree.
Pre-condition:	Values must match according to operator==.
Post-condition:	Will return a pointer the Comparable item if found. */
Comparable* SearchTree::getComparable(Comparable*& data) const {

    if (root == nullptr) {
        return nullptr;
    }
    else {
        return getComparableHelper(root, data);
    }

}

/*	-------------------------getComparableHelper-----------------------------
Description: Recursively traverses through tree until it finds the node* that
                contains they comparable key that was passed as a parameter.
Pre-condition:	Called by retrieve function.
Post-condition:	Returns found matching Comparable. Else, it will return
                nullptr if not found.*/
Comparable* SearchTree::getComparableHelper(Node* pNode, Comparable*& nodeData) const {
    if (pNode == nullptr) {
        return nullptr;
    }
    else if (*pNode->nodeData == *nodeData) {
        return pNode->nodeData;
    }

    if (*pNode->nodeData > *nodeData) {
        return getComparableHelper(pNode->left, nodeData);
    }
    else {
        return getComparableHelper(pNode->right, nodeData);
    }
}

/*	---------------------------------makeEmpty---------------------------------
Description: Recursively removes and deallocates each node on the tree.
Pre-condition:	Called by makeEmpty function.
Post-condition:	All data from tree is deallocated */
void SearchTree::makeEmpty(Node*& subTree) {

    if (subTree == nullptr) {
        return;
    }

    if (subTree->left != nullptr) {
        makeEmpty(subTree->left);
    }

    if (subTree->right != nullptr) {
        makeEmpty(subTree->right);
    }

    delete subTree;
    subTree = nullptr;
}

/*	----------------------------------<<-----------------------------------
Description: Overloaded operator that prints the Comparable item.
Pre-condition:	N/A
Post-condition:	Calls helper method, printTree*/
ostream& operator<<(ostream& outStream, const SearchTree& tree) {

    tree.printTreeHelper(outStream, tree.root);
    return outStream;

}