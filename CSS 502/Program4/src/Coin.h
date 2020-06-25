/*  ---------------------------------------------------------------------------
    COIN.H
    Derived class Coin with parent class Item
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Coin class: Derived class of item. 
        -- Sorted by type, year, and then grade */

#pragma once
#include "Item.h"
#include <iomanip>

class Coin : public Item {
protected:
    string type;
    int grade;

public: 

    /*	------------------------------Destructor-------------------------------
      Description: Conventional destructor.
      Pre-condition:  No longer in scope Coin.
      Post-condition: Destructs class and all items*/
    ~Coin();

    /*	--------------------------------create---------------------------------
    Description: Allows for open ended principle
    Pre-condition: Called by ItemFactory.
    Post-condition: rreturns item pointer. */
    virtual Item* create() const;

    /*	-----------------------------Constructor-------------------------------
    Description: Default constructor for class SportsCards
    Pre-condition: Called by Create function.
    Post-condition:	Created new Coin*/
    Coin();

    /*	---------------------------------setData-------------------------------
    Description: Sets data using string of data
    Pre-condition: Called by Manager class after it creates new Coin.
    Post-condition:	Coin data set with corresponding precedence defined and
                    count initialized at 0. Also set year, type, and grade
                    based on parameter values */
    void setData(const string& data);

    /*	--------------------------------getType--------------------------------
    Description: Getter for member Type
    Pre-condition:	None.
    Post-condition:	Returns string type */
    const string& getType() const;

    /*	--------------------------------getGrade-------------------------------
    Description: Getter for member grade
    Pre-condition:	None.
    Post-condition:	Returns int grade */
    const int& getGrade() const;

    /*	----------------------------------<------------------------------------
    Description:  Checks if this is lesser than Item passed as parameter.
    Pre-condition:	None.
    Post-condition:  Returns true if less than parameter*/
    bool operator<(const Comparable& c) const override;

    /*	-------------------------------->-------------------------------------
    Description: Checks if this is greater than Item passed as parameter.
    Pre-condition:	None.
    Post-condition:  Returns true if greater than parameter */
    bool operator>(const Comparable& c) const override;

    /*	------------------------------==-------------------------------------
    Description: Checks if two Items are equal
    Pre-condition:	None.
    Post-condition:  Returns true if equal*/
    bool operator==(const Comparable& c) const override;

    /*	--------------------------------!=----------------------------------
    Description: Checks if two Items are not equal
    Pre-condition:	None.
    Post-condition:  Returns false if equal */
    bool operator!=(const Comparable& c) const override;

    /*	-------------------------------print---------------------------------
    Description: Helper print method. Overrides base class so that Coin can
    print its items unique to its containing data.
    Pre-condition:	None.
    Post-condition:  Returns formatted ostream */
    ostream& print(ostream& out) const;

};

