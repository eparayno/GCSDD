/*  ---------------------------------------------------------------------------
    COMPARABLE.H
    Parent class for Item and Customer
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Comparable class: Base class for item and customer
        -- Has comparison operators */

#pragma once
#include "Hashable.h"

using namespace std;
class Comparable : public Hashable{

public:
    /*	------------------------------Constructor-------------------------------
    Description: Conventional constructor.
    Pre-condition:	None.
    Post-condition:	Creates new Comparable.*/
    Comparable();

    /*	------------------------------Destructor-------------------------------
      Description:      Virtual destructor since this is a base class
      Pre-condition:    No longer in scope.
      Post-condition:   Calls derived class destructor implementation.*/
    virtual ~Comparable();

    /*	----------------------------------<------------------------------------
    Description:  Virtual operator< method.
    Pre-condition:	None.
    Post-condition:  Calls derived class's operator< implementation*/
    virtual bool operator< (const Comparable& c) const = 0;

    /*	---------------------------------->------------------------------------
    Description:  Virtual operator> method.
    Pre-condition:	None.
    Post-condition:  Calls derived class's operator> implementation*/
    virtual bool operator> (const Comparable& c) const = 0;

    /*	----------------------------------===------------------------------------
    Description:  Virtual operator== method.
    Pre-condition:	None.
    Post-condition:  Calls derived class's operator== implementation*/
    virtual bool operator== (const Comparable& c) const = 0;

    /*	----------------------------------!=------------------------------------
    Description:  Virtual operator!= method.
    Pre-condition:	None.
    Post-condition:  Calls derived class's operator!= implementation*/
    virtual bool operator!= (const Comparable& c) const = 0;

};