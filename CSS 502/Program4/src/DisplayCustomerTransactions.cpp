/*  ---------------------------------------------------------------------------
	DISPLAYCUSTOMERTRANSACTIONS.CPP
	Derived class DisplayCustomerTransactions with parent class Action
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	DisplayCustomerTransactions class: Derived class of Action.
		-- outputs all the transactions for a customer */

#include "DisplayCustomerTransactions.h"
#include "HashTable.h"
#include "Store.h"

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Creates DisplayCustomerTransactions.*/
DisplayCustomerTransactions::DisplayCustomerTransactions()
{
}

/*	------------------------------Destructor-------------------------------
  Description: Conventional destructor.
  Pre-condition: No longer in scope.
  Post-condition: Destructs class.*/
DisplayCustomerTransactions::~DisplayCustomerTransactions()
{
	delete customer;
}

/*	--------------------------------create---------------------------------
Description: Allows for open ended principle
Pre-condition: Called by ActionFactory.
Post-condition: Returns Action pointer. */
Action* DisplayCustomerTransactions::create() const
{
	return new DisplayCustomerTransactions;
}

/*	--------------------------------runAction------------------------------
Description: Uses data in Store to print customer history.
Pre-condition: Called in factory.
Post-condition: Prints appropriately */
void DisplayCustomerTransactions::runAction(Store& store, const string& data)
{
	cout << "DISPLAY CUSTOMER TRANSACTIONS:_______________________________________________________________________________" << endl;
	string dataString = data;
	HashTable* lookUpTable = store.getCustomerDB()->getHashTable();
	this->customer = dynamic_cast<Customer*>(lookUpTable->getHashable(stoi(dataString.substr(0, 3))));

	customer->printHistory();

}

/*	-------------------------------print---------------------------------
Description: Helper print method. Overrides base class so that this can
print its necessary messages.
Pre-condition:	None.
Post-condition:  Returns formatted ostream */
ostream& DisplayCustomerTransactions::print(ostream& out) const
{
	return out;
}
