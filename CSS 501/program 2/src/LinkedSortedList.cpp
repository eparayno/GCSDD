// File Name: ListSortedList.cpp
// Author name: Erika Parayno (SID: 1425156)
// Date: October 23, 2019
// Description: From Carrano and Henry's Data Abstraction and Problem Solving with C++ (6th edition). Some methods were
// left unimplemented as it was not needed to reach the goal of the assignment. A new method was added, the merge
// sort list, which takes every value from l1 and l2 and adds it to a new sorted list, using merge sorting.
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Implementation file for the class LinkedSortedList.
 @file LinkedSortedList.cpp */

#include "LinkedSortedList.h"  // Header file
#include "PrecondViolatedExcep.h"
#include <cassert>
#include <iostream>

using namespace std;

// Private methods:
template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const
{
   Node<ItemType>* curPtr = headPtr;
   Node<ItemType>* prevPtr = nullptr;

   while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
   {
      prevPtr = curPtr;
      curPtr = curPtr->getNext();
   } // end while

   return prevPtr;
} // end getNodeBefore

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeAt(int position) const {
   assert(position > 0 && position <= itemCount);
   // Count from the beginning of the chain
   Node<ItemType> *curPtr = headPtr;
   for (int skipNodePtr = 1; skipNodePtr < position; skipNodePtr++) {
      curPtr = curPtr->getNext();
   }
   return curPtr;
} //end getNodeAt

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::copyChain(const Node<ItemType>* origChainPtr)
{
   Node<ItemType>* copiedChainPtr;
   if (origChainPtr == nullptr)
   {
      copiedChainPtr = nullptr;
      itemCount = 0;
   }
   else
   {
      // Build new chain from given one
      Node<ItemType>* copiedChainPtr = new Node<ItemType>(origChainPtr->getItem());
      copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
      itemCount++;
   }  // end if

   return copiedChainPtr;
}  // end copyChain


// Public methods
template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList() {
   headPtr = nullptr;
   itemCount = 0;
} // end default constructor

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(const LinkedSortedList<ItemType>& aList)
{
   headPtr = copyChain(aList.headPtr);
   itemCount = aList.itemCount;
}  // end copy constructor

template<class ItemType>
LinkedSortedList<ItemType>::~LinkedSortedList() {
   clear();
}; //destructor

template<class ItemType>
void LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry)
{
   Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
   Node<ItemType>* prevPtr = getNodeBefore(newEntry);

   if (isEmpty() || (prevPtr == nullptr)) // Add at beginning
   {
      newNodePtr->setNext(headPtr);
      headPtr = newNodePtr;
   }
   else // Add after node before
   {
      Node<ItemType>* aftPtr = prevPtr->getNext();
      newNodePtr->setPrev(prevPtr); // sets prev pointer
      newNodePtr->setNext(aftPtr);  // sets next pointer
      prevPtr->setNext(newNodePtr);
   } // end if
   itemCount++;
} // end insertSorted

template<class ItemType>
bool LinkedSortedList<ItemType>::removeSorted(const ItemType &anEntry) {
   return false; // not implemented, functionality not needed.
} // needs to be edited

template<class ItemType>
int LinkedSortedList<ItemType>::getPosition(const ItemType &newEntry) const {
   return 0; // not implemented, functionality not needed.
}

template<class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const {
   return itemCount == 0;; // checks if empty
}

template<class ItemType>
int LinkedSortedList<ItemType>::getLength() const {
   return itemCount; // returns itemCount
}

template<class ItemType>
bool LinkedSortedList<ItemType>::remove(int position) {
   Node<ItemType>* entryNodePtr = getNodeAt(position);
   bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
   if (canRemoveItem)
   {
      // Copy data from first node to located node
      entryNodePtr->setItem(headPtr->getItem());

      // Delete first node
      Node<ItemType>* nodeToDeletePtr = headPtr;
      headPtr = headPtr->getNext();

      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;

      itemCount--;
   } // end if
   return canRemoveItem;
} // end of remove method, implementation from warm-up file LinkedBag.cpp

template<class ItemType>
void LinkedSortedList<ItemType>::clear() {
   Node<ItemType>* nodeToDeletePtr = headPtr;
   while (headPtr != nullptr) {
      headPtr = headPtr->getNext();

      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;

      nodeToDeletePtr = headPtr;
   }
} //end of clear method, implementation from warm-up file LinkedBag.cpp

template<class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep) {
   if ((position > 0) && (position <= itemCount)) // It will try to get the entry if position exists.
   {
      Node<int>* nodePtr = getNodeAt(position); // Node pointer created, pointing at node at specified position
      return nodePtr->getItem(); // Returns that node
   }
   else
   {
      std::string message = "You have an error. The position does not exist."; // Error message
      throw(PrecondViolatedExcep(message));
   }  // end if
}

/**
     * Description: This method takes two sorted lists, that can vary in lengths. It creates a new list and traverses
     * through each of two original lists. It compares the values of the each node at a given list, whichever list has
     * the lower value (if it exists), will be added to the new list. Thus, the new list will be a combination of all
     * values seen in the two original lists and must be in ascending order.
     * Parameter: Takes in LinkedSortedList<ItemType>list2 which will be compared to list1. Both are LinkedSortedList<ItemType>.
     * Pre-condition: mergeSortedList is called on list1 with list2 passed as a parameter.
     * Post-condition: We traverse through list1 and list2 until each value was evaluated. During every evaluation, we
     * compare the values to see which one is of lower value and that is inserted into the newly constructed linked list.
     * At the end of the method, we have a new list that with length the sum of the two original lists. Neither original
     * is manipulated at anytime during the process.
     * Return: Returns a LinkedSortedList.
     */
template<class ItemType>
LinkedSortedList<ItemType> LinkedSortedList<ItemType>::mergeSortedList(LinkedSortedList<ItemType>& list2) const {
   Node<ItemType>* list1Ptr = headPtr;                // creates a new pointer pointing to start of list1
   Node<ItemType>* list2Ptr = list2.headPtr;          // creates a new pointer pointing to start of list2
   LinkedSortedList<ItemType> newSortedList;          // creates the new LinkedSortedList to be returned later
   Node<ItemType>* newListPtr = new Node<ItemType>(); // creates a pointer
   cout << "Your new sorted list: ";
   //newSortedList.headPtr = newListPtr;

   if (list1Ptr == nullptr && list2Ptr == nullptr) {  // Returns empty list if both list1 and list2 are empty
      return newSortedList;
   }

   while ((list1Ptr != nullptr) || (list2Ptr != nullptr) ) { // While one of either list1 or list2 is not empty
      int list1curVal;
      int list2curVal;

      if (list1Ptr != nullptr) {
         list1curVal = list1Ptr->getItem(); // Will only try to get list1's item if its not null
      }

      if (list2Ptr != nullptr) {
         list2curVal = list2Ptr->getItem(); // Will only try to get list1's item if its not null
      }

      if (newSortedList.itemCount == 0 ) { // when adding the first value
         if ((list1curVal <= list2curVal || (list2Ptr == nullptr)) && (list1Ptr != NULL)) { //performs l1 and l2 value comparison
            newListPtr->setItem(list1Ptr->getItem()); //We are setting the value since we are at the head
            list1Ptr = list1Ptr->getNext();
         } else {
            newListPtr->setItem(list2Ptr->getItem());  //We are setting the value since we are at the head
            list2Ptr = list2Ptr->getNext();
         }
         newSortedList.headPtr = newListPtr; // sets newSortedList's headPointer to newListPtr
      } else { // when adding to the rest of list
         if ((list1curVal <= list2curVal || (list2Ptr == nullptr)) && (list1Ptr != NULL)) { //performs l1 and l2 value comparison.
            newListPtr->setNext(list1Ptr);
            list1Ptr = list1Ptr->getNext();
         } else {
            newListPtr->setNext(list2Ptr);
            list2Ptr = list2Ptr->getNext();
         }
         newListPtr = newListPtr->getNext(); // getNextPointer
      }
      newSortedList.itemCount++; // increase itemCount
      cout << newListPtr->getItem() << " "; // to print on cout
   }
   //while loop ends once every value in both list1 and list2 have been visited

   return newSortedList;
}

