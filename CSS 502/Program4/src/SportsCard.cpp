#include "SportsCard.h"
#include <iomanip>
/*	------------------------------Destructor-------------------------------
  Description: Conventional destructor.
  Pre-condition:  No longer in scope.
  Post-condition: Destructs class and all items it contains.*/
SportsCard::~SportsCard()
{
}

/*	--------------------------------create---------------------------------
Description: Maintains open-ended principle.
Pre-condition: Called by ItemFactory.
Post-condition: Returns item pointer */
Item* SportsCard::create() const
{
    return new SportsCard;
}
/*	-----------------------------Constructor-------------------------------
Description: Default constructor for class SportsCards
Pre-condition: Called by Create function.
Post-condition:	Created new SportsCard */
SportsCard::SportsCard() {}

/*	-------------------------------setData-------------------------------
Description: Sets data using string of data
Pre-condition: Called by Manager class after it creates new SportsCard.
Post-condition:	New SportsCards created with corresponding precedence defined
                and count initialized. Also set year, manufacturer,
                player, and grade based on parameter values */
void SportsCard::setData(const string& data)
{
    vector<string> dataSet;
    stringstream line(data);
    string part;

    while (getline(line, part, ',')) {
        dataSet.push_back(part);
    }

    this->count = stoi(dataSet[0]);
    this->year = stoi(dataSet[1]);
    this->grade = dataSet[2];
    this->player = dataSet[3];
    this->manufacturer = dataSet[4];

    this->precedence = 2;
    line.str(string());
    dataSet.clear();
}

/*	---------------------------------getPlayer-----------------------------
Description: Getter for member player
Pre-condition:	None.
Post-condition:	Returns string player */
const string SportsCard::getPlayer() const
{
	return player;
}

/*	---------------------------------getPublisher--------------------------
Description: Getter for member publisher
Pre-condition:	None.
Post-condition:	Returns string publisher */
const string SportsCard::getManufacturer() const
{
	return manufacturer;
}

const string SportsCard::getGrade() const
{
	return grade;
}

/*	----------------------------------<------------------------------------
Description:  Checks if this is lesser than Item passed as parameter.
Pre-condition:	None.
Post-condition:  Returns true if less than parameter*/
bool SportsCard::operator<(const Comparable& c) const
{
    const SportsCard& rhs = static_cast<const SportsCard&>(c);

    // compare by player
    if (player < rhs.player)
        return true;
    if (rhs.player < player)
        return false;

    // compare by year
    if ((*this).year < rhs.year)
        return true;
    if (rhs.year < (*this).year)
        return false;

    // compare by manufacturer
    if (manufacturer < rhs.manufacturer)
        return true;
    if (rhs.manufacturer < manufacturer)
        return false;

    // compare by grade
    return grade < rhs.grade;
}

/*	-------------------------------->-------------------------------------
Description: Checks if this is greater than Item passed as parameter.
Pre-condition:	None.
Post-condition:  Returns true if greater than parameter */
bool SportsCard::operator>(const Comparable& c) const
{
	return c < *this;
}

/*	------------------------------==-------------------------------------
Description: Checks if two Items are equal
Pre-condition:	None.
Post-condition:  Returns true if equal*/
bool SportsCard::operator==(const Comparable& c) const
{
    const SportsCard& rhs = static_cast<const SportsCard&>(c);

    return player == rhs.player 
        && year == rhs.year 
        && manufacturer == rhs.manufacturer 
        && grade == rhs.grade;
}

/*	--------------------------------!=----------------------------------
Description: Checks if two Items are not equal
Pre-condition:	None.
Post-condition:  Returns false if equal */
bool SportsCard::operator!=(const Comparable& c) const
{
	return !(c == *this);
}

std::ostream& SportsCard::print(ostream& out) const
{
    out << "Symbol: S, ";
    out << "Year: " << getYear() << ", ";
    out << "Grade: " << getGrade() << ", ";
    out << "Player: " << getPlayer() << ", ";
    out << "Manufacturer: " << getManufacturer();
    return out;
}

