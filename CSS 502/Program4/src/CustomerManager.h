/*  ---------------------------------------------------------------------------
    CUSTOMERMANAGER.H
    Manager class of type Customer
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    CustomerManager class: Reads file and creates Customer item, it also stores
    it in the tree as well as a hashtable for quick look up.
        -- We inherit dataFileVector, which contains all data to be process.*/

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "CustomerSearchTree.h"
#include "Customer.h"
#include "HashTable.h"

class CustomerManager {
protected:
    const int numOfItems = 1000;            // max number of customers
    const int numOfTypeOfCustomers = 1;     // max number of customer type

    vector<CustomerSearchTree*> customers;
    HashTable* customerLookUp;

public:
    /*	------------------------------Constructor-------------------------------
    Description: Conventional constructor.
    Pre-condition:	None.
    Post-condition:	Initializes customers and resizes it to numOfTypeOfCustomers.
                    It will also initialize customerLookUp..*/
    CustomerManager();

    /*	------------------------------Destructor-------------------------------
    Description: Conventional destructor.
    Pre-condition:	No longer in scope of CustomerManager.
    Post-condition:	Calls destructors for this class and all its items, including
                    customers and customerLookUp.*/
    ~CustomerManager();

    /*	------------------------------Destructor-------------------------------
    Description: Reads infile and builds Customer tree.
    Pre-condition:	Called in store method.
    Post-condition:	Tree accurately represents data stored in text file. */
    void buildCustomerData(ifstream& infile);

    /*	-------------------------------getCustomerFiles-------------------------
    Description: Getter for vector holding customer tree.
    Pre-condition: N/A.
    Post-condition:	Returns customers. */
    vector<CustomerSearchTree*>& getCustomerFiles();

    /*	-------------------------------getHashTable-------------------------------
    Description: Getter for getHashTable.
    Pre-condition: N/A.
    Post-condition:	Returns getHashTable. */
    HashTable*& getHashTable();
};

