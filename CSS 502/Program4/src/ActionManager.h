/*  ---------------------------------------------------------------------------
    ACTIONMANAGER.H
    Derived Manager class of type Action
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    ActionManager class: Is a aderived manager class for Actions.  It contains
    a ActionFactory member to create new Actions.
        -- We inherit dataFileVector, which contains all data to be process.*/

#pragma once
#include "Action.h"
#include "ActionFactory.h"
#include "Manager.h"

class ActionManager: public Manager {
private:

	ActionFactory* objFactory;

public:

    /*	------------------------------Constructor-------------------------------
    Description: Conventional constructor.
    Pre-condition:	None.
    Post-condition:	Initializes objFactory.*/
    ActionManager();

    /*	------------------------------Destructor-------------------------------
    Description: Conventional destructor.
    Pre-condition:	No longer in scope of ActionManager.
    Post-condition:	Destructs this class and its items, including objFactory
                    and dataFileVector.*/
	~ActionManager();

    /*	----------------------------BuildByFactory-------------------------------
    Description: Calls factory to make action.
    Pre-condition:	Called by Store to create items.
    Post-condition:	Will check first letter of line to determine what type of 
                    action and pass that through the factory. Then the factory
                    will return new action (derived). Then we call that derived
                    action's class runAction method.*/
	void buildByFactory(Store& store);
};

