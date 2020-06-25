/*  ---------------------------------------------------------------------------
	DISPLAYINVENTORY.H
	Derived class DisplayInventory with parent class Action
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	DisplayInventory class: Derived class of Action.
		-- outputs entire inventory of store including count of each item*/

#pragma once
#include <string>
#include "Customer.h"

class Store;
class DisplayInventory : public Action
{
public:
	/*	------------------------------Constructor-------------------------------
	Description: Conventional constructor.
	Pre-condition:	None.
	Post-condition:	Creates DisplayInventory.*/
	DisplayInventory();

	/*	------------------------------Destructor-------------------------------
	  Description: Conventional destructor.
	  Pre-condition: No longer in scope.
	  Post-condition: Destructs class.*/
	~DisplayInventory();

	/*	--------------------------------create---------------------------------
	Description: Allows for open ended principle
	Pre-condition: Called by ActionFactory.
	Post-condition: Returns Action pointer. */
	virtual Action* create() const;

	/*	--------------------------------runAction---------------------------------
	Description: Uses data in Store to print inventory.
	Pre-condition: Called in factory.
	Post-condition: Prints appropriately */
	void runAction(Store& store, const string& data);

	/*	-------------------------------print---------------------------------
	Description: Helper print method. Overrides base class so that DisplayInventory
	can print its items unique to its containing data.
	Pre-condition:	None.
	Post-condition:  Returns formatted ostream */
	ostream& print(ostream& out) const;

};


