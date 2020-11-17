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
    this->incomeLedger = new Ledger(this->maxNumTrans, 0);
    this->expensesLedger = new Ledger(this->maxNumTrans, 0);
    cout << "Initialization of account succeed! There are two ledger: Income and Expenses." << endl;
    cout << "==========Account Summary==========" << endl;
    cout << "Maximum #. transactions allowed for each ledger: " << this->maxNumTrans << endl;
    cout << "Current #. transactions allowed for each ledger: " << this->maxNumTrans << endl;
    cout << "Current bank balance: " << this->bankBalance << endl;
    cout << "Current credit card balance: " << this->creditCardBalance << endl;
    cout << "Current cash balance: " << this->cashBalance << endl << endl;
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


void Account::updateLedger(Transaction* oldTrans, Transaction* newTrans) {
    // New and Old transaction types not matching!
    // Fail to insert records!
    // Successfully updated.
    if (oldTrans && newTrans) {  // cannot be null
        if (dynamic_cast<Income*>(oldTrans) && dynamic_cast<Income*>(newTrans)) {  // same Income type
            this->incomeLedger->updateTransactionInLedger(oldTrans, newTrans);
        }
        else if (dynamic_cast<Expenses*>(oldTrans) && dynamic_cast<Expenses*>(newTrans)) {  // same Expenses type
            this->expensesLedger->updateTransactionInLedger(oldTrans, newTrans);
        }
        else {
            cout << "New and Old transaction types not matching!" << endl;
            cout << "Fail to insert records!" << endl;
            return;
        }

        // here are 2 methods to do this task(use one only):
        // ===============================================================
        // method 1
        // balance = balance - old && balance = balance + new
        switch (oldTrans->getGoesTo()) {
            case GoesTo::BANK:
                this->bankBalance -= oldTrans->getAmount();
                break;

            case GoesTo::CREDIT_CARD:
                this->creditCardBalance -= oldTrans->getAmount();
                break;

            case GoesTo::CASH:
                this->cashBalance -= oldTrans->getAmount();
                break;
        }

        switch (newTrans->getGoesTo()) {
            case GoesTo::BANK:
                this->bankBalance += newTrans->getAmount();
                break;

            case GoesTo::CREDIT_CARD:
                this->creditCardBalance += newTrans->getAmount();
                break;

            case GoesTo::CASH:
                this->cashBalance += newTrans->getAmount();
                break;
        }

        delete oldTrans;  // delete the old transaction
        cout << "Successfully updated." << endl;

        // ===============================================================
        // method 2
        // balance = balance - old && balance = balance + new
/*        int goTo = oldTrans->getGoesTo();
        double oldAmount = oldTrans->getAmount();
        if (goTo == GoesTo::BANK) {
            this->bankBalance -= oldAmount;
        }
        else if (goTo == GoesTo::CREDIT_CARD) {
            this->creditCardBalance -= oldAmount;
        }
        else {
            this->cashBalance -= oldAmount;
        }

        goTo = newTrans->getGoesTo();
        double newAmount = newTrans->getAmount();
        if (goTo == GoesTo::BANK) {
            this->bankBalance += newAmount;
        }
        else if (goTo == GoesTo::CREDIT_CARD) {
            this->creditCardBalance += newAmount;
        }
        else {
            this->cashBalance += newAmount;
        }

        delete oldTrans;  // delete the old transaction
        cout << "Successfully updated" << endl;*/

    }
}

void Account::addTransactionToLedger(Transaction* newTransact) {
    // 5000 added into Bank.
    // 5000 added into Cash.
    // 5000 added into Credit Card.
    // Oh no! Not enough money to spend! :(
    // Fail to add the transaction! >.<
    // Transaction amount 5000 added

    if (newTransact) {  // not null
        // here are 2 methods to do this task(use one only):
        // ===============================================================
        // method 1 (no use local variables and use switch)
        if (dynamic_cast<Income *>(newTransact)) {  // income transaction
            switch (newTransact->getGoesTo()) {
                case GoesTo::BANK:
                    this->bankBalance += newTransact->getAmount();
                    cout << newTransact->getAmount() << " added into Bank." << endl;
                    break;

                case GoesTo::CREDIT_CARD:
                    this->creditCardBalance += newTransact->getAmount();
                    cout << newTransact->getAmount() << " added into Credit Card." << endl;
                    break;

                case GoesTo::CASH:
                    this->cashBalance += newTransact->getAmount();
                    cout << newTransact->getAmount() << " added into Cash." << endl;
                    break;
            }
            incomeLedger->addTransaction(newTransact);  // call Ledger::addTransaction
            cout << "Transaction amount " << newTransact->getAmount() << " added" << endl;
        }
        else if (dynamic_cast<Expenses *>(newTransact)) {  // expenses transaction
            switch (newTransact->getGoesTo()) {
                case GoesTo::BANK:
                    if (this->bankBalance < -newTransact->getAmount()) {
                        cout << "Oh no! Not enough money to spend! :(" << endl;
                        delete newTransact;  // delete the new Transaction before return
                        return;
                    }

                    this->bankBalance += newTransact->getAmount();
                    cout << newTransact->getAmount() << " added into Bank." << endl;
                    break;

                case GoesTo::CREDIT_CARD:
                    if (this->creditCardBalance < -newTransact->getAmount()) {
                        cout << "Oh no! Not enough money to spend! :(" << endl;
                        delete newTransact;  // delete the new Transaction before return
                        return;
                    }

                    this->creditCardBalance += newTransact->getAmount();
                    cout << newTransact->getAmount() << " added into Credit Card." << endl;
                    break;

                case GoesTo::CASH:
                    if (this->cashBalance < -newTransact->getAmount()) {
                        cout << "Oh no! Not enough money to spend! :(" << endl;
                        delete newTransact;  // delete the new Transaction before return
                        return;
                    }
                    this->cashBalance += newTransact->getAmount();
                    cout << newTransact->getAmount() << " added into Cash." << endl;
                    break;
            }

            expensesLedger->addTransaction(newTransact);
            cout << "Transaction amount " << newTransact->getAmount() << " added" << endl;
        }
        else {
            cout << "Fail to add the transaction! >.<" << endl;
        }

        // ===============================================================
        // method 2 (use local variables and use if condition)
        /*    if (dynamic_cast<Income*>(newTransact)) {  // income transaction
            int goTo = newTransact->getGoesTo();
            double amount = newTransact->getAmount();

            if (goTo == GoesTo::BANK) {
                this->bankBalance += amount;
                cout << amount << " added into Bank." << endl;
            }
            else if (goTo == GoesTo::CREDIT_CARD) {
                this->creditCardBalance += amount;
                cout << amount << " added into Credit Card." << endl;
            }
            else {
                this->cashBalance += amount;
                cout << amount << " added into Cash." << endl;
            }
            incomeLedger->addTransaction(newTransact);  // call Ledger::addTransaction
            cout << "Transaction amount " << amount << " added" << endl;
        }

        else if (dynamic_cast<Expenses*>(newTransact)) {  // expenses transaction
            int goTo = newTransact->getGoesTo();
            double amount = newTransact->getAmount();
            if (goTo == GoesTo::BANK) {
                if (this->bankBalance < -amount) {
                    cout << "Oh no! Not enough money to spend! :(" << endl;
                    delete newTransact;  // delete the new Transaction before return
                    return;
                }
                this->bankBalance += amount;
                cout << amount << " added into Bank." << endl;
            }
            else if (goTo == GoesTo::CREDIT_CARD) {
                if (this->creditCardBalance < -amount) {
                    cout << "Oh no! Not enough money to spend! :(" << endl;
                    delete newTransact;  // delete the new Transaction before return
                    return;
                }
                this->creditCardBalance += amount;
                cout << amount << " added into Credit Card." << endl;
            }
            else {
                if (this->cashBalance < -amount) {
                    cout << "Oh no! Not enough money to spend! :(" << endl;
                    delete newTransact;  // delete the new Transaction before return
                    return;
                }
                this->cashBalance += amount;
                cout << amount << " added into Cash." << endl;
            }
            expensesLedger->addTransaction(newTransact);
            cout << "Transaction amount " << amount << " added" << endl;
        }

        else {
            cout << "Fail to add the transaction! >.<" << endl;
        }*/

    }
}

void Account::removeTransactionFromLedger(Ledger* led, int numTransact) {
    // Error! No transactions in this ledger!
    // An transaction has been removed successfully
    if (led->getCurrNumTrans() == 0) {
        cout << "Error! No transactions in this ledger!" << endl;
        return;
    }

    // here are 2 methods to do this task(use one only):
    // ===============================================================
    // method 1 (no use local variables and use switch)
    // method 2 (use local variables and use if condition)
    Transaction* removeTransact = led->getTransactionByNum(numTransact);
    if (removeTransact) {  // successfully retrieve a transaction
        switch (removeTransact->getGoesTo()) {
            case GoesTo::BANK:
                this->bankBalance += removeTransact->getAmount();
                break;

            case GoesTo::CREDIT_CARD:
                this->creditCardBalance += removeTransact->getAmount();
                break;

            case GoesTo::CASH:
                this->cashBalance += removeTransact->getAmount();
                break;
        }

        led->removeSingleTransaction(numTransact);  // call Ledger::removeSingleTransaction
        cout << "An transaction has been removed successfully." << endl;
    }
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
