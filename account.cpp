#include "account.h"
#include <string>
#include <iostream>
using namespace std;

Account::Account(double bank, double creditCard, double cash)
{
    // Initialization of account succeed! There are two ledger: Income and Expenses.
    // ==========Account Summary==========
    // Maximum #. transactions allowed for each ledger: 100
    // Current #. transactions allowed for each ledger: 100
    // Current bank balance: 1000
    // Current credit card balance: 1000
    // Current cash balance: 1000
    //
    this->bankBalance = bank;
    this->creditCardBalance = creditCard;
    this->cashBalance = cash;
    this->incomeLedger = nullptr;
    this->expensesLedger = nullptr;
    cout << "Initialization of account succeed! There are two ledger: Income and Expenses." << endl;
    cout << "==========Account Summary==========" << endl;
    cout << "Maximum #. transactions allowed for each ledger: " << this->maxNumTrans << endl;
    cout << "Current #. transactions allowed for each ledger: " << this->maxNumTrans << endl;
    cout << "Current bank balance: " << this->bankBalance << endl;
    cout << "Current credit card balance: " << this->creditCardBalance << endl;
    cout << "Current cash balance: " << this->cashBalance << endl;
}

Ledger* Account::getIncomeLedger() {
    return this->incomeLedger;
}

Ledger* Account::getExpensesLedger() {
    return this->expensesLedger;
}


void Account::addBalance(int option, double amount) {
    if (option == 0) {
        bankBalance += amount;
    }
    else if (option == 1) {
        cashBalance += amount;
    }
    else if (option == 2) {
        creditCardBalance += amount;
    }
    else {
        cout << "Wrong balance option number!" << endl;
    }
}


void Account::updateLedger(Transaction* oldTrans, Transaction* newTrans){
    // New and Old transaction types not matching!
    // Fail to insert records!
    // Successfully updated.
}

void Account::addTransactionToLedger(Transaction* newTransact){
    // 5000 added into Bank.
    // 5000 added into Cash.
    // 5000 added into Credit Card.
    // Oh no! Not enough money to spend! :(
    // Fail to add the transaction! >.<
}

void Account::removeTransactionFromLedger(Ledger* led, int numTransact){
    // Error! No transactions in this ledger!
    // An transaction has been removed successfully
    
}

void Account::printBalance() const {
    // Printing Balances
    // Bank: 10850
    // Credit Card: 1000
    // Cash: 800
    cout << "Printing Balances" << endl;
    cout << "Bank: " << this->bankBalance << endl;
    cout << "Credit Card: " << this->creditCardBalance << endl;
    cout << "Cash: " << this->cashBalance << endl;

}

Account::~Account() {
    // All account records deleted.
    if (incomeLedger) {
        delete incomeLedger;
        incomeLedger = nullptr;
    }

    if (expensesLedger) {
        delete expensesLedger;
        expensesLedger = nullptr;
    }

    cout << "All account records deleted." << endl;
}
