#include "Customer.h"
#include <iomanip>


Customer::Customer(const int& id, const string& firstName, const string& lastName) : Comparable() {
    ID = id;
    this->firstName = firstName;
    this->lastName = lastName;
}

Customer::~Customer() {
    for (int i = 0; i < history.size(); i++) {
        if (history[i] != NULL) {
            delete history[i];
        }
    }
    history.clear();
}

const int Customer::getID() const
{
    return ID;
}

const string Customer::getFirstName() const {
    return firstName;
}

const string Customer::getLastName() const {
    return lastName;
}


void Customer::printHistory() const {
    if (history.size() == 0) {
        cout << "   ";
        cout << "ID: " << ID << ", First Name: " << firstName << ", Last Name: " << lastName << ", ";
        cout << "Message: This customer has no transaction history." << endl;
    }
    else {
        for (int i = 0; i < history.size(); i++) {
            cout << *history[i] << endl;
        }
    }
}

bool Customer::operator<(const Comparable& rhs) const {
    const Customer& c = static_cast<const Customer&>(rhs);
    if (firstName < c.firstName)
        return true;
    if (c.firstName < firstName)
        return false;
    return lastName < c.lastName;
}

bool Customer::operator>(const Comparable& rhs) const {
    return rhs < *this;
}

bool Customer::operator==(const Comparable& rhs) const {
    const Customer& c = static_cast<const Customer&>(rhs);
    return ID == c.ID &&
        firstName == c.firstName &&
        lastName == c.lastName &&
        history == c.history;
}

bool Customer::operator!=(const Comparable& rhs) const {
    return !(rhs == *this);
}

ostream& Customer::print(ostream& out) const
{
    out << "ID: " << std::setfill('0') << std::setw(3) << getID() << ", ";
    out << "First Name: " << getFirstName() << ", ";
    out << "Last Name: " << getLastName() << ", ";
    return out;
}

void Customer::addTransaction(Action* transaction) {
    history.push_back(transaction);
}