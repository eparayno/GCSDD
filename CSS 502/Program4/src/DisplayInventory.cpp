/*  ---------------------------------------------------------------------------
	DISPLAYINVENTORY.CPP
	Derived class DisplayInventory with parent class Action
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	DisplayInventory class: Derived class of Action.
		-- outputs entire inventory of store including count of each item*/

#include "DisplayInventory.h"
#include "ItemSearchTree.h"
#include "Store.h"

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Creates DisplayInventory.*/
DisplayInventory::DisplayInventory()
{
}

/*	------------------------------Destructor-------------------------------
  Description: Conventional destructor.
  Pre-condition: No longer in scope.
  Post-condition: Destructs class.*/
DisplayInventory::~DisplayInventory()
{
}

/*	--------------------------------create---------------------------------
Description: Allows for open ended principle
Pre-condition: Called by ActionFactory.
Post-condition: Returns Action pointer. */
Action* DisplayInventory::create() const
{
	return new DisplayInventory;
}

/*	--------------------------------runAction---------------------------------
Description: Uses data in Store to print inventory.
Pre-condition: Performed in factory.
Post-condition: Prints appropriately */
void DisplayInventory::runAction(Store& store, const string& data)
{
	cout << "DISPLAY INVENTORY:________________________________________________________________________________________" << endl;
	int numOfTrees = store.getItemDB()->getShelves().size();
	for (int i = 0; i < numOfTrees; i++) {
		if (store.getItemDB()->getShelves()[i] != NULL) {
			ItemSearchTree* tree = store.getItemDB()->getShelves()[i];
			cout << *tree;
		}
	}
}

/*	-------------------------------print---------------------------------
Description: Helper print method. Overrides base class so that DisplayInventory
can print its items unique to its containing data.
Pre-condition:	None.
Post-condition:  Returns formatted ostream */
ostream& DisplayInventory::print(ostream& out) const
{
	return out;
}
