/*  ---------------------------------------------------------------------------
	COMPARABLE.CPP
	BinarySearchTree for Comparable
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	SearchTree class: This class will encapsulate a char character and is one
	of the mebmers in the SearchTree class. 
		-- Overloaded >> allows for reading the file by char 
		-- checks for inequality and comparison, which will allow us to sort
		   tree in ascending ASCII order. 
	Assumptions:
		-- Will be able to read text file by char.
	*/


#include "Comparable.h"

	/*	----------------------------->>---------------------------------------
	Reads char from istream.
	Precondition:	None.
	Postcondition:  Returns char value to istream*/
	istream& operator>>(istream& input, Comparable& c) {
		input.get(c.rawData);
		return input;
	}

	/*	-------------------------------<<-------------------------------------
	Prints out to ostream.
	Precondition:	None.
	Postcondition:  Returns char value to ostream using char::operator<<*/
	ostream& operator<<(ostream& output, const Comparable& c) {
		output << c.rawData;
		return output;
	}

	/*	------------------------------==-------------------------------------
	Checks if two comparables are equal
	Precondition:	None.
	Postcondition:  Returns true if equal*/
	bool Comparable::operator==(const Comparable& a) const {
		if (rawData == a.rawData) {
			return true;
		} else {
			return false;
		}
	}

	/*	--------------------------------!=----------------------------------
	Checks if two comparables are not equal
	Precondition:	None.
	Postcondition:  Returns false if equal*/
	bool Comparable::operator!=(const Comparable& a) const {
		if (rawData != a.rawData) {
			return true;
		} else {
			return false;
		}
	}

	/*	-------------------------------->-------------------------------------
	Checks if this is greater than Comparable passed as parameter are not equal
	Precondition:	None.
	Postcondition:  Returns true if greater than parameter*/
	bool Comparable::operator>(const Comparable& a) const {
		if (rawData > a.rawData) {
			return true;
		} else {
			return false;
		}
	}

	/*	----------------------------------<------------------------------------
	Checks if this is lesser than Comparable passed as parameter are not equal.
	Precondition:	None.
	Postcondition:  Returns true if less than parameter*/
	bool Comparable::operator<(const Comparable& a) const{
		if (rawData < a.rawData) {
			return true;
		} else {
			return false;
		}
	}

