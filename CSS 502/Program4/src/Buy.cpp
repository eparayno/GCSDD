/*  ---------------------------------------------------------------------------
    BUY.CPP
    Derived class Buy with parent class Action
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Buy class: Derived class of Action.
        -- adds item to the inventory*/

#include "Buy.h"
#include "Store.h"

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Creates Buy.*/
Buy::Buy()
{
}

/*	--------------------------------create---------------------------------
Description: Allows for open ended principle
Pre-condition: Called by ActionFactory.
Post-condition: Returns Action pointer. */
Action* Buy::create() const
{
	return new Buy;
}

/*	------------------------------Destructor-------------------------------
  Description: Conventional destructor.
  Pre-condition:	No longer in scope.
  Post-condition: Destructs class.*/
Buy::~Buy()
{
}

/*	--------------------------------runAction---------------------------------
Description: Uses data in Store to buy (add) an item to the inventory.
Pre-condition: Performed in factory.
Post-condition: Made appropriate changes to inventory and adds to customer
                history vector*/
void Buy::runAction(Store& store, const string& data)
{
    string dataString = data;

    // Get customer
    HashTable* lookUpTable = store.getCustomerDB()->getHashTable();
    this->customer = dynamic_cast<Customer*>(lookUpTable->getHashable(stoi(dataString.substr(0,3))));

    // Make temp item
    char type = dataString.at(5); 
    Item* tempItem = store.getItemDB()->getFactory()->create(type);

    // Truncate string
    dataString.erase(0, 5);

    // Set count to 1
    dataString[0] = '1';

    // set item data
    tempItem->setData(dataString);

    // Attempt to add into tree
    ItemSearchTree* tree = store.getItemDB()->getShelves()[tempItem->getPrecedence()];
    Comparable* temp = static_cast<Comparable*>(tempItem);
    bool added = tree->add(temp);
    
    this->item = static_cast<Item*>(tree->getComparable(temp));
    this->customer->addTransaction(this);

    if (!added) {
        delete temp;
    }

}

/*	-------------------------------print---------------------------------
Description: Helper print method. Overrides base class so that Buy can
print its necessary messages.
Pre-condition:	None.
Post-condition:  Returns formatted ostream */
ostream& Buy::print(ostream& out) const
{

    if (customer != NULL && item != NULL) {
        out << "B, ";
        out << *customer;
        out << *item;
    }
    return out;

}

