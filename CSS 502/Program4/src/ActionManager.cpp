/*  ---------------------------------------------------------------------------
	ACTIONMANAGER.CPP
	Derived Manager class of type Action
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	ActionManager class: Is a aderived manager class for Actions.  It contains
	a ActionFactory member to create new Actions.
		-- We inherit dataFileVector, which contains all data to be process.*/

#include "ActionManager.h"

/*	------------------------------Destructor-------------------------------
Description: Conventional destructor.
Pre-condition:	No longer in scope of ActionManager.
Post-condition:	Destructs this class and its items, including objFactory
				and dataFileVector.*/
ActionManager::~ActionManager()
{
	dataFileVector.clear();
	delete objFactory;
}

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Initializes objFactory.*/
ActionManager::ActionManager()
{
	objFactory = new ActionFactory;
}

/*	----------------------------BuildByFactory-------------------------------
Description: Calls factory to make action.
Pre-condition:	Called by Store to create items.
Post-condition:	Will check first letter of line to determine what type of
				action and pass that through the factory. Then the factory
				will return new action (derived). Then we call that derived
				action's class runAction method.*/
void ActionManager::buildByFactory(Store& store)
{
	char obj;
	Action* p;

	for (int i = 0; i < dataFileVector.size(); i++) {
		
		// get action symbol
		obj = dataFileVector[i].at(0);
		dataFileVector[i].erase(0, 3);

		// call factory to return action pointer
		p = objFactory->create(obj);

		if (p != nullptr) {
			// if valid action, runAction
			p->runAction(store, dataFileVector[i]);
			cout << endl << endl;
		}
	}
}
