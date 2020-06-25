//--------------------------------------------------------------------
// CLASS: HEAP.H
// Declaration and definition of the template Heap class
// Author: Olson (borrowing from a previous edition of Carrano/Henry)
// Edited by: Erika Parayno (SID # 1425156)
//--------------------------------------------------------------------
// Heap class:
//	Implements a priority queue with the following methods:
//		insert, deleteMin, findMin, heapify. Added Default constructor,
//      copy constructor, operator=, and destructor. 
//  The heap is stored in a vector (see the CSS 502 lecture notes)
//  Assumptions:
//	 Can only store data for which operator< exists
//	 (hence the Comparable type variable)
//--------------------------------------------------------------------

#pragma once
#include <vector>
#include <iostream>

using namespace std;

template <typename Comparable>
class Heap {
public:

     ///-------------------------Default_Constructor---------------------------
    /*  Definition: Default constructor for Heap class
        Precondition: None
        Post Condition: Creates Heap constructor with an empty vector of
            Node* and initializes numElements at 0. */
    Heap() {
        // create dummy node
        Comparable* c = nullptr;
        items.push_back(c);
    }
    
    //-------------------------------Constructor-------------------------------
    /*  Definition: Constructor that takes an array of Comparable pointers and
                constructs a Heap using the (supplied) heapify method.
        Precondition: None.
        Post Condition: Creates a heap from array data*/
    Heap(Comparable** array, int count) {
        for (int i = 0; i < count; i++) {
            Comparable* heapNodePtr = array[i];
            insert(heapNodePtr);
            heapify();
        }

    }

    //-------------------------------Destructor--------------------------------
    /*  Definition: Destructor that deallocates and removes data that stored
            and owned by Heap.
        Precondition: Will be called once the heap is no longer in the scope
        Post Condition: Heap and any data in the heap should be deallocated
                and removed from memory. */
    virtual ~Heap() {
        for (int i = 0; i < size(); i++) {
            delete items[i];
        }

        items.clear();
        numElements = NULL;
    }

    //-------------------------------operator=--------------------------------
    /*  Definition: Assignment operator that clears this heap and performs a 
            deep copy of source heap that is passed as a parameter.
        Precondition: Must pass non-empty sourceHeap.
        Post Condition: Returns Heap w/ copied values of source Heap but 
            containing different addresses (deep copy)*/
    Heap& operator=(const Heap& sourceHeap) {
        if (items = sourceHeap.items) {
	        return *this;
	    }

        items.clear();
        copyHelper(sourceHeap);
	    return this;
    }

    //-----------------------------Copy_Constructor----------------------------
    /*  Definition: Copy constructor that performs a deep copy of source
            Heap that is passed as a parameter.
        Precondition: Must pass non-empty sourceHeap.
        Post Condition: Returns Heap w/ copied values of source Heap but
            containing different addresses (deep copy). */
    Heap(const Heap& sourceHeap) {
        copyHelper(sourceHeap);
    }

    //-----------------------------Copy_Constructor----------------------------
    /*  Definition: Takes advantage of vector properties of being able to 
            perform deep copy of trees without implementing recursion.
            Will copy the first few nodes in the sourceHeap.
        Precondition: Must pass non-empty sourceHeap.
        Post Condition: Returns Heap w/ copied values of source Heap but
            containing different addresses (deep copy). */
    void copyHelper(const Heap& sourceHeap) {
        for (int i = 0; i < sourceHeap.size(); i++) {
            Comparable* copyHeapPtr = new Comparable(*sourceHeap.items[i]);
            items.push_back(copyHeapPtr);   // adds into vector
            numElements++;                  //increment numElements
            heapify();
        }
    }

   
    //------------------------------------------------------------------------
    // insert - adds a single item to the heap
    // Preconditions: the initial heap has sufficient memory allocated
    //					and satisfies the heap order property
    // Postconditions: inserts the item into the queue, such that a new
    //					heap is created containing the union of the elements
    void insert(Comparable* c) {
        if (c == NULL) return;

        // Add item in position 0 (dummy position) to prevent percolating up from root
        if (items.size() < 1) items.push_back(c);
        else items[0] = c;

        // Ensure we have enough space
        numElements++;
        while ((int)items.size() <= numElements)
            items.push_back(nullptr);

        // Percolate up
        int position = numElements;
        while (*c < *items[position / 2]) {
            items[position] = items[position / 2];
            position = position / 2;
        }
        items[position] = c;
    }

    //------------------------------------------------------------------------
    // findMin - returns a const pointer to the minimum value in the heap
    // Preconditions: items[0] exists if numElements is larger than zero
    // Postconditions: Returns nullptr if the heap is empty, otherwise returns
    //	the item at the root of the heap (presumably the minimum priority).
    const Comparable* findMin() const {
        if (numElements <= 0) return nullptr;
        else return items[1];
    }


    //------------------------------------------------------------------------
    // deleteMin - delete the minimum and return a pointer to it
    // Preconditions: items[0] exists if numElements is larger than zero
    // Postconditions: Returns nullptr if the heap is empty, otherwise returns
    //	the item at the root of the heap (presumably the minimum priority).
    //  That element is deleted from the heap and the heap order property is
    //  restored.
    Comparable* deleteMin() {
        if (numElements == 0) return nullptr;

        // Give memory back to user
        Comparable* toReturn = items[1];
        items[1] = items[numElements];
        numElements--;

        percolateDown(1);
        return toReturn;
    }

    //------------------------------------------------------------------------
    // heapify - modifies any set of data into a heap
    // Preconditions: items has been allocated space for numElements pointers
    // Postconditions: The items stored form a heap
    void heapify() {
        for (int i = numElements / 2; i > 0; i--)
            percolateDown(i);
    }

    //------------------------------------------------------------------------
    // size
    // Preconditions: none
    // Postconditions: returns the size of the heap
    int size() const {
        return numElements;
    }

    //------------------------------------------------------------------------
    // isEmpty
    // Preconditions: none
    // Postconditions: returns whether the heap is empty (zero elements)
    int isEmpty() const {
        return numElements == 0;
    }

private:

    //------------------------------------------------------------------------
    // percolateDown - used to restore the heap order property after deleteMin
    // Preconditions: Both subtrees of the root are heaps
    // Postconditions: Restores the heap order property to shifting the root
    //  down until it reaches an appropriate node
    void percolateDown(int position) {
        int child = position * 2;
        if (child > numElements) return;
        if (child != numElements && *items[child] > * items[child + 1]) child++;
        if (*items[child] < *items[position]) {
            swap(items[child], items[position]);
            percolateDown(child);
        }
    }

    int numElements = 0;			// Number of elements in the heap
    vector <Comparable*> items;	    // The elements in the heap
};
