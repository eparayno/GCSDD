/*  ---------------------------------------------------------------------------
	COMPARABLE.H
	BinarySearchTree for Comparable
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	SearchTree class: This class will encapsulate a char character and is one
	of the mebmers in the SearchTree class. Contains header files.
		-- Overloaded >> allows for reading the file by char
		-- checks for inequality and comparison, which will allow us to sort
		   tree in ascending ASCII order.
	Assumptions:
		-- Will be able to read text file by char.
	*/


#pragma once
#include <istream>
#include <ostream>
#include <iostream>

using namespace std;

class Comparable {
	char rawData;	// encapsulated char value.

	/*	----------------------------->>---------------------------------------
	Reads char from istream.
	Precondition:	None.
	Postcondition:  Returns char value to istream*/
	friend istream& operator>>(istream& input, Comparable& c);

	/*	-------------------------------<<-------------------------------------
	Prints out to ostream.
	Precondition:	None.
	Postcondition:  Returns char value to ostream using char::operator<<*/
	friend ostream& operator<<(ostream& output, const Comparable& c);

public:

	/*	------------------------------==-------------------------------------
	Checks if two comparables are equal
	Precondition:	None.
	Postcondition:  Returns true if equal*/
	bool operator==(const Comparable& a) const;

	/*	--------------------------------!=----------------------------------
	Checks if two comparables are not equal
	Precondition:	None.
	Postcondition:  Returns false if equal*/
	bool operator!=(const Comparable& a) const;

	/*	-------------------------------->-------------------------------------
	Checks if this is greater than Comparable passed as parameter are not equal
	Precondition:	None.
	Postcondition:  Returns true if greater than parameter*/
	bool operator<(const Comparable& a) const;

	/*	----------------------------------<------------------------------------
	Checks if this is lesser than Comparable passed as parameter are not equal.
	Precondition:	None.
	Postcondition:  Returns true if less than parameter*/
	bool operator>(const Comparable& a) const;

};

