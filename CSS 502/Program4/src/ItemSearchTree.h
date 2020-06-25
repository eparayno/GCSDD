/*  ---------------------------------------------------------------------------
    ITEMSEARCHTREE.H
    Binary Search Tree for Item
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    SearchTree class: Derived class of SearchTree
        -- different add and remove function	*/

#pragma once
#include "SearchTree.h"

class ItemSearchTree : public SearchTree
{
    /*	------------------------------addHelper------------------------------------
    Description: Add helper that adds node. Increments count. Recursive function.
    Pre-condition:	Called by add.
    Post-condition:	Adds node  to tree or increments count appropriately. */
    bool addHelper(Node*& subTree, Comparable*& comparable) override;

    /*	-----------------------------removeHelper------------------------------
     Description: Recursive algorithm that will search for node location of node
                     containing Comparable. If it exists and contains more than 1
                     occurrence, decrement item count. Will not remove from tree
                     if count is zero.
     Pre-condition:	Called by remove function.
     Post-condition:	will have successfully decremented or removed node from
                     tree.*/
    bool removeHelper(Node*& subTree, Comparable*& comparable) override;

    /*	------------------------------printTree------------------------------------
    Description: Recursively traverses through tree in inorder traversal. 
                    Each node will take up a line containing the data that was 
                    encapsulated in comparable along with its frequency.
    Pre-condition:	Called by << function.
    Post-condition:	prints out a frequency table with each unique character taking
                    up one line. Sum of all frequency should be the count of
                    characters in entire text file.*/
    void printTreeHelper(ostream& outStream, Node* node) const override;
};

