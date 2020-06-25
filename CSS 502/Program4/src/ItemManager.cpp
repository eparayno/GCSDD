/*  ---------------------------------------------------------------------------
	ITEMMANGER.CPP
	Derived Manager class of type Item
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	ItemManagerClass class: Is a aderived manager class for Items.  It contains
	a ItemFactory member to create new Items as well as a shelf, which contains
	pointers to SearchTrees. Each SearchTree represents a derived class of item.
		-- Shelves contain all items.
		-- We inherit dataFileVector, which contains all data to be process.
	assumptions:
		-- Max number of shelves is 26 (26 letters in alphabet) */
#include "ItemManager.h"

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Creates objFactory and resizes shelves.*/
ItemManager::ItemManager()
{
	objFactory = new ItemFactory;
	shelves.resize(26);
}

/*	------------------------------Destructor-------------------------------
Description: Conventional destructor.
Pre-condition:	No longer in scope of ItemManager.
Post-condition:	Deallocates objFactory and shelves.*/
ItemManager::~ItemManager()
{
	// delete each SearchTree
	for (vector<int>::size_type i = 0; i < shelves.size(); i++) {
		if (shelves[i] != nullptr) {
			delete shelves[i];
		}
	}
	
	// clear shelves
	shelves.clear();

	// clear dataFile
	dataFileVector.clear();

	// delete factory
	delete objFactory;
}

/*	----------------------------BuildByFactory-------------------------------
Description: Calls factory to make item.
Pre-condition:	Called by Store to create items.
Post-condition:	Shelves contain SearchTrees with each tree representing a
				different derived item class. All information indicated in
				dataFileVector is represented in the shelves.*/
void ItemManager::buildByFactory()
{
	char obj;	// letter to help determine which derived item class
	Item* p;

	for (int i = 0; i < dataFileVector.size(); i++) {

		// first letter is the item type
		obj = dataFileVector[i].at(0);
		dataFileVector[i].erase(0, 3);

		// Returns item pointer (derived item)
		p = objFactory->create(obj);

		// If obj was an existing item type, p will not be nullptr. 
		if (p != nullptr) {

			// set data
			p->setData(dataFileVector[i]);

			// get precedence to figure out which item comes first
			int shelfIndex = p->getPrecedence();

			// If no tree exists, create a new tree
			if (shelves[shelfIndex] == NULL) {
				shelves[shelfIndex] = new ItemSearchTree;
			}

			// add p to corresponding shelf (SearchTree)
			Comparable* compC = &*p;
			shelves[shelfIndex]->add(compC);

		}
	}
}

/*	-------------------------------getShelves-------------------------------
Description: Getter for shelves.
Pre-condition: N/A.
Post-condition:	Returns shelves. */
vector<ItemSearchTree*> ItemManager::getShelves()
{
	return shelves;
}

/*	-------------------------------getFactory-------------------------------
Description: Getter for itemFactory.
Pre-condition: N/A.
Post-condition:	Returns itemFactory. */
ItemFactory*& ItemManager::getFactory()
{
	return objFactory;
}
