/*  ---------------------------------------------------------------------------
    CUSTOMERMANAGER.CPP
    Manager class of type Customer
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    CustomerManager class: Reads file and creates Customer item, it also stores
    it in the tree as well as a hashtable for quick look up.
        -- We inherit dataFileVector, which contains all data to be process.*/

#include "CustomerManager.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Initializes customers and resizes it to numOfTypeOfCustomers.
                It will also initialize customerLookUp..*/
CustomerManager::CustomerManager()
{
    customerLookUp = new HashTable;

    customers.resize(numOfTypeOfCustomers);
    customers[0] = new CustomerSearchTree;
}

/*	------------------------------Destructor-------------------------------
Description: Conventional destructor.
Pre-condition:	No longer in scope of CustomerManager.
Post-condition:	Calls destructors for this class and all its items, including
                customers and customerLookUp.*/
CustomerManager::~CustomerManager()
{
    for (vector<int>::size_type i = 0; i < customers.size(); i++) {
        if (customers[i] != nullptr) {
            delete customers[i];
        }
    }
    customers.clear();
    delete customerLookUp;
}

/*	------------------------------Destructor-------------------------------
Description: Reads infile and builds Customer tree.
Pre-condition:	Called in store method.
Post-condition:	Tree accurately represents data stored in text file. */
void CustomerManager::buildCustomerData(ifstream& infile)
{
    customerLookUp->buildTable(numOfItems);
	 for (;;) {

            if (infile.eof()) {
                return;
            }

            // Store line as a string
            string data;
            getline(infile, data);

            vector<string> dataSet;
            stringstream line(data);
            string part;

            while (getline(line, part, ',')) {
                dataSet.push_back(part);
            }

            if (dataSet.size() > 0) {
                // Extract ID
                int ID = stoi(dataSet[0]);

                // Extract full name
                string fullName = dataSet[1];
                fullName.erase(0, 1);
                string nameDelimiter = " ";

                // Extract first name from full name string
                string firstName = fullName.substr(0, fullName.find(nameDelimiter));
                fullName.erase(0, fullName.find(nameDelimiter) + nameDelimiter.length());

                // Extract last name from full name string if exists
                string lastName;
                if (fullName != "") {
                    lastName = fullName.substr(0, fullName.find(nameDelimiter));
                }
                else {
                    lastName = "";
                }

                // Create new customer
                Comparable* cust = new Customer(ID, firstName, lastName);
                customerLookUp->addHashable(ID, cust);

                // Add customer to SearchTree
                customers[0]->add(cust);
    
            }
     }
}

/*	-------------------------------getCustomerFiles-------------------------
Description: Getter for vector holding customer tree.
Pre-condition: N/A.
Post-condition:	Returns customers. */
vector<CustomerSearchTree*>& CustomerManager::getCustomerFiles()
{
    return customers;
}

/*	-------------------------------getHashTable-------------------------------
Description: Getter for getHashTable.
Pre-condition: N/A.
Post-condition:	Returns getHashTable. */
HashTable*& CustomerManager::getHashTable()
{
    return customerLookUp;
}
