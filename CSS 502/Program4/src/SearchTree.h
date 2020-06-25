#pragma once
/*  ---------------------------------------------------------------------------
    SEARCHTREE.H
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

#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include "Comparable.h"
#include "Item.h"

using namespace std;

class SearchTree {
protected:
    struct Node {
        Comparable* nodeData;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    /*	-----------------------------addHelper--------------------------------
    Description: Virtual addHelper function.
    Pre-condition:	N/a
    Post-condition:	Will have successfully called derived SearchTree class
                    implementation.*/
    virtual bool addHelper(Node*& subTree, Comparable*& comparable) = 0;

    /*	-----------------------------removeHelper------------------------------
    Description: Virtual removeHelper function.
    Pre-condition:	N/a
    Post-condition:	Will have successfully called derived SearchTree class
                    implementation.*/
    virtual bool removeHelper(Node*& subTree, Comparable*& comparable) = 0;

    /*	-----------------------------deleteNode------------------------------
    Description: Will perform different algorithm depeneding on how many children
                    it has. Follows conventional binary tree deletion.
    Precondition:	Called by remove function.
    Postcondition:	Will have successfully removed node from tree.*/
    void deleteNode(Node*& pNode);

    /*	-------------------------getComparableHelper-----------------------------
    Description: Recursively traverses through tree until it finds the node* that
                    contains they comparable key that was passed as a parameter. 
    Pre-condition:	Called by retrieve function.
    Post-condition:	Returns found matching Comparable. Else, it will return 
                    nullptr if not found.*/
    Comparable* getComparableHelper(Node* subTree, Comparable*& comparable) const;

    /*	--------------------------findAndDeleteMostLeft------------------------
    Description: Finds and deletes the lowest value of the right subtree as this is
                    a convention for deletion of a node that contains more than 1 child.
    Pre-condition:	Called by delete function.
    Post-condition:	will have deleted lowest value of right subtree.*/
    Comparable* findAndDeleteSmallest(Node*& node);

    /*	---------------------------------makeEmpty---------------------------------
    Description: Recursively removes and deallocates each node on the tree.
    Pre-condition:	Called by makeEmpty function.
    Post-condition:	All data from tree is deallocated */
    void makeEmpty(Node*& subTree);

public:

    Node* root = nullptr;

    /*	-----------------------------Constructor-------------------------------
    Description: Default constructor for class SearchTree
    Pre-condition:	None
    Post-condition:	Creates default constructor, with root set to nullptr */
    SearchTree();

    /*	------------------------------Destructor-------------------------------
    Description: Conventional destructor.
    Pre-condition:	None. No longer in scope of Search Tree.
    Post-condition:	Removes and deallocates all data from the SearchTree.*/
    virtual ~SearchTree();

    /*	-------------------------------remove----------------------------------
    Description: Takes a Comparable as parameter. Passes the paremeter into removeHelper
                    function to find location of the Node containing the 
                    Comparable pointer and remove it.
    Pre-condition:	None.
    Post-condition:	Calls remove helper, which has different implementation 
                    between the different subclasses*/
    bool remove(Comparable*& comparable);

    /*	-------------------------------getComparable-------------------------------
    Description: Takes comparable as a parameter and tries to find and retrieve 
                    pointer to the Comparable item stored in the of nodes in the tree.
                    Will return root if at root, or call recursive function to find
                    in the tree.
    Pre-condition:	Values must match according to operator==.
    Post-condition:	Will return a pointer the Comparable item if found. */
    Comparable* getComparable(Comparable*& comparable) const;

    /*	----------------------------------<<-----------------------------------
    Description: Overloaded operator that prints the Comparable item.
    Pre-condition:	N/A
    Post-condition:	Calls helper method, printTree*/
    friend ostream& operator<<(ostream& outStream, const SearchTree& tree);

    /*	------------------------------printTree------------------------------------
    Description: Virtual method that allows derived SearchTree classes to 
                    implement their own printTree functions.
    Pre-condition:	Called by operator<< function.
    Post-condition:	Will have called derived class implementaiton*/
    virtual void printTreeHelper(ostream& outStream, Node* node) const = 0;

    /*	--------------------------------add--------------------------------
    Description: Takes a comparable pointer and attempts to insert into tree.
                    If root is empty, will create new node containing comparable
                    data, and sets it to root of tree. Else, it will pass the
                    comparable item into insertHelper method, which will 
                    recursively find appropriate node location.
    Pre-condition:	itemPtr must be a derived class of Comparable
    Post-condition:	Returns true if it was added to the tree*/
    bool add(Comparable*& comparable);
};
