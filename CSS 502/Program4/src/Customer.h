#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Action.h"

#include "Comparable.h"

using namespace std;

class Customer: public Comparable {
private:
    int ID;
    string firstName;
    string lastName;

    vector<Action*> history; // vector containing transactions in chronological order

public:
    /*	-----------------------------Constructor-------------------------------
    Description: Constructor for class Customer
    Pre-condition:
    Post-condition:	New Customer created with corresponding ID, first name, last
                    name set & history will be initialized as null with size 0. */
    Customer(const int& id, const string& firstName, const string& lastName);

    /*	------------------------------Destructor-------------------------------
    Description: Conventional destructor.
    Pre-condition:	Will be called when Customer is no longer within scope.
    Post-condition:	Removes and deallocates Customer data from memory. */
    ~Customer();

    const int getID() const;


    /*	------------------------------getFirstName-----------------------------
    Description: Getter for member firstName
    Pre-condition:	None.
    Post-condition:	Returns string firstName */
    const string getFirstName() const;

    /*	-------------------------------getLastName-----------------------------
    Description: Getter for member lastName
    Pre-condition:	None.
    Post-condition:	Returns string lastName */
    const string getLastName() const;

    /*	-----------------------------addTransaction----------------------------
    Description: Adds transaction to Customer's history
    Pre-condition:	Takes in a parameter with all necessary data to process with
                    proper formatting.
    Post-condition:	Transaction information is added to end of vector*/
    void addTransaction(Action* transaction);

    /*	------------------------------printTransaction-------------------------
    Description: Iterates through vector and reads its contents.
    Pre-condition:	Non-empty vector.
    Post-condition:	Prints one transaction per line. Number of lines outputted
                    should equal size of history vector*/
    void printHistory() const;

    /*	----------------------------------<------------------------------------
    Description:  Checks if this is lesser than Customer passed as parameter.
    Pre-condition:	None.
    Post-condition:  Returns true if less than parameter*/
    bool operator<(const Comparable& rhs) const override;

    /*	-------------------------------->-------------------------------------
    Description: Checks if this is greater than Customer passed as parameter.
    Pre-condition:	None.
    Post-condition:  Returns true if greater than parameter */
    bool operator>(const Comparable& rhs) const override;

    /*	------------------------------==-------------------------------------
    Description: Checks if two Customers are equal
    Pre-condition:	None.
    Post-condition:  Returns true if equal*/
    bool operator==(const Comparable& rhs) const override;

    /*	--------------------------------!=----------------------------------
    Description: Checks if two Customers are not equal
    Pre-condition:	None.
    Post-condition:  Returns false if equal*/
    bool operator!=(const Comparable& rhs) const override;


    ostream& print(ostream& out) const;

};

