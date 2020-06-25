/*  ---------------------------------------------------------------------------
    SPORTSCARD.H
    Derived class SportsCard with parent class Item
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    SportsCard class: Derived class of item.
        -- Sorted by player, yera, manufacturer and grade */

#pragma once
#include "Item.h"

class SportsCard : public Item {

protected:
    string player;
    string manufacturer;
    string grade;

public:

    /*	------------------------------Destructor-------------------------------
      Description: Conventional destructor.
      Pre-condition:  No longer in scope.
      Post-condition: Destructs class and all items it contains.*/
    ~SportsCard();

    /*	--------------------------------create---------------------------------
    Description: Maintains open-ended principle.
    Pre-condition: Called by ItemFactory.
    Post-condition: Returns item pointer */
    virtual Item* create() const;

    /*	-----------------------------Constructor-------------------------------
    Description: Default constructor for class SportsCards
    Pre-condition: Called by Create function.
    Post-condition:	Created new SportsCard */
    SportsCard();

    /*	-------------------------------setData-------------------------------
    Description: Sets data using string of data
    Pre-condition: Called by Manager class after it creates new SportsCard.
    Post-condition:	New SportsCards created with corresponding precedence defined
                    and count initialized. Also set year, manufacturer,
                    player, and grade based on parameter values */
    void setData(const string& data);

    /*	---------------------------------getPlayer-----------------------------
    Description: Getter for member player
    Pre-condition:	None.
    Post-condition:	Returns string player */
    const string getPlayer() const;

    /*	---------------------------------getPublisher--------------------------
    Description: Getter for member publisher
    Pre-condition:	None.
    Post-condition:	Returns string publisher */
    const string getManufacturer() const;

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
    std::ostream& print(ostream& out) const;

};

