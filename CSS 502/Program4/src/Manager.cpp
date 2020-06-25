/*  ---------------------------------------------------------------------------
	MANAGER.CPP
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

#include "Manager.h"

/*	------------------------------buildItemData-----------------------------
Description: Takes an infile, reads it line by line. Any line that contains
			 more than 0 character, will be added to the back of the linked
			 list file.
Pre-condition:	Called by method by Store class and passes its corresponding
				text file.
Post-condition:	dataFileVector represents all valuable inputs in infile. */
void Manager::buildItemData(ifstream& infile)
{
	for (;;) {

		// Break if we reached end of file.
		if (infile.eof()) {
			return;
		}

		string line;

		getline(infile, line);
		if (line.size() > 0) {
			// push each line to the back of dataFileVector
			dataFileVector.push_back(line);
		}

	}
}

