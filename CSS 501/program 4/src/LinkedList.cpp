/* File name: LinkedList.cpp
 * Author name: Erika Parayno (SID #: 1425156)
 * Date: 11/27/2019
 * Description: This class a modified implementation of the LinkedList class. It contains a constructor and destructor
 * to free program from memory leaks. To add items on to the LinkedList, we have add, which adds to the end of the
 * LinkedList so that the LinkedListNodes found closer to the headPtr are occurrences that are read earlier in the text
 * (chronological order). It also has a few methods traversing through the LinkedList ot print its content
 * in KWIC format. Nested in this class is the struct LinkedListNode, which contains contents for occurrence.
 * */

#include <iostream>
#include <iomanip>
#include "LinkedList.h"

using namespace std;

/* Description: default constructor for LinkedList
 * Parameter: N/A
 * Pre-condition: will be called whenever a new node is created
 * Post-condition: creates a new LinkedList with headPtr equal to null and itemCount at zero
 * Return: N/A
 * */
LinkedList::LinkedList() {
   headPtr = nullptr;
   itemCount = 0;
}

/* Description: calls clear method, which is responsible for clearing and deleting all the nodes in LinkedList
 * Parameter: N/A
 * Pre-condition: called when the object goes out of scope on the stack
 * Post-condition: the data previously stored in the LinkedList is cleared and deleted, thus free from memory
 * Return: N/A
 * */
LinkedList::~LinkedList() {
   clear();
}

/* Description: creates a new LinkedListNode and adds that LinkedListNode to the end of the LinkedList, to preserve
 * concordance that shows word occurrences in chronological order (in the order the text is to be read). If the
 * LinkedList is empty, the LinkedListNode will set as headPtr.
 * Parameter: const string &key, const string &preContext, const string &postContext
 * Pre-condition: will be called in the insert method from the BST class if the key already exists. If not, it
 * will be called from the BSTNode constructor which is nested in the BST.h class.
 * Post-condition: A new LinkedListNode is created and added to the LinkedList
 * Return: true if successfully added.
 * */
bool LinkedList::add(const string &key, const string &preContext, const string &postContext) {

   LinkedListNode *nextNodePtr = new LinkedListNode(key, preContext, postContext);

   if (headPtr == nullptr) {  // if the linked list is empty, set head as new node.
      headPtr = nextNodePtr;
      return true;

   } else { // else, traverse through LinkedList and add the new node to end of LinkedList
      // traversing through list
      LinkedListNode *currNode = headPtr;
      while (currNode->next != nullptr) {
         currNode = currNode->next;
      }

      // adding to end of linked list
      nextNodePtr->next = currNode->next;
      currNode->next = nextNodePtr;
      itemCount++;   // increase itemCount as we added 1 new node to the LinkedList
      return true;
   }
}

/* Description: traverses through entire linked list, clearing and deleting each item on the way
 * Parameter: N/A
 * Pre-condition: called by the class destructor
 * Post-condition: the data previously stored in the LinkedList is cleared and deleted, thus free from memory
 * Return: N/A
 * */
void LinkedList::clear() {
   LinkedListNode* current = headPtr;
   while( current != 0 ) { //traverses through Linked List
      LinkedListNode* next = current->next;
      delete current;   // deletes content
      current = next;
   }
   headPtr = 0;
}

/* Description: iterates through the LinkedList and calls printThisOccurrence to print contents of each node
 * Parameter: N/A
 * Pre-condition: will be called from displayInOrder from the BST class
 * Post-condition: iterated through each LinkedListNode in LinkedList and called printThisOccurrence for all items.
 * At the end of this method, you will have printed all occurrences of one word (key).
 * Return: N/A
 * */
void LinkedList::printOccurrences() const {
   LinkedListNode *currPtr = headPtr;
   printThisOccurrence(currPtr);

   while (currPtr->next != nullptr) {  // traverses through LinkedList
      currPtr = currPtr->next;
      printThisOccurrence(currPtr);
   }
}

/* Description: takes a pointer pointing to a specific LinkedListNode in the LinkedList and prints its pre-context,
 * key, and post-context in KWIC format.
 * Parameter: LinkedListNode *currPtr
 * Pre-condition: will be called from printOccurrences
 * Post-condition: printed the LinkedListNode's pre-context, key, and post context in the correct KWIC format.
 * Return: N/A
 * */
void LinkedList::printThisOccurrence(LinkedListNode *currPtr) const {
   cout << setw(60) << right << currPtr->getPreContext();   // prints preContext
   cout << " ";
   cout << setw(15) << left << currPtr->getKey();  // prints key
   cout << setw(60) << left << currPtr->getPostContext() << endl; // prints postContext
}






