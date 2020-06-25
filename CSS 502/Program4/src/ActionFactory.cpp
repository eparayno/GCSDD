/*  ---------------------------------------------------------------------------
	ACTIONFACTORY.CPP
	Factory class of type Action
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	ActionFactory class: Allows us to maintain the open-closed principle. We
	can make an derived item type without having to call directly, using a
	hashtable.
		-- stored in a HashTable
		-- HashTable class must be in directory.
	Assumptions:
		-- Max number of actions is 26*/

#include "ActionFactory.h"
#include "Hashable.h"

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Creates objFactory. Adds all different types of actions in
				the hashtable. */
ActionFactory::ActionFactory()
{
	objFactory = new HashTable;
	objFactory->buildTable(numOfItems);

	objFactory->addHashable('S' - 'A', new Sell);
	objFactory->addHashable('B' - 'A', new Buy);
	objFactory->addHashable('D' - 'A', new DisplayInventory);
	objFactory->addHashable('C' - 'A', new DisplayCustomerTransactions);
	objFactory->addHashable('H' - 'A', new DisplayHistory);

}

/*	------------------------------Destructor-------------------------------
  Description:		Called to deallocate Hashable items here since it was 
					created in this class.
  Pre-condition:	No longer in scope of ActionFactory.
  Post-condition:	Destructs class and all items it contains, including 
					objFactory.*/
ActionFactory::~ActionFactory()
{
	delete objFactory->getHashable('S' - 'A');
	delete objFactory->getHashable('D' - 'A');
	delete objFactory->getHashable('C' - 'A');
	delete objFactory->getHashable('H' - 'A');

	delete objFactory;
}

/*	--------------------------------create-------------------------------
Description:		Looks up new Item value pointer in the hashtable by using a
					key char.
Pre-condition:		hashtable is complete with accurate data.
Post-condition:		Derived class create method is called .*/
Action* ActionFactory::create(const char& ch) const
{
	if (objFactory->getHashable(ch - 'A') == NULL) {
		// if such action does not exist, return nullptr
		return nullptr;
	}
	else {
		Hashable* hashable = objFactory->getHashable(ch - 'A');
		Action* action = dynamic_cast<Action*>(hashable);
		return action->create();
	}
}
