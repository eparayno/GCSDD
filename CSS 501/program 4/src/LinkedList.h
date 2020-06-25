/* File name: LinkedList.h
 * Author name: Erika Parayno (SID #: 1425156)
 * Date: 11/27/2019
 * Description: This class a modified implementation of the LinkedList class. It contains a constructor and destructor
 * to free program from memory leaks. To add items on to the LinkedList, we have add, which adds to the end of the
 * LinkedList so that the LinkedListNodes found closer to the headPtr are occurrences that are read earlier in the text
 * (chronological order). It also has a few methods traversing through the LinkedList ot print its content
 * in KWIC format. Nested in this class is the struct LinkedListNode, which contains contents for occurrence. Is the
 * header file for methods in LinkedList.cpp
 * */

#include <string>

#ifndef CONCORDANCE_LINKEDLIST_H
#define CONCORDANCE_LINKEDLIST_H

using namespace std;

class LinkedList
{
private:
   /* File name: LinkedListNode (struct)
    * Author name: Erika Parayno (SID #: 1425156)
    * Date: 11/27/2019
    * Description: This struct will be the structure contained in LinkedLists. They are responsible for holding the
    * following string variables: pre-context, key, and post-context. The constructor will require all three as
    * parameters. The only other methods included are getter methods, which are called to print the concordance in
    * KWIC format.
    * */
   struct LinkedListNode {
      LinkedListNode *next = nullptr;
      string preContext;
      string key;
      string postContext;

      /* Description: the only LinkedListNode constructor used for this program. Takes the key, pre-context, and post-
       * context and creates a new LinkedListNode and sets all its variables.
       * Parameter: const string &keyInput, const string &preContextInput, const string &postContextInput
       * Pre-condition: will be called from the add function in LinkedList class
       * Post-condition: creates a new node which will be later added to the end of LinkedList.
       * Return: N/A
       * */
      LinkedListNode(const string &keyInput, const string &preContextInput, const string &postContextInput) {
         preContext = preContextInput;
         key = keyInput;
         postContext = postContextInput;
      }

      /* Description: getter for preContext
       * Parameter: N/A
       * Pre-condition: will be called when printing the pre-context for the concordance in KWIC format
       * Post-condition: gets and returns string preContext
       * Return: string preContext
       * */
      const string &getPreContext() const {
         return preContext;
      }

      /* Description: getter for postContext
       * Parameter: N/A
       * Pre-condition: will be called when printing the post-context for the concordance in KWIC format
       * Post-condition: gets and returns string postContext
       * Return: string postContext
       * */
      const string &getPostContext() const {
         return postContext;
      }

      /* Description: getter for key
       * Parameter: N/A
       * Pre-condition: will be called when printing the key for the concordance in KWIC format
       * Post-condition: gets and returns string key
       * Return: string key
       * */
      const string &getKey() const {
         return key;
      }
   };

   LinkedListNode* headPtr;
   int itemCount = 0;

public:

   /* Description: default constructor for LinkedList
    * Parameter: N/A
    * Pre-condition: will be called whenever a new node is created
    * Post-condition: creates a new LinkedList with headPtr equal to null and itemCount at zero
    * Return: N/A
    * */
   LinkedList();

   /* Description: calls clear method, which is responsible for clearing and deleting all the nodes in LinkedList
    * Parameter: N/A
    * Pre-condition: called when the object goes out of scope on the stack
    * Post-condition: the data previously stored in the LinkedList is cleared and deleted, thus free from memory
    * Return: N/A
    * */
   ~LinkedList();

   /* Description: creates a new LinkedListNode and adds that LinkedListNode to the end of the LinkedList, to preserve
    * concordance that shows word occurrences in chronological order (in the order the text is to be read). If the
    * LinkedList is empty, the LinkedListNode will set as headPtr.
    * Parameter: const string &key, const string &preContext, const string &postContext
    * Pre-condition: will be called in the insert method from the BST class if the key already exists. If not, it
    * will be called from the BSTNode constructor which is nested in the BST.h class.
    * Post-condition: A new LinkedListNode is created and added to the LinkedList
    * Return: true if successfully added.
    * */
   bool add(const string &key, const string &preContext, const string &postContext);

   /* Description: traverses through entire linked list, clearing and deleting each item on the way
    * Parameter: N/A
    * Pre-condition: called by the class destructor
    * Post-condition: the data previously stored in the LinkedList is cleared and deleted, thus free from memory
    * Return: N/A
    * */
   void clear();

   /* Description: iterates through the LinkedList and calls printThisOccurrence to print contents of each node
    * Parameter: N/A
    * Pre-condition: will be called from displayInOrder from the BST class
    * Post-condition: iterated through each LinkedListNode in LinkedList and called printThisOccurrence for all items.
    * At the end of this method, you will have printed all occurrences of one word (key).
    * Return: N/A
    * */
   void printOccurrences() const;

   /* Description: takes a pointer pointing to a specific LinkedListNode in the LinkedList and prints its pre-context,
    * key, and post-context in KWIC format.
    * Parameter: LinkedListNode *currPtr
    * Pre-condition: will be called from printOccurrences
    * Post-condition: printed the LinkedListNode's pre-context, key, and post context in the correct KWIC format.
    * Return: N/A
    * */
   void printThisOccurrence(LinkedListNode *currPtr) const;

}; // end LinkedList

#endif //CONCORDANCE_LINKEDLIST_H
