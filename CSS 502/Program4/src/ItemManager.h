/*  ---------------------------------------------------------------------------
    ITEMMANGER.H
    Derived Manager class of type Item
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    ItemManagerClass class: Is a aderived manager class for Items.  It contains
    a ItemFactory member to create new Items as well as a shelf, which contains
    pointers to SearchTrees. Each SearchTree represents a derived class of item.
        -- Shelves contain all items.
        -- We inherit dataFileVector, which contains all data to be process. 
    assumptions:
        -- Max number of shelves is 26 (26 letters in alphabet) */

#pragma once
#include "Item.h"
#include "ItemFactory.h"
#include "ItemSearchTree.h"
#include "Manager.h"

class ItemManager : public Manager {
private:

	ItemFactory* objFactory;
	vector<ItemSearchTree*> shelves;

public:

    /*	------------------------------Constructor-------------------------------
    Description: Conventional constructor.
    Pre-condition:	None.
    Post-condition:	Creates objFactory and resizes shelves.*/
	ItemManager();

    /*	------------------------------Destructor-------------------------------
    Description: Conventional destructor.
    Pre-condition:	No longer in scope of ItemManager.
    Post-condition:	Deallocates objFactory and shelves.*/
	~ItemManager();


    /*	----------------------------BuildByFactory-------------------------------
    Description: Calls factory to make item. 
    Pre-condition:	Called by Store to create items.
    Post-condition:	Shelves contain SearchTrees with each tree representing a 
                    different derived item class. All information indicated in 
                    dataFileVector is represented in the shelves.*/
	void buildByFactory();


    /*	-------------------------------getShelves-------------------------------
    Description: Getter for shelves.
    Pre-condition: N/A.
    Post-condition:	Returns shelves. */
	vector<ItemSearchTree*> getShelves();

    /*	-------------------------------getFactory-------------------------------
    Description: Getter for itemFactory.
    Pre-condition: N/A.
    Post-condition:	Returns itemFactory. */
	ItemFactory*& getFactory();

};