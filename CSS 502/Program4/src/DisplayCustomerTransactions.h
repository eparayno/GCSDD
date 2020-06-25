/*  ---------------------------------------------------------------------------
	DISPLAYCUSTOMERTRANSACTIONS.H
	Derived class DisplayCustomerTransactions with parent class Action
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	DisplayCustomerTransactions class: Derived class of Action.
		-- outputs all the transactions for a customer */

#pragma once
#include <string>
#include "Action.h"
#include "Customer.h"

class Store;
class DisplayCustomerTransactions : public Action
{
protected:
	Customer* customer;

public:

	/*	------------------------------Constructor-------------------------------
	Description: Conventional constructor.
	Pre-condition:	None.
	Post-condition:	Creates DisplayCustomerTransactions.*/
	DisplayCustomerTransactions();

	/*	------------------------------Destructor-------------------------------
	  Description: Conventional destructor.
	  Pre-condition: No longer in scope.
	  Post-condition: Destructs class.*/
	~DisplayCustomerTransactions();

	/*	--------------------------------create---------------------------------
	Description: Allows for open ended principle
	Pre-condition: Called by ActionFactory.
	Post-condition: Returns Action pointer. */
	virtual Action* create() const;

	/*	--------------------------------runAction------------------------------
	Description: Uses data in Store to print customer history.
	Pre-condition: Called in factory.
	Post-condition: Prints appropriately */
	void runAction(Store& store, const string& data);

	/*	-------------------------------print---------------------------------
	Description: Helper print method. Overrides base class so that this can
	print its necessary messages.
	Pre-condition:	None.
	Post-condition:  Returns formatted ostream */
	ostream& print(ostream& out) const;

};
