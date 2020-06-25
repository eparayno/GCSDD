/* File name: BST.h
 * Author name: Erika Parayno (SID #: 1425156)
 * Date: 11/27/2019
 * Description: This class is a modified implementation of the BinarySearchTree class. For the most part, it utilizes
 * recursive algorithms to traverse a tree. More specifically, we are using inOrder, to insure that we are printing
 * out the keys in alphabetical order. This class also contains constructors and destructor, which clears and deletes
 * the structure whenever it is out of scope, which should ensure that we are free of memory leaks. This class
 * is the header file for BST.cpp.
 * */

#ifndef CONCORDANCE_BST_H
#define CONCORDANCE_BST_H

#pragma
#include <string>
#include <iostream>
#include <algorithm>

#include "LinkedList.h"

using namespace std;

class BST {
private:
   /* File name: BSTNode (struct)
    * Author name: Erika Parayno (SID #: 1425156)
    * Date: 11/27/2019
    * Description: this class is a relatively simple class that contains a constructor. The constructor requires
    * pre-context, key, and post-context as parameters. It sets the key and adds the occurrence onto the LinkedList.
    * */
   struct BSTNode {
      string key;
      LinkedList occurrences;
      BSTNode *left = nullptr;
      BSTNode *right = nullptr;

      /* Description: constructor that takes in contents and sets class variables to those parameters
       * Parameter: const string &keyInput, const string &preContextInput, const string &postContextInput
       * Pre-condition: called from insert method in the BST class, will only be called if it couldn't find an
       * already existing node for that key.
       * Post-condition: node created with key set and added occurrence
       * Return: N/A
       * */
      BSTNode(const string &keyInput, const string &preContextInput, const string &postContextInput) {
         key = keyInput;
         occurrences.add(key, preContextInput, postContextInput);
      };

   };

   BSTNode *root = nullptr;
   int itemCount = 0;

   /* Description: recursively searches for correct placement of new node. if it already exists, we will only add the
    * occurrence. if the key does not yet exist in the BST, we will create a new node which will add the key and its
    * occurrence at the same time
    * Parameter: BSTNode * &subTree, const string &name, const string &preContextInput, const string &postContextInput
    * Pre-condition: called from add if the tree root is not null
    * Post-condition: successfully added a new BSTNode with its respective content into the BST
    * Return: boolean true if successfully added a new BSTNode into BST
    * */
   bool insert(BSTNode * &subTree, const string &key, const string &preContextInput, const string &postContextInput);

   /* Description: recursive function that prints each BSTNode content in inOrder traversal, which will print contents
    * in alphabetical order based on keys.
    * Parameter: ostream &outStream, BSTNode *subTree
    * Pre-condition: called by << operator
    * Post-condition: will have traversed through entire tree in inOrder traversal, printing contents in KWIC format.
    * Return: N/A
    * */
   void displayInOrder(ostream &outStream, BSTNode *subTree) const;

   /* Description: clears contents of BST in a recursive traversal and deletes subTrees along the way
    * Parameter: BSTNode * &subTree
    * Pre-condition: will always be called by destructor method and pass root as parameter
    * Post-condition: called clear starting from root, which is responsible for recursively clearing the tree
    * Return: N/A
    * */
   void clear(BSTNode * &subTree);

public:
   /* Description: default constructor
    * Parameter: N/A
    * Pre-condition: called in main
    * Post-condition: creates a new BST with root equal to nullPtr and itemCount at 0
    * Return: N/A
    * */
   BST();

   /* Description: default destructor
    * Parameter: N/A
    * Pre-condition: called when the object goes out of scope on the stack
    * Post-condition: called clear starting from root, which is responsible for recursively clearing the tree
    * Return: N/A
    * */
   ~BST();

   /* Description: this method checks if the tree is empty and if it is, we add a new node and set it to root. Otherwise,
    * we will call the insert method, which will recursively find the correct placement of the key, so that it preserves
    * order of the BST.
    * Parameter: const string &key, const string &preContextInput, const string &postContextInput
    * Pre-condition: called from main class in the addContentsToTree method.
    * Post-condition: successfully added a new BSTNode with its respective contents in the BST.
    * Return: boolean true if it successfully added a new BSTNode into BST.
    * */
   bool add(const string &key, const string &preContextInput, const string &postContextInput);

   /* Description: overloaded friend operator to print concordance in KWIC whenever we try to print a BST
    * Parameter: outStream &outStream, const BST &tree
    * Pre-condition: will be called in the main at the end of int main() method when the tree if fully constructed
    * Post-condition: calls displayInOrder, which is a recursive function to print out content of the tree
    * Return: outStream
    * */
   friend ostream& operator<<(ostream &outStream, const BST &binaryTree);

};
#endif //CONCORDANCE_BST_H
