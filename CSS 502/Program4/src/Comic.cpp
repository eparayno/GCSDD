/*  ---------------------------------------------------------------------------
    COMIC.CPP
    Derived class Comic with parent class Item
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Coin class: Derived class of item.
        -- Sorted by publisher, title, year, and grade */

#include "Comic.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

/*	------------------------------Destructor-------------------------------
  Description: Conventional destructor.
  Pre-condition:  No longer in scope.
  Post-condition: Destructs class and all items.*/
Comic::~Comic() {}

/*	--------------------------------create---------------------------------
Description: Allows for open ended principle
Pre-condition: Called by ItemFactory.
Post-condition: rreturns item pointer. */
Item* Comic::create() const
{
    return new Comic;
}

/*	-----------------------------Constructor-------------------------------
Description: Default constructor for class SportsCards
Pre-condition: Called by Create function.
Post-condition: Created new Comic*/
Comic::Comic()
{
}

/*	-----------------------------Constructor-------------------------------
Description: Sets data using string of data
Pre-condition: Called by Manager class after it creates new Comic.
Post-condition:	Comic data set with corresponding precedence defined and
                count initialized. Also set year, publisher, title,
                and grade based on parameter values */
void Comic::setData(const string& data) {

    vector<string> dataSet;
    stringstream line(data);
    string part;

    while (getline(line, part, ',')) {
        dataSet.push_back(part);
    }

    this->count = stoi(dataSet[0]);
    this->year = stoi(dataSet[1]);
    this->grade = dataSet[2];
    this->title = dataSet[3];
    this->publisher = dataSet[4];

    this->precedence = 1;

    dataSet.clear();
}

/*	-------------------------------getPublisher----------------------------
Description: Getter for member publisher
Pre-condition:	None.
Post-condition:	Returns string publisher */
const string Comic::getPublisher() const
{
	return publisher;
}

/*	---------------------------------getTitle------------------------------
Description: Getter for member title
Pre-condition:	None.
Post-condition:	Returns string title */
const string Comic::getTitle() const
{
	return title;
}

/*	--------------------------------getGrade-------------------------------
Description: Getter for member grade
Pre-condition:	None.
Post-condition:	Returns string grade */
const string Comic::getGrade() const
{
	return grade;
}

/*	----------------------------------<------------------------------------
Description:  Checks if this is lesser than Item passed as parameter.
Pre-condition:	None.
Post-condition:  Returns true if less than parameter*/
bool Comic::operator<(const Comparable& c) const
{
    const Comic& rhs = static_cast<const Comic&>(c);

    // compare publisher
    if (publisher < rhs.publisher)
        return true;
    if (rhs.publisher < publisher)
        return false;

    // compare by title
    if (title < rhs.title)
        return true;
    if (rhs.title < title)
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
bool Comic::operator>(const Comparable& c) const
{
	return c < *this;
}

/*	------------------------------==-------------------------------------
Description: Checks if two Items are equal
Pre-condition:	None.
Post-condition:  Returns true if equal*/
bool Comic::operator==(const Comparable& c) const
{
    const Comic& rhs = static_cast<const Comic&>(c);

    return publisher == rhs.publisher 
        && title == rhs.title 
        && year == rhs.year 
        && grade == rhs.grade;
}

/*	--------------------------------!=----------------------------------
Description: Checks if two Items are not equal
Pre-condition:	None.
Post-condition:  Returns false if equal */
bool Comic::operator!=(const Comparable& c) const
{
	return !(c == *this);
}

ostream& Comic::print(ostream& out) const
{
    out << "Symbol: C, ";
    out << "Year: " << getYear() << ", ";
    out << "Grade: " << getGrade() << ", ";
    out << "Title: " << getTitle() << ", ";
    out << "Publisher: " << getPublisher();
    return out;
}
