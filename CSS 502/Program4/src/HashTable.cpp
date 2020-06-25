/*  ---------------------------------------------------------------------------
	HASHTABLE.CPP
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

#include "HashTable.h"
#include <cstddef>
#include <vector>

using namespace std;

struct HashEntry;

/*	------------------------------Destructor-------------------------------
  Description: Resizer.
  Pre-condition:  N/A
  Post-condition: Takes parameter and adjust table to that size.*/
void HashTable::buildTable(const int& size)
{
	table.resize(size);
}

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Creates HashTable.*/
HashTable::HashTable() {}

/*	------------------------------Destructor-------------------------------
  Description: Conventional destructor.
  Pre-condition:  No longer in scope.
  Post-condition: Destructs class and all items it contains, including table.*/
HashTable::~HashTable()
{
	for (int i = 0; i < table.size(); i++) {
		HashLinkedListNode* currHead = table[i].head;
		if (currHead != NULL) {
			HashLinkedListNode* curr = currHead;
			while (currHead != NULL) {
				currHead = currHead->next;
				if (curr != NULL) {
					delete curr;
				}
				curr = NULL;
				curr = currHead;
			}
		}
	}
}

/*	------------------------------getHashable-------------------------------
  Description: Performs hash to find index. If not equal, then it will
  search that index's linkedlist.
  Pre-condition:  N/A
  Post-condition: Returns hashable if found*/
Hashable* HashTable::getHashable(const int& key)
{
	if (table[key % hashNumber].head == NULL) {
		return nullptr;
	}
	else {
		HashLinkedListNode* current = table[key % hashNumber].head;
		while (current != NULL) {
			if (key == current->key) {
				return current->hashable;
			}
			current = current->next;
		}
	}
	return nullptr;
}

/*	------------------------------addHashable-------------------------------
  Description: Attempts to add hashable into the HashTable
  Pre-condition:  N/A
  Post-condition: Returns true if successful*/
bool HashTable::addHashable(const int& key, Hashable* comparable)
{
	HashLinkedListNode* node = new HashLinkedListNode;
	node->hashable = comparable;
	node->key = key;
	node->next = NULL;

	if (table[key % hashNumber].head == NULL) {
		node->next = table[key % hashNumber].head;
		table[key % hashNumber].head = node;
	}
	else {
		HashLinkedListNode* current = table[key % hashNumber].head;
		while (current->next != NULL) {
			if (key == current->key) {
				delete node->hashable;
				delete node;
				node = NULL;
				return false;
			}
			current = current->next;
		}
		current->next = node;
	}
	return true;
}
