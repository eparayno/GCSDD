#include "CustomerSearchTree.h"
#include "Customer.h"

/*	------------------------------addHelper------------------------------------
Description: Add helper that adds node. Recursive function.
Pre-condition:	Called by << function.
Post-condition:	Adds node to tree. */
bool CustomerSearchTree::addHelper(Node*& subTree, Comparable*& comparable)
{
    if (subTree == nullptr) {
        subTree = new Node;
        subTree->nodeData = comparable;
        return true;
    }

    if (*subTree->nodeData == *comparable) {
        return false;
    }

    if (*subTree->nodeData > * comparable) {
        return addHelper(subTree->left, comparable);
    }
    else {
        return addHelper(subTree->right, comparable);
    }

}

/*	------------------------------removeHelper------------------------------------
Description: remove helper that removes node if found. Recursive function.
Pre-condition:	Called by << function.
Post-condition:	Removes node from tree. */
bool CustomerSearchTree::removeHelper(Node*& subTree, Comparable*& comparable)
{
    if (subTree == nullptr) {
        return false;
    }

    if (*subTree->nodeData == *comparable) {
        deleteNode(subTree);
        return true;
    }

    if (*subTree->nodeData > * comparable) {
        return removeHelper(subTree->left, comparable);
    }
    else {
        return removeHelper(subTree->right, comparable);
    }
}

/*	------------------------------printTree------------------------------------
Description: Recursively traverses through tree in inorder traversal. Each node
                will take up a line, and will print according to its operator<<
                implementation.
Pre-condition:	Called by SearchTree's operator<< function.
Post-condition:	prints out all of nodes in tree by printing its comparable item*/
void CustomerSearchTree::printTreeHelper(ostream& outStream, Node* node) const
{
    if (node != nullptr) {
        printTreeHelper(outStream, node->left);
        Customer* customer = dynamic_cast<Customer*>(node->nodeData);
        customer->printHistory();
        printTreeHelper(outStream, node->right);
    }
}
