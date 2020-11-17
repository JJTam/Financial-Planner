
#include "ledger.h"
#include <cmath>

Ledger::Ledger(int maxNumTrans, int currNumTrans) {
    this->maxNumTrans = maxNumTrans;
    this->currNumTrans = currNumTrans;
    this->allTransactions = nullptr;
}

Ledger::~Ledger() {
    if (allTransactions) {  // if have transactions
        for (int i = 1; i <= currNumTrans; ++i) {
            if (allTransactions[i]) {
                delete allTransactions[i];
                allTransactions[i] = nullptr;
            }
        }
        currNumTrans = 0;
        delete [] allTransactions;
        allTransactions = nullptr;
    }
}


/*
 * Helper function to check the equality of two transactions(amount, realized, date)
 * called by Ledger::updateTransactionInLedger
 */
bool equal(Transaction *thisTrans, Transaction *oldTrans) {
        bool checkAmount = fabs(thisTrans->getAmount() - oldTrans->getAmount()) < 0.00001;
        bool checkHasRealized = thisTrans->getHasRealized() == oldTrans->getHasRealized();
        bool checkDate = thisTrans->getDate() == oldTrans->getDate();

        // true if all are the same
        return (checkAmount && checkHasRealized && checkDate);
}


void Ledger::updateTransactionInLedger(Transaction* oldTrans, Transaction* newTrans) {
    // No matching old transaction found!
    if (allTransactions == nullptr || currNumTrans == 0) {
        return;
    }

    // here are 2 methods to do this task(use one only):
    // ===============================================================
    // method 1 (use helper function)
    for (int i = 1; i <= currNumTrans; ++i) {
/*        if (allTransactions[i] == oldTrans) {  // it may compare the address of two objects, but not sure it works or not
            allTransactions[i] = newTrans;  // shallow copying
            return;
        } */

        if (equal(allTransactions[i], oldTrans)) {  // call helper function
            allTransactions[i] = newTrans;  // shallow copying
            return;
        }

        if (i == currNumTrans) {
            cout << "No matching old transaction found!" << endl;
            return;
        }
    }

    // ===============================================================
    // method 2 (not use helper function)
/*    for (int i = 1; i <= currNumTrans; ++i) {  // check in details
        bool checkAmount = fabs(allTransactions[i]->getAmount() - oldTrans->getAmount()) < 0.00001;
        bool checkHasRealized = allTransactions[i]->getHasRealized() == oldTrans->getHasRealized();
        bool checkDate = allTransactions[i]->getDate() == oldTrans->getDate();
        if (checkAmount && checkHasRealized && checkDate) {  // if all are the same
            delete allTransactions[i];  // same as delete oldTrans;
            allTransactions[i] = newTrans;  // shallow copying
            return;
        }

        if (i == currNumTrans) {
            cout << "No matching old transaction found!" << endl;
            return;
        }
    }*/

}

void Ledger::addTransaction(Transaction* newTransaction) {  // added from account
    // Memory is full. Failed to add transaction!
    if (currNumTrans >= maxNumTrans) {
        cout << "Memory is full. Failed to add transaction!" << endl;
        return;
    }

    Transaction** newAllTransactions = new Transaction*[currNumTrans + 1];
    for (int i = 1; i <= currNumTrans; ++i)  // shallow copying from the old list, if old list is empty then skip
        newAllTransactions[i] = allTransactions[i];

    newAllTransactions[++currNumTrans] = newTransaction;  // add the new one, shallow copying

    if (currNumTrans != 1)  // if it has old list, then delete the old list container
        delete [] allTransactions;

    allTransactions = newAllTransactions;  // now, the old list point to the new list

}

void Ledger::printAllTransactions() const {
    // here are 2 methods to do this task(use one only):
    // ===============================================================
    // method 1
    if (allTransactions == nullptr || currNumTrans == 0) {
        cout << "Sorry, no transaction to print!" << endl;
        return;
    }

    else {
        for (int i = 1; i <= currNumTrans; ++i) {
            if (allTransactions[i]) {
                cout << *allTransactions[i];  // call operate<< function to print
            }
        }
    }

    // ===============================================================
    // method 2
/*    if (allTransactions) {
        for (int i = 1; i <= currNumTrans; ++i) {
            if (allTransactions[i]) {
                cout << *allTransactions[i];  // call operate<< function to print
            }
        }
    }

    // Sorry, no transaction to print!
    else {
        cout << "Sorry, no transaction to print!" << endl;
        return;
    }*/

}

void Ledger::printRecentNTrans(int nTrans) const {
    // Sorry, no transaction to print!
    if (allTransactions == nullptr || currNumTrans == 0) {
        cout << "Sorry, no transaction to print!" << endl;
        return;
    }

    if (nTrans > currNumTrans) {  // do nothing as Q&A said??
        return;
    }

    else {
        for (int i = 0; i < nTrans; ++i) {  // print the last N transactions
            cout << *allTransactions[currNumTrans - i];
        }
    }

}

void Ledger::removeSingleTransaction(int numTransact) {	// numTransact starts counting from 0
    // Sorry, no transaction to remove!
    if (currNumTrans <= 0) {
        cout << "Sorry, no transaction to remove!" << endl;
        return;
    }

    // Invalid transaction number!
    if (numTransact >= currNumTrans || numTransact < 0) {
	    cout << "Invalid transaction number!" << endl;
        return;
	}

    // here are 2 methods to do this task(use one only):
    // ===============================================================
    // method 1
    if (currNumTrans - 1 != 0) {
        Transaction** newAllTransactions = new Transaction*[--currNumTrans];  // a smaller pointer array
        for (int i = 0, j = 1; i < currNumTrans + 1; ++i) {
            if (i == numTransact) {  // it is the to be deleted one, just skip
                continue;
            }
            newAllTransactions[j] = allTransactions[i + 1];  // shallow copying
            ++j;
        }
        delete allTransactions[numTransact + 1];  // delete the target
        allTransactions[numTransact + 1] = nullptr;
        delete [] allTransactions;
        allTransactions = newAllTransactions;
    }

    else {   // If there are only one transaction, just deallocating the original list
        delete allTransactions[numTransact + 1];
        allTransactions[numTransact + 1] = nullptr;
        delete [] allTransactions;
        allTransactions = nullptr;
    }

    // ===============================================================
    // method 2
/*    int currNum = currNumTrans - 1;
    if (currNum == 0) {  // If there are only one transaction, calling destructor explicitly
        delete allTransactions[numTransact + 1];
        allTransactions[numTransact + 1] = nullptr;
        delete [] allTransactions;
        allTransactions = nullptr;
    }

    else {
        Transaction** newAllTransactions = new Transaction*[currNum];  // a smaller pointer array
        for (int i = 1; i <= numTransact; ++i) {
            newAllTransactions[i] = allTransactions[i];  // shallow copying the upper half
        }

        for (int j = numTransact + 1; j < currNumTrans; ++j) {
            newAllTransactions[j] = allTransactions[j + 1];  // shallow copying the lower half
        }

        --currNumTrans;
        delete allTransactions[numTransact + 1];  // delete the target
        allTransactions[numTransact + 1] = nullptr;
        delete [] allTransactions;
        allTransactions = newAllTransactions;
    }*/

}

void Ledger::printRealizedTransactions(bool realized) const {
    // There is no realized transaction.
    // There is no unrealized transaction.
    // Sorry, no transaction to remove!
    if (allTransactions == nullptr || currNumTrans == 0) {
        cout << "Sorry, no transaction to remove!" << endl;
        return;
    }

    int numOfRealized = 0;
    int numOfUnrealized = 0;
    // here are 2 methods to do this task(use one only):
    // ===============================================================
    // method 1
    for (int i = 1; i <= currNumTrans; ++i) {
        if (allTransactions[i]->getHasRealized() == realized) {
            cout << *allTransactions[i]; // print out the transactions that specified by the realized
            if (realized) {  // realized transactions checking
                ++numOfRealized;
            }
            else {  // unrealized transactions checking
                ++numOfUnrealized;
            }
        }

        if (i == currNumTrans && numOfRealized == 0 && realized) {
            cout << "There is no realized transaction." << endl;
        }
        else if (i == currNumTrans && numOfUnrealized == 0 && !realized) {
            cout << "There is no unrealized transaction." << endl;
        }
    }

    // ===============================================================
    // method 2
/*    if (realized) {  // realized transactions checking
        for (int i = 1; i <= currNumTrans; ++i) {
           if (allTransactions[i]->getHasRealized()) {
               cout << *allTransactions[i];  // print out realized transactions
               ++numOfRealized;
           }
           if (i == currNumTrans && numOfRealized == 0) {
               cout << "There is no realized transaction." << endl;
           }
        }
    }

    else {   // unrealized transactions checking
        for (int i = 1; i <= currNumTrans; ++i) {
            if (!allTransactions[i]->getHasRealized()) {
                cout << allTransactions[i];  // print out unrealized transactions
                ++numOfUnrealized;
            }
            if (i == currNumTrans && numOfUnrealized == 0) {
                cout << "There is no unrealized transaction." << endl;
            }
        }
    }*/

}

Transaction* Ledger::getTransactionByNum(int numTransact) {  // numTransact starts counting from 0
    //Sorry, no transaction to retrieve!
    if (allTransactions == nullptr || currNumTrans == 0) {
        cout << "Sorry, no transaction to retrieve!" << endl;
        return nullptr;
    }

    // Wrong transaction number! Cannot retrieve transactions!
    if (numTransact >= currNumTrans || numTransact < 0) {
        cout << "Wrong transaction number! Cannot retrieve transactions!" << endl;
        return nullptr;
    }

    return allTransactions[numTransact + 1];
}


int Ledger::getCurrNumTrans() const {
    return this->currNumTrans;
}