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

#pragma once
#include "Coin.h"
#include "Comic.h"
#include "SportsCard.h"
#include "HashTable.h"

class ItemFactory {

public:
	/*	------------------------------Constructor-------------------------------
	Description: Conventional constructor.
	Pre-condition:	None.
	Post-condition:	Creates objFactory. Adds all different types of items in
					the hashtable. */
	ItemFactory();

	/*	------------------------------Destructor-------------------------------
	  Description:		Called to deallocate Hashable items here since it was
						created in this class.
	  Pre-condition:	No longer in scope of ItemFactory.
	  Post-condition:	Destructs class and all items it contains, including
						objFactory.*/
	~ItemFactory();

	/*	--------------------------------create-------------------------------
	Description:		Looks up new Action value pointer in the hashtable by using a
						key char.
	Pre-condition:		hashtable is complete with accurate data.
	Post-condition:		Derived class create method is called .*/
	Item* create(const char& ch) const;

private:

	const int numOfItems = 26;	
	HashTable* objFactory;

};

