
#include "expenses.h"

Expenses::Expenses(double amount, bool hasRealized, string date, TransactionCategory ic, GoesTo gt, string description)
            : Transaction(amount, hasRealized, date, description) {
    // Expense with amount -200 dated 20/10/2020 initialized.
    this->sources = ic;
    this->sumToWhere = gt;
    cout << "Expense with amount " << this->amount
         << " dated " << this->date << " initialized." << endl;

}

Expenses::~Expenses() {
    // Expenses with -200 dollars on 20/10/2020 deleted.
    cout << "Expenses with " << this->amount << " dollars on "
         << this->date << " deleted." << endl;
}

void Expenses::setGoesTo(GoesTo gt) {
    // Expenses has sent to 1
    this->sumToWhere = gt;
    cout << "Expenses has sent to " << this->sumToWhere << endl;
}

ostream& Expenses::printTransaction(ostream& out) const {
    // =====================================
    // Expenses: Friend's birthday presents
    // Expenses Date: 11/10/2020
    // Amount: -150
    // Has been realized?: 0
    // Amount added into: Bank
    // =====================================
    out << "=====================================" << endl;
    out << "Expenses: " << this->descriptions << endl;
    out << "Expenses Date: " << this->date << endl;
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

TransactionCategory Expenses::getCategory() const {
    // Identifying which type of expenses is this...
    cout << "Identifying which type of expenses is this..." << endl;
    return this->sources;
}

GoesTo Expenses::getGoesTo() const {
    // Identify where this expense goes to...
    cout << "Identify where this expense goes to..." << endl;
    return this->sumToWhere;
}