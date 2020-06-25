/*  ---------------------------------------------------------------------------
    COIN.CPP
    Derived class Coin with parent class Item
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Coin class: Derived class of item.
        -- Sorted by type, year, and then grade */

#include "Coin.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/*	------------------------------Destructor-------------------------------
  Description: Conventional destructor.
  Pre-condition:  No longer in scope Coin.
  Post-condition: Destructs class and all items*/
Coin::~Coin()
{
}

/*	--------------------------------create---------------------------------
Description: Create function that takes in a string. To follow Factory
method.
Pre-condition: Called by ItemFactory.
Post-condition: Takes in a string and extracts data to pass into the
                parameter of Coin constructor. */
Item* Coin::create() const
{
    return new Coin;
}
/*	-----------------------------Constructor-------------------------------
Description: Default constructor for class SportsCards
Pre-condition: Called by Create function.
Post-condition:	Created new Coin*/
Coin::Coin()
{
    grade = 0;
}

/*	---------------------------------setData-------------------------------
Description: Sets data using string of data
Pre-condition: Called by Manager class after it creates new Coin.
Post-condition:	Coin data set with corresponding precedence defined and
                count initialized at 0. Also set year, type, and grade
                based on parameter values */
void Coin::setData(const string& data)
{
    vector<string> dataSet;
    stringstream line(data);
    string part;

    while (getline(line, part, ',')) {
        dataSet.push_back(part);
    }

    this->count = stoi(dataSet[0]);
    this->year = stoi(dataSet[1]);
    this->grade = stoi(dataSet[2]);
    this->type = dataSet[3];

    this->precedence = 0;

    line.str(string());
    dataSet.clear();
}

/*	--------------------------------getType--------------------------------
Description: Getter for member Type
Pre-condition:	None.
Post-condition:	Returns string type */
const string& Coin::getType() const
{
    return type;
}

/*	--------------------------------getGrade-------------------------------
Description: Getter for member grade
Pre-condition:	None.
Post-condition:	Returns int grade */
const int& Coin::getGrade() const
{
    return grade;
}

/*	----------------------------------<------------------------------------
Description:  Checks if this is lesser than Item passed as parameter.
Pre-condition:	None.
Post-condition:  Returns true if less than parameter*/
bool Coin::operator<(const Comparable& c) const
{
    const Coin& rhs = static_cast<const Coin&>(c);

    // compare by type
    if (type < rhs.type)
        return true;
    if (rhs.type < type)
        return false;

    // compare by year
    if ((*this).year < rhs.year)
        return true;
    if (rhs.year < (*this).year)
        return false;

    // compare by grade
    return grade < rhs.grade;
}

/*	-------------------------------->-------------------------------------
Description: Checks if this is greater than Item passed as parameter.
Pre-condition:	None.
Post-condition:  Returns true if greater than parameter */
bool Coin::operator>(const Comparable& c) const
{
    return c < *this;
}

/*	------------------------------==-------------------------------------
Description: Checks if two Items are equal
Pre-condition:	None.
Post-condition:  Returns true if equal*/
bool Coin::operator==(const Comparable& c) const
{
    const Coin& rhs = static_cast<const Coin&>(c);

    return type == rhs.type 
        && year == rhs.year 
        && grade == rhs.grade;
}

/*	--------------------------------!=----------------------------------
Description: Checks if two Items are not equal
Pre-condition:	None.
Post-condition:  Returns false if equal */
bool Coin::operator!=(const Comparable& c) const
{
    return !(c == *this);
}

/*	-------------------------------print---------------------------------
Description: Helper print method. Overrides base class so that Coin can
print its items unique to its containing data.
Pre-condition:	None.
Post-condition:  Returns formatted ostream */
ostream& Coin::print(ostream& out) const
{
    out << "Symbol: M, ";
    out << "Year: " << getYear() << ", ";
    out << "Grade: " << getGrade() << ", ";
    out << "Type: " << getType() << ", ";
    return out;
}
