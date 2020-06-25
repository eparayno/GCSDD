/*  ---------------------------------------------------------------------------
    HASHABLE.H
    Parent class for Comparable and Action
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Hashable class: Base class for all items
        -- Has comparison printing funcitonalities */

#pragma once
#include <iostream>

using namespace std;

class Hashable
{
public:
    /*	------------------------------Constructor-------------------------------
    Description: Conventional constructor.
    Pre-condition:	None.
    Post-condition:	Creates new Hashable.*/
	Hashable() {}

    /*	------------------------------Destructor-------------------------------
      Description:      Virtual destructor since this is a base class
      Pre-condition:    No longer in scope.
      Post-condition:   Calls derived class destructor implementation.*/
	virtual ~Hashable() {}

    /*	------------------------------Destructor-------------------------------
      Description:      Overloaded operator<< class
      Pre-condition:    n/a
      Post-condition:   Calls print.*/
    friend ostream& operator<<(ostream& out, const Hashable& foo);

    /*	------------------------------Destructor-------------------------------
      Description:      Virtual print helper
      Pre-condition:    Called by operator<<
      Post-condition:   Calls derived class implementation.*/
	virtual ostream& print(ostream& out) const = 0;
};

