/*  ---------------------------------------------------------------------------
	ITEM.CPP
	Parent class for Coin, Comic, and SportsCard
	Authors: Erika Parayno
	---------------------------------------------------------------------------
	Store class: Base class for the different types of items sold in the store.
		-- Each item contains a count, year, precedence */

#include "Item.h"

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Creates new item. Initializes values. */
Item::Item() {
	year = 0000;
	count = 0;
	precedence = -1;
}

/*	-------------------------------getFactory-------------------------------
Description: Getter for precedence.
Pre-condition: N/A.
Post-condition:	Returns precedence. */
int& Item::getPrecedence()
{
	return precedence;
}

/*	--------------------------------getCount-------------------------------
Description: Getter for member count
Pre-condition:	None.
Post-condition:	Returns int count */
const int& Item::getCount() const
{
	return count;
}

/*	--------------------------------getYear-------------------------------
Description: Getter for member year
Pre-condition:	None.
Post-condition:	Returns year */
const int& Item::getYear() const
{
	return year;
}

/*	--------------------------------setCount-------------------------------
Description: Setter for member count
Pre-condition:	None.
Post-condition:	Changes count to parameter count */
void Item::setCount(const int& count)
{
	this->count = count;
}
