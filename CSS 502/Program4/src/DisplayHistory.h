/*  ---------------------------------------------------------------------------
	DISPLAYHISTORY.H
	Derived class DisplayHistory with parent class Action
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	DisplayHistory class: Derived class of Action.
		-- outputs the history for every customer, customers alphabetical order */

#pragma once
#include <string>
#include "Action.h"

class Store;

class DisplayHistory : public Action
{
public:
	
	/*	------------------------------Constructor-------------------------------
	Description: Conventional constructor.
	Pre-condition:	None.
	Post-condition:	Creates DisplayHistory.*/
	DisplayHistory();

	/*	------------------------------Destructor-------------------------------
	  Description: Conventional destructor.
	  Pre-condition: No longer in scope.
	  Post-condition: Destructs class.*/
	~DisplayHistory();

	/*	--------------------------------create---------------------------------
	Description: Allows for open ended principle
	Pre-condition: Called by ActionFactory.
	Post-condition: Returns Action pointer. */
	virtual Action* create() const;

	/*	--------------------------------runAction---------------------------------
	Description: Uses data in Store to print history.
	Pre-condition: Called in factory.
	Post-condition: Prints appropriately */
	void runAction(Store& store, const string& data);

	/*	-------------------------------print---------------------------------
	Description: Helper print method. Overrides base class so that DisplayHistory
	can print its items unique to its containing data.
	Pre-condition:	None.
	Post-condition:  Returns formatted ostream */
	ostream& print(ostream& out) const;
};
