/*  ---------------------------------------------------------------------------
    COMIC.H
    Derived class Comic with parent class Item
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Coin class: Derived class of item.
        -- Sorted by publisher, title, year, and grade */

#pragma once
#include "Item.h"
#include <iomanip>

class Comic : public Item {
protected:
    string publisher;
    string title;
    string grade;

public:

    /*	------------------------------Destructor-------------------------------
      Description: Conventional destructor.
      Pre-condition:  No longer in scope.
      Post-condition: Destructs class and all items.*/
    ~Comic();

    /*	--------------------------------create---------------------------------
    Description: Allows for open ended principle
    Pre-condition: Called by ItemFactory.
    Post-condition: rreturns item pointer. */
    virtual Item* create() const;

     /*	-----------------------------Constructor-------------------------------
     Description: Default constructor for class SportsCards
     Pre-condition: Called by Create function.
     Post-condition: Created new Comic*/
     Comic();

     /*	-----------------------------Constructor-------------------------------
    Description: Sets data using string of data
    Pre-condition: Called by Manager class after it creates new Comic.
    Post-condition:	Comic data set with corresponding precedence defined and
                    count initialized. Also set year, publisher, title,
                    and grade based on parameter values */
     void setData(const string& data);

    /*	-------------------------------getPublisher----------------------------
    Description: Getter for member publisher
    Pre-condition:	None.
    Post-condition:	Returns string publisher */
    const string getPublisher() const;

    /*	---------------------------------getTitle------------------------------
    Description: Getter for member title
    Pre-condition:	None.
    Post-condition:	Returns string title */
    const string getTitle() const;

    /*	--------------------------------getGrade-------------------------------
    Description: Getter for member grade
    Pre-condition:	None.
    Post-condition:	Returns string grade */
    const string getGrade() const;

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
      Description: Helper print method. Overrides base class so that Comic can
      print its items unique to its containing data.
      Pre-condition:	None.
      Post-condition:  Returns formatted ostream */
    ostream& print(ostream& out) const;

};

