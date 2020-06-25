/*  ---------------------------------------------------------------------------
    ITEMSEARCHTREE.CPP
    Binary Search Tree for Item
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    SearchTree class: Derived class of SearchTree
        -- different add and remove function	*/

#include "ItemSearchTree.h"
#include <iomanip>

/*	------------------------------addHelper------------------------------------
Description: Add helper that adds node. Increments count. Recursive function.
Pre-condition:	Called by add.
Post-condition:	Adds node  to tree or increments count appropriately. */
bool ItemSearchTree::addHelper(Node*& subTree, Comparable*& comparable)
{
    if (subTree == nullptr) {
        subTree = new Node;
        subTree->nodeData = comparable;
        return true;
    }

    if (*subTree->nodeData == *comparable) {
        Item* item = static_cast<Item*>(subTree->nodeData);
        item->setCount(item->getCount() + 1);
        return false;
    }

    if (*subTree->nodeData > * comparable) {
        return addHelper(subTree->left, comparable);
    }
    else {
        return addHelper(subTree->right, comparable);
    }

}

/*	-----------------------------removeHelper------------------------------
 Description: Recursive algorithm that will search for node location of node
                 containing Comparable. If it exists and contains more than 1
                 occurrence, decrement item count. Will not remove from tree
                 if count is zero.
 Pre-condition:	Called by remove function.
 Post-condition:	will have successfully decremented or removed node from
                 tree.*/
bool ItemSearchTree::removeHelper(Node*& subTree, Comparable*& comparable)
{
    if (subTree == nullptr) {
        return false;
    }

    if (*subTree->nodeData == *comparable) {
        Item* item = static_cast<Item*>(subTree->nodeData);
        item->setCount(item->getCount() - 1);
        // Will keep in inventory despite 0 count, bc we might need to refer to it.

        return true;
    }

    if (*subTree->nodeData > * comparable) {
        return removeHelper(subTree->left, comparable);
    }
    else {
        return removeHelper(subTree->right, comparable);
    }
}

void ItemSearchTree::printTreeHelper(ostream& outStream, Node* node) const
{
    if (node != nullptr) {
        printTreeHelper(outStream, node->left);
        
        outStream << "Count:" << std::setfill('0') << std::setw(3) << static_cast<Item*>(node->nodeData)->getCount() << ", ";
        outStream << *node->nodeData << endl;
        printTreeHelper(outStream, node->right);
    }
}
