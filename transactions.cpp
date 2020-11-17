
#include "transactions.h"

Transaction::Transaction(double amount, bool hasRealized, string date, string describe) {
    this->amount = amount;
    this->hasRealized = hasRealized;
    this->date = date;
    this->descriptions = describe;
}

Transaction::~Transaction() {
    // Transaction with 1200 dollars on 11/10/2020 deleted.
    cout << "Transaction with " << this->amount
         << "dollars on " << this->date << " deleted." << endl;
}

ostream& operator<< (ostream &out, const Transaction &trans) {
    return trans.printTransaction(out);
}

void Transaction::setAmount(double amount) {
    // Transaction with 1200 dollars on 11/10/2020 added.
    this->amount = amount;
    cout << "Transaction with " << this->amount
         << "dollars on " << this->date << " added." << endl;
}

double Transaction::getAmount() const {
    return this->amount;
}

bool Transaction::getHasRealized() {
    return this->hasRealized;
}

void Transaction::setHasRealized() {
    // The transaction has realized already!
    this->hasRealized = true;
    cout << "Transaction has realized already!" << endl;
}

void Transaction::setDescriptions(string str) {
    this->descriptions = str;
}

void Transaction::setDate(string str) {
    this->date = str;
}

string Transaction::getDescriptions() const {
    return this->descriptions;
}

string Transaction::getDate() const {
    return this->date;
}