/*  ---------------------------------------------------------------------------
	ACTIONFACTORY.H
	Factory class of type Action
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	ActionFactory class: Allows us to maintain the open-closed principle. We
	can make an derived item type without having to call directly, using a 
	hashtable. 
		-- stored in a HashTable
		-- HashTable class must be in directory.
	Assumptions:
		-- Max number of actions is 1000*/

#pragma once
#include "Sell.h"
#include "Buy.h"
#include "HashTable.h"
#include "DisplayInventory.h"
#include "DisplayCustomerTransactions.h"
#include "DisplayHistory.h"

class ActionFactory {
private:
	const int numOfItems = 1000;
	HashTable* objFactory;		// for quick lookup of actions

public:

	/*	------------------------------Constructor-------------------------------
	Description: Conventional constructor.
	Pre-condition:	None.
	Post-condition:	Creates objFactory. Adds all different types of actions in 
					the hashtable. */
	ActionFactory();

	/*	------------------------------Destructor-------------------------------
	  Description:		Called to deallocate Hashable items here since it was
						created in this class.
	  Pre-condition:	No longer in scope of ActionFactory.
	  Post-condition:	Destructs class and all items it contains, including
						objFactory.*/
	~ActionFactory();

	/*	--------------------------------create-------------------------------
	Description:		Looks up new Item value pointer in the hashtable by using a 
						key char. 
	Pre-condition:		hashtable is complete with accurate data.
	Post-condition:		Derived class create method is called .*/
	Action* create(const char& ch) const;

};

