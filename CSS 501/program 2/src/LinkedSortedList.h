// File Name: ListSortedList.h
// Author name: Erika Parayno (SID: 1425156)
// Date: October 23, 2019
// Description: From Carrano and Henry's Data Abstraction and Problem Solving with C++ (6th edition). Some methods were
// left unimplemented as it was not needed to reach the goal of the assignment. A new method was added, the merge
// sort list, which takes every value from l1 and l2 and adds it to a new sorted list, using merge sorting.
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 12-2

/** ADT sorted list: Link-based implementation.
 @file LinkedSortedList.h */

#ifndef _LINKED_SORTED_LIST
#define _LINKED_SORTED_LIST

#include "SortedListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class LinkedSortedList : public SortedListInterface<ItemType>
{
private:
    Node<ItemType>* headPtr; // Pointer to first node in the chain
    int itemCount;           // Current count of list items

    // Locates the node that is before the node that should or does
    // contain the given entry.
    // @param anEntry  The entry to find.
    // @return  Either a pointer to the node before the node that contains
    //    or should contain the given entry, or nullptr if no prior node exists.
    Node<ItemType>* getNodeBefore(const ItemType& anEntry) const;

    // Locates the node at a given position within the chain.
    Node<ItemType>* getNodeAt(int position) const;

       // Returns a pointer to a copy of the chain to which origChainPtr points.
    Node<ItemType>* copyChain(const Node<ItemType>* origChainPtr);

public:
    LinkedSortedList();
    LinkedSortedList(const LinkedSortedList<ItemType>& aList);

    explicit LinkedSortedList(Node<ItemType> *headPtr);

    virtual ~LinkedSortedList();

    void insertSorted(const ItemType& newEntry);
    bool removeSorted(const ItemType& anEntry);
    int getPosition(const ItemType& newEntry) const;

    // The following methods are the same as given in ListInterface:
    bool isEmpty() const;
    int getLength() const;
    bool remove(int position);
    void clear();
    ItemType getEntry(int position) const throw(PrecondViolatedExcep);

    // Merge sorted list
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
    LinkedSortedList<ItemType> mergeSortedList(LinkedSortedList<ItemType>& list2) const;

}; // end LinkedSortedList

#include "LinkedSortedList.cpp"
#endif