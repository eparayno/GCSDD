/*  ---------------------------------------------------------------------------
    SELL.CPP
    Derived class Sell with parent class Action
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Buy class: Derived class of Action.
        -- removes an item from the inventory*/

#include "Sell.h"
#include "Store.h"

/*	------------------------------Constructor-------------------------------
Description: Conventional constructor.
Pre-condition:	None.
Post-condition:	Creates Sell.*/
Sell::Sell()
{
}

/*	------------------------------Destructor-------------------------------
  Description: Conventional destructor.
  Pre-condition:	No longer in scope.
  Post-condition: Destructs class.*/
Sell::~Sell()
{
}

/*	--------------------------------create---------------------------------
Description: Allows for open ended principle
Pre-condition: Called by ActionFactory.
Post-condition: Returns Action pointer. */
Action* Sell::create() const
{
	return new Sell;
}

/*	--------------------------------runAction---------------------------------
Description: Uses data in Store to buy (add) an item to the inventory.
Pre-condition: Performed in factory.
Post-condition: Made appropriate changes to inventory and adds to customer
                history vector. */
void Sell::runAction(Store& store, const string& data)
{
    string dataString = data;

    // Get customer
    HashTable* lookUpTable = store.getCustomerDB()->getHashTable();
    this->customer = dynamic_cast<Customer*>(lookUpTable->getHashable(stoi(dataString.substr(0, 3))));

    if (this->customer != nullptr) {
        // Make temp item
        char type = dataString.at(5);
        Item* tempItem = store.getItemDB()->getFactory()->create(type);

        // Truncate string
        dataString.erase(0, 5);

        // Set count to 1
        dataString[0] = '1';

        if (tempItem != nullptr) { // only if its a legal item

            // set item data
            tempItem->setData(dataString);

            // Attempt to add into tree
            ItemSearchTree* tree = store.getItemDB()->getShelves()[tempItem->getPrecedence()];
            Comparable* comp = static_cast<Comparable*>(tempItem);
            bool remove = tree->remove(comp);

            this->item = static_cast<Item*>(tree->getComparable(comp));
            this->customer->addTransaction(this);

            delete comp;
        }
    }
}

/*	-------------------------------print---------------------------------
Description: Helper print method. Overrides base class so that Sell can
print its necessary messages.
Pre-condition:	None.
Post-condition:  Returns formatted ostream */
ostream& Sell::print(ostream& out) const
{
    if (customer != NULL && item != NULL) {
        out << "S, ";
        out << *customer << ", ";
        out << *item;
    }
    return out;
}
