/*  ---------------------------------------------------------------------------
	SELL.H
	Derived class Sell with parent class Action
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	Buy class: Derived class of Action.
		-- removes an item from the inventory*/

#pragma once
#include <string>
#include "Action.h"
#include "Customer.h"
#include "Item.h"

class Store;
class Sell : public Action
{
protected:
	Customer* customer;
	Item* item;

public:

	/*	------------------------------Constructor-------------------------------
	Description: Conventional constructor.
	Pre-condition:	None.
	Post-condition:	Creates Sell.*/
	Sell();

	/*	------------------------------Destructor-------------------------------
	  Description: Conventional destructor.
	  Pre-condition:	No longer in scope.
	  Post-condition: Destructs class.*/
	~Sell();

	/*	--------------------------------create---------------------------------
	Description: Allows for open ended principle
	Pre-condition: Called by ActionFactory.
	Post-condition: Returns Action pointer. */
	virtual Action* create() const;

	/*	--------------------------------runAction---------------------------------
	Description: Uses data in Store to buy (add) an item to the inventory.
	Pre-condition: Performed in factory.
	Post-condition: Made appropriate changes to inventory and adds to customer
					history vector. */
	void runAction(Store& store, const string& data);

	/*	-------------------------------print---------------------------------
	Description: Helper print method. Overrides base class so that Sell can
	print its necessary messages.
	Pre-condition:	None.
	Post-condition:  Returns formatted ostream */
	ostream& print(ostream& out) const;

};

