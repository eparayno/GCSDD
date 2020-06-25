/*  ---------------------------------------------------------------------------
    STORE.CPP
    Store class called by main to execute program
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Store class: The main function of this class to extract data from text files
    provided in the directory. The files contain initial inventory, customer
    profiles, and a set commands to run.
        -- Initializes inventory
        -- Creates customer database
        -- Runs commands
    Assumptions:
        -- Assumes all three files are present in the directory */

#include "Store.h"

using namespace std;

/*	-------------------------------execute---------------------------------
Description: Will perform all three actions (initialize inventory, create
                customer profiles and run commands) necessary to run the
                program
Pre-condition: Called by main class.
Post-condition:	Will have created customer and item data sets and modified
                them accordingly based on the commands ran. */
void Store::execute() 
{
    createInventory();
    createCustomers();
    runCommands();
}

/*	----------------------------createInventory----------------------------
Description: Will read in a file and read each item line by line. Each item
                will contain character denoting the type of item, number in
                inventory, year, grade, and other item descriptions. This
                method will create an item derived class based on character,
                set its values accordingly, and update the item database. To
                create derived items, it will have to call create from
                ItemFactory.
Pre-condition: Called by execute.
Post-condition:	The item SearchTree will accurately depict the text file
                contents. It will print out any errors accordingly. */
void Store::createInventory() {

    ifstream infile("hw4inventory.txt");

    if (!infile) {
        cout << "The file could not be opened";
    } else {
        itemDB->buildItemData(infile);
        itemDB->buildByFactory();
    }

}

/*	----------------------------createCustomers----------------------------
Description: Takes a file and reads each Customer data by line. Each Customer
                will contain a 3 digit iD and string that are subdivided to
                first and last name, although last name is not required. This
                method will create a Customer, set values accordingly, and
                update the Customer database.
Pre-condition: Called by execute.
Post-condition:	The Customer SearchTree will accurately depict the text file
                contents. It will print out any errors accordingly. */
void Store::createCustomers() {

    ifstream infile("hw4customers.txt");

    if (!infile) {
        cout << "The file could not be opened";
    }
    else {
        customerDB->buildCustomerData(infile);
    }

}

/*	------------------------------runCommands------------------------------
Description: Takes a file and reads each Command by line. Each Command will
                contain a set of data to be extracted and passed as parameters
                in methods of InventoryTracker. The first letter will denote
                what type of action will be called.
Pre-condition: Called by execute.
Post-condition:	Will have call methods in the InventoryTracker accordingly.
                Will print errors accordingly */
void Store::runCommands() {

    ifstream infile("hw4commands.txt");

    if (!infile) {
        cout << "The file could not be opened";
    }
    else {
        actionDB->buildItemData(infile);
        actionDB->buildByFactory(*this);
    }

}
/*	-----------------------------Constructor-------------------------------
Description: Default constructor for class Store
Pre-condition:	None
Post-condition:	Creates default constructor, will create new DB's */
Store::Store()
{
    actionDB = new ActionManager;
    customerDB = new CustomerManager;
    itemDB = new ItemManager;
}

/*	------------------------------Destructor-------------------------------
Description: Conventional destructor.
Pre-condition:	No longer in scope of Store.
Post-condition:	Calls destructors for each DB.*/
Store::~Store()
{
    delete actionDB;
    delete customerDB;
    delete itemDB;
}

/*	-------------------------------getItemDB-------------------------------
Description: Getter for itemDB.
Pre-condition: itemDB exists.
Post-condition:	Returns itemDB. */
ItemManager*& Store::getItemDB()
{
    return itemDB;
}

/*	------------------------------getCustomerDB-------------------------------
 Description: Getter for customerDB.
 Pre-condition: customerDB exists.
 Post-condition:	Returns customerDB. */
CustomerManager*& Store::getCustomerDB()
{
    return customerDB;
}

/*	-------------------------------getActionDB-------------------------------
 Description: Getter for actionDB.
 Pre-condition: actionDB exists.
 Post-condition:	Returns actionDB. */
ActionManager*& Store::getActionDB()
{
    return actionDB;
}
