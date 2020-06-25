/*  ---------------------------------------------------------------------------
	ITEMFACTORY.CPP
	Factory class of type Item
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	ItemFactory class: Allows us to maintain the open-closed principle. We
	can make an derived item type without having to call directly, using a
	hashtable.
		-- stored in a HashTable
		-- HashTable class must be in directory.
	Assumptions:
		-- Max number of items is 26*/

#include "ItemFactory.h"

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Creates objFactory. Adds all different types of items in
				the hashtable. */
ItemFactory::ItemFactory()
{
	objFactory = new HashTable;
	objFactory->buildTable(numOfItems);

	objFactory->addHashable('M' - 'A', new Coin);
	objFactory->addHashable('C' - 'A', new Comic);
	objFactory->addHashable('S' - 'A', new SportsCard);
}


/*	------------------------------Destructor-------------------------------
  Description:		Called to deallocate Hashable items here since it was
					created in this class.
  Pre-condition:	No longer in scope of ItemFactory.
  Post-condition:	Destructs class and all items it contains, including
					objFactory.*/
ItemFactory::~ItemFactory()
{
	delete objFactory->getHashable('M' - 'A');
	delete objFactory->getHashable('C' - 'A');
	delete objFactory->getHashable('S' - 'A');

	delete objFactory;
}

/*	--------------------------------create-------------------------------
Description:		Looks up new Action value pointer in the hashtable by using a
					key char.
Pre-condition:		hashtable is complete with accurate data.
Post-condition:		Derived class create method is called .*/
Item* ItemFactory::create(const char& ch) const
{
	if (objFactory->getHashable(ch - 'A') == NULL) {
		// if no such item exists, return nullptr
		return nullptr;
	}
	else {
		Hashable* hashable = objFactory->getHashable(ch - 'A');
		Item* item = dynamic_cast<Item*>(hashable);
		return item->create();
	}
}
