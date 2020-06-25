/*  ---------------------------------------------------------------------------
    ITEM.H
    Parent class for Coin, Comic, and SportsCard
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Item class: Base class for the different types of items sold in the store.
        -- Each item contains a count, year, precedence */

#pragma once
#include "Comparable.h"
#include <string>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Item : public Comparable {
protected:
    int count;
    int year;
    int precedence;

public:
    /*	------------------------------Constructor-------------------------------
    Description: Conventional constructor.
    Pre-condition:	None.
    Post-condition:	Creates new item.*/
    Item();

    /*	--------------------------------setData-------------------------------
    Description: Virtual setData method.
    Pre-condition: None.
    Post-condition: Calls derived class setData implementation .*/
    virtual void setData(const string& data) = 0;

    /*	------------------------------Destructor-------------------------------
      Description:      Virtual destructor since this is a parent class
      Pre-condition:    No longer in scope of Store.
      Post-condition:   Calls derived class destructor implementation.*/
    virtual ~Item() {}

    /*	--------------------------------setData-------------------------------
    Description: Virtual create method.
    Pre-condition: None.
    Post-condition: Calls derived class create implementation .*/
    virtual Item* create() const = 0; 

    /*	--------------------------------getCount-------------------------------
    Description: Getter for member count
    Pre-condition:	None.
    Post-condition:	Returns int count */
    const int& getCount() const;

    /*	--------------------------------getYear-------------------------------
    Description: Getter for member year
    Pre-condition:	None.
    Post-condition:	Returns year */
    const int& getYear() const;

    /*	--------------------------------setCount-------------------------------
    Description: Setter for member count
    Pre-condition:	None.
    Post-condition:	Changes count to parameter count */
    void setCount(const int& count);

    /*	----------------------------------<------------------------------------
    Description:  Virtual operator< method. 
    Pre-condition:	None.
    Post-condition:  Calls derived class's operator< implementation*/
    virtual bool operator<(const Comparable& rhs) const override = 0;

    /*	---------------------------------->------------------------------------
    Description:  Virtual operator> method.
    Pre-condition:	None.
    Post-condition:  Calls derived class's operator> implementation*/
    virtual bool operator>(const Comparable& rhs) const override = 0;

    /*	----------------------------------===------------------------------------
    Description:  Virtual operator== method.
    Pre-condition:	None.
    Post-condition:  Calls derived class's operator== implementation*/
    virtual bool operator==(const Comparable& rhs) const override = 0;

    /*	----------------------------------!=------------------------------------
    Description:  Virtual operator!= method.
    Pre-condition:	None.
    Post-condition:  Calls derived class's operator!= implementation*/
    virtual bool operator!=(const Comparable& rhs) const override = 0;

    /*	-------------------------------getFactory-------------------------------
    Description: Getter for precedence.
    Pre-condition: N/A.
    Post-condition:	Returns precedence. */
    int& getPrecedence();
};


