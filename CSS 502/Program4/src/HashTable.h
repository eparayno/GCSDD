/*  ---------------------------------------------------------------------------
	HASHTABLE.H
	Hashtable for all things hashable
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	Hashable class: Simple implementaiton of HashTable. Vector carries HashLists,
	Which contains HashListNodes.
		-- Vector implementation
		-- Linked list for collisions
		-- allows for retrieval and insertion of Comparable* item
	Assumptions:
		-- Will be size 1000 unless otherwise stated in build tree
		-- uses prime number 769 for hashing */

#pragma once
#include <vector>
#include "Hashable.h"

class HashTable {
	static const int SIZE = 1000; // will resize as needed
	static const int hashNumber = 769;  // prime number best for hashing

private:

	struct HashLinkedListNode {
		int key;
		Hashable* hashable;
		HashLinkedListNode* next;
	};

	struct HashLinkedList {
		HashLinkedListNode* head;
	};

	vector<HashLinkedList> table;

public:

	/*	------------------------------Constructor-------------------------------
	Description: Conventional constructor.
	Pre-condition:	None.
	Post-condition:	Creates HashTable.*/
	HashTable();

	/*	------------------------------Destructor-------------------------------
	  Description: Conventional destructor.
	  Pre-condition:  No longer in scope.
	  Post-condition: Destructs class and all items it contains, including table.*/
	~HashTable();

	/*	------------------------------Destructor-------------------------------
	  Description: Resizer.
	  Pre-condition:  N/A
	  Post-condition: Takes parameter and adjust table to that size.*/
	void buildTable(const int& size);

	/*	------------------------------getHashable-------------------------------
	  Description: Performs hash to find index. If not equal, then it will
	  search that index's linkedlist.
	  Pre-condition:  N/A
	  Post-condition: Returns hashable if found*/
	Hashable* getHashable(const int& key);

	/*	------------------------------addHashable-------------------------------
	  Description: Attempts to add hashable into the HashTable
	  Pre-condition:  N/A
	  Post-condition: Returns true if successful*/
	bool addHashable(const int& key, Hashable* hashable);

};