/*  ---------------------------------------------------------------------------
	DISPLAYHISTORY.CPP
	Derived class DisplayHistory with parent class Action
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	DisplayHistory class: Derived class of Action.
		-- outputs the history for every customer, customers alphabetical order */

#include "DisplayHistory.h"
#include "Store.h"
#include "CustomerSearchTree.h"

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Creates DisplayHistory.*/
DisplayHistory::DisplayHistory()
{
}

/*	------------------------------Destructor-------------------------------
  Description: Conventional destructor.
  Pre-condition: No longer in scope.
  Post-condition: Destructs class.*/
DisplayHistory::~DisplayHistory()
{
}

/*	--------------------------------create---------------------------------
Description: Allows for open ended principle
Pre-condition: Called by ActionFactory.
Post-condition: Returns Action pointer. */
Action* DisplayHistory::create() const
{
	return new DisplayHistory;
}
/*	--------------------------------create---------------------------------
Description: Uses data in Store to print inventory.
Pre-condition: Called in factory.
Post-condition: Prints appropriately */
void DisplayHistory::runAction(Store& store, const string& data)
{;
	cout << "DISPLAY HISTORY:________________________________________________________________________________________" << endl;
	CustomerSearchTree* tree = store.getCustomerDB()->getCustomerFiles()[0];
	cout << *tree;
	
}

/*	-------------------------------print---------------------------------
Description: Helper print method. Overrides base class so that DisplayHistory
can print its items unique to its containing data.
Pre-condition:	None.
Post-condition:  Returns formatted ostream */
ostream& DisplayHistory::print(ostream& out) const
{
	return out;
}
