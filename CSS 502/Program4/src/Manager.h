/*  ---------------------------------------------------------------------------
    MANAGER.H
    Base Manager class
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Manager class: Is a base class for Action and Item manager. Only contains one
    function, whose purpose is to read a file and store into a string-- as this 
    is the same mechanism for each manager class.
        -- infile contains data
    Assumptions:
        -- In order for this program to work, you must have both ActionManager
           and itemManager classes.*/

#pragma once
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Manager {
protected:

	vector<string> dataFileVector;

public:

    /*	------------------------------Destructor-------------------------------
    Description: Virtual destructor.
    Pre-condition:	A manager class is no longer within scope.
    Post-condition:	Calls appropriate derived class destructor implemenation.*/
	virtual ~Manager() {}

    /*	------------------------------buildItemData-----------------------------
    Description: Takes an infile, reads it line by line. Any line that contains
                 more than 0 character will be added to the back of the linked
                 list file.
    Pre-condition:	Called by method by Store class and passes its corresponding
                    text file.
    Post-condition:	dataFileVector represents all valuable inputs in infile. */
	void buildItemData(ifstream& infile);
};

