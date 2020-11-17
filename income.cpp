
#include "income.h"

Income::Income(double amount, bool hasRealized, string date, TransactionCategory ic, GoesTo gt, string description)
        : Transaction(amount, hasRealized, date, description) {
    // Income with amount 5000 dated 11/10/2020 initialized.
    this->sources = ic;
    this->sumToWhere = gt;
}

Income::~Income() {
    // Income with 10000 dollars on 11/10/2020 deleted.
    cout << "Income with " << this->amount << " dollars on "
         << this->date << " deleted." << endl;
}

Income* Income::operator*(int salaryMultiplier) {
    // The transaction amount has been multiplied 2 times.
    this->amount = this->amount * salaryMultiplier;
    printf("The transaction amount has been multiplied %d times.\n", salaryMultiplier);
    return this;
}    

void Income::setGoesTo(GoesTo gt) {
    // Income has sent to 1
    this->sumToWhere = gt;
    cout << "Income has sent to " << this->sumToWhere << endl;
}

ostream& Income::printTransaction(ostream& out) const {
    // =====================================
    // Income: Part time salary
    // Income Date: 11/10/2020
    // Amount: 10000
    // Has been realized?: 1
    // Amount added into: Bank
    // =====================================
    out << "=====================================" << endl;
    out << "Income: " << this->descriptions << endl;
    out << "Income Date: " << this->date << endl;
    out << "Amount: " << this->amount << endl;
    out << "Has been realized?: " << this->hasRealized << endl;
    if (this->sumToWhere == GoesTo::BANK)
        out << "Amount added into: Bank" << endl;
    else if (this->sumToWhere == GoesTo::CASH)
        out << "Amount added into: Cash" << endl;
    else if (this->sumToWhere == GoesTo::CREDIT_CARD)
        out << "Amount added into: Credit Card" << endl;
    out << "=====================================" << endl;
    return out;
}

TransactionCategory Income::getCategory() const {
    // "Identifying which type of income is this..."
    cout << "Identifying which type of income is this..." << endl;
    return this->sources;
}

GoesTo Income::getGoesTo() const {
    // Identify where this income goes to...
    cout << "Identify where this income goes to..." << endl;
    return this->sumToWhere;
}