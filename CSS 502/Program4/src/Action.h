/*  ---------------------------------------------------------------------------
	Action.CPP
	Parent class for buy, sell, and display classes
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	Action class: Base class for the different types of actions that can be performed. */

#pragma once
#include "Hashable.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Store;
class Action : public Hashable {
protected:
	char transactionSymbol;

public:
	/*	------------------------------Constructor-------------------------------
	Description: Conventional constructor.
	Pre-condition:	None
	Post-condition:	Creates new action. */
	Action() {}


	/*	------------------------------Destructor-------------------------------
	  Description:      Virtual destructor since this is a parent class
	  Pre-condition:    No longer in scope of Store.
	  Post-condition:   Calls derived class destructor implementation.*/
	virtual ~Action() {}

	/*	--------------------------------create---------------------------------
	Description: Virtual function. Allows for open ended principle
	Pre-condition: Called by ActionFactory.
	Post-condition: Calls derived class implementation */
	virtual Action* create() const = 0;
	
	/*	--------------------------------runAction---------------------------------
	Description: Virtual function. 
	Pre-condition: Called by ActionFactory.
	Post-condition: Calls derived class implementation */
	virtual void runAction(Store& store, const string& data) = 0;
};

