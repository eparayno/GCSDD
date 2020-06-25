/* File name: BST.cpp
 * Author name: Erika Parayno (SID #: 1425156)
 * Date: 11/27/2019
 * Description: This class is a modified implementation of the BinarySearchTree class. For the most part, it utilizes
 * recursive algorithms to traverse a tree. More specifically, we are using inOrder, to insure that we are printing
 * out the keys in alphabetical order. This class also contains constructors and destructor, which clears and deletes
 * the structure whenever it is out of scope, which should ensure that we are free of memory leaks.
 * */

#include "BST.h"

/* Description: default constructor
 * Parameter: N/A
 * Pre-condition: called in main
 * Post-condition: creates a new BST with root equal to nullPtr and itemCount at 0
 * Return: N/A
 * */
BST::BST() {}

/* Description: default destructor
 * Parameter: N/A
 * Pre-condition: called when the object goes out of scope on the stack
 * Post-condition: called clear starting from root, which is responsible for recursively clearing the tree
 * Return: N/A
 * */
BST::~BST() {
   clear(root);
}

/* Description: this method checks if the tree is empty and if it is, we add a new node and set it to root. Otherwise,
 * we will call the insert method, which will recursively find the correct placement of the key, so that it preserves
 * order of the BST.
 * Parameter: const string &key, const string &preContextInput, const string &postContextInput
 * Pre-condition: called from main class in the addContentsToTree method.
 * Post-condition: successfully added a new BSTNode with its respective contents in the BST.
 * Return: boolean true if it successfully added a new BSTNode into BST.
 * */
bool BST::add(const string &key, const string &preContextInput, const string &postContextInput) {
   itemCount++;
   if (root == nullptr) {
      root = new BSTNode(key, preContextInput, postContextInput);    // if root is null, create new node and set it as root.
      return true;
   } else {
      return insert(root, key, preContextInput, postContextInput);
   }
}

/* Description: overloaded friend operator to print concordance in KWIC whenever we try to print a BST
 * Parameter: outStream &outStream, const BST &tree
 * Pre-condition: will be called in the main at the end of int main() method when the tree if fully constructed
 * Post-condition: calls displayInOrder, which is a recursive function to print out content of the tree
 * Return: outStream
 * */
ostream& operator<<(ostream &outStream, const BST &binaryTree) {
   binaryTree.displayInOrder(outStream, binaryTree.root);
   return outStream;
}

/* Description: recursively searches for correct placement of new node. if it already exists, we will only add the
 * occurrence. if the key does not yet exist in the BST, we will create a new node which will add the key and its
 * occurrence at the same time
 * Parameter: BSTNode * &subTree, const string &name, const string &preContextInput, const string &postContextInput
 * Pre-condition: called from add if the tree root is not null
 * Post-condition: successfully added a new BSTNode with its respective content into the BST
 * Return: boolean true if successfully added a new BSTNode into BST
 * */
bool BST::insert(BSTNode * &subTree, const string &key, const string &preContextInput, const string &postContextInput) {
   if (subTree == nullptr) {
      subTree = new BSTNode(key, preContextInput, postContextInput);   // if key doesn't exist, create new Node
      return true;
   }

   if (subTree->key == key) {
      subTree->occurrences.add(key, preContextInput, postContextInput);   // if key already exists, add occurrence
      return false;
   }

   if (subTree->key > key) {
      return insert(subTree->left, key, preContextInput, postContextInput); // recursively checks the left subTree
   } else {
      return insert(subTree->right, key, preContextInput, postContextInput); // Recursively checks right subTree
   }
}

/* Description: recursive function that prints each BSTNode content in inOrder traversal, which will print contents
 * in alphabetical order based on keys.
 * Parameter: ostream &outStream, BSTNode *subTree
 * Pre-condition: called by << operator
 * Post-condition: will have traversed through entire tree in inOrder traversal, printing contents in KWIC format.
 * Return: N/A
 * */
void BST::displayInOrder(ostream &outStream, BSTNode *subTree) const {
   if (subTree != nullptr) {
      displayInOrder(outStream, subTree->left);
      subTree->occurrences.printOccurrences();
      displayInOrder(outStream, subTree->right);
   }
}

/* Description: clears contents of BST in a recursive traversal and deletes subTrees along the way
 * Parameter: BSTNode * &subTree
 * Pre-condition: will always be called by destructor method and pass root as parameter
 * Post-condition: called clear starting from root, which is responsible for recursively clearing the tree
 * Return: N/A
 * */
void BST::clear(BSTNode * &subTree) {
   if (subTree == nullptr) {
      return;
   }
   if (subTree->left != nullptr) {
      clear(subTree->left);
   }
   if (subTree->right != nullptr) {
      clear(subTree->right);
   }

   delete subTree;
   subTree = nullptr;
}

