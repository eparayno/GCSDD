#pragma once
#include "SearchTree.h"

class CustomerSearchTree : public SearchTree
{
    /*	------------------------------addHelper------------------------------------
    Description: Add helper that adds node. Recursive function.
    Pre-condition:	Called by << function.
    Post-condition:	Adds node to tree. */
    bool addHelper(Node*& subTree, Comparable*& comparable) override;

    /*	------------------------------removeHelper------------------------------------
    Description: remove helper that removes node if found. Recursive function.
    Pre-condition:	Called by << function.
    Post-condition:	Removes node from tree. */
    bool removeHelper(Node*& subTree, Comparable*& comparable) override;

    /*	------------------------------printTree------------------------------------
    Description: Recursively traverses through tree in inorder traversal. Each node 
                    will take up a line, and will print according to its operator<< 
                    implementation.
    Pre-condition:	Called by SearchTree's operator<< function.
    Post-condition:	prints out all of nodes in tree by printing its comparable item*/
    void printTreeHelper(ostream& outStream, Node* node) const override;
    

};

