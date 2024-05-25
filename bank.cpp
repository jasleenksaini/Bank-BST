// Jasleen Kaur Saini
// Program 5

#include "bank.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// default constructor
Bank::Bank() {

}

// PHASE 1
// getline takes file input in line sections (phrases of char, string, int, ect.)
// use of istringstream and parse 
bool Bank::ReadTransactions(const string& file_name) {
    ifstream file(file_name);
    // error handling: file will not open 
    if (!file.is_open()) {
        cerr << "Cannot open " << file_name << endl;
        return false;
    }
    string command;
    while (getline(file, command)) {
        if (command.empty()) {
            break;
        }
        istringstream read(command);
        char transaction_type;
        read >> transaction_type;

        // char type input 
        // intializing all values 
        // open account 
        if (transaction_type == 'O') {
            // variables 
            int account_id;
            string last_name;
            string first_name;
            // take in
            read >> account_id >> last_name >> first_name;
            Transaction tran(transaction_type, account_id, last_name, first_name, true);
            transactions_.push(tran);
            // deposit and withdraw 
        } else if (transaction_type == 'D' || transaction_type == 'W') {
            int account_id;
            int fund_id;
            int amount;
            read >> account_id >> fund_id >> amount;
            Transaction tran(transaction_type, account_id, fund_id, amount, true);
            transactions_.push(tran);
            // transfer
        } else if (transaction_type == 'T') {
            int account_id;
            int fund_id;
            int transfer_account_id;
            int transfer_fund_id;
            int amount;
            read >> account_id >> fund_id >> transfer_account_id >> transfer_fund_id >> amount;
            Transaction tran(transaction_type, account_id, fund_id, transfer_account_id, transfer_fund_id, amount, true);
            transactions_.push(tran);
            // account history 
        } else if (transaction_type == 'H') {
            int account_id;
            read >> account_id;
            Transaction tran(transaction_type, account_id, true);
            transactions_.push(tran);
            // fund history 
        } else if (transaction_type == 'F') {
            int account_id;
            int fund_id;
            read >> account_id >> fund_id;
            Transaction tran(transaction_type, account_id, fund_id, true);
            transactions_.push(tran);
            // default/error handling 
        } else {
            cerr << "ERROR: Transaction Type is Invalid: " << transaction_type << std::endl;
        }
    }
    return true;
}

// PHASE 2 FUNCTIONS 
// display history functions 
void Bank::MainFundHistory(const Transaction& current, int account_id) {
    int fund_id = current.get_fund_id();
    Account *account;

    if (accounts_.Retrieve(account_id, account)) {
        account->TotalFundHistory(fund_id);
    } else {
        cerr << "ERROR: Invalid Information " << current.get_account_id() << " (Fund History Cannot be Printed)" << endl;
    }
}

void Bank::MainAccountHistory(const Transaction& current, int account_id) {
    Account *account;
    if (accounts_.Retrieve(account_id, account)) {
        account->TotalAccountHistory();
    } else {
        cerr << "ERROR: Invalid Account " << current.get_account_id() << " (Account History Cannot be Printed)" << endl;
    }
}

// PHASE 3 
// print all account created
// includes 0-8 funds 
// display function is member of binary search class, traversing through tree 
void Bank::Print() {
    cout << "Account Balances:" << endl;
    accounts_.Display();
    cout << endl; 
}

// DEBUGGING: use multiple functions to prevent errors 


// Process all transactions in the queue
void Bank::ExecuteTransactions() {
    while (!transactions_.empty()) {
        Transaction current = transactions_.front();
        transactions_.pop();

        int account_id = current.get_account_id();
        Account *account;

        switch (current.get_transaction_type()) {
          case 'W': {
                int fund_id = current.get_fund_id();
                int amount = current.get_amount();
                Account *account;
                if (accounts_.Retrieve(account_id, account)) {
                    account->Withdraw(current.get_transaction_type(), fund_id, account_id, 0, 0, amount);
                } else {
                    cerr << "ERROR: Account " << account_id << " not found (Withdraw Refused)" << endl;
                }
                break;
            }
          case 'D': {
                int fund_id = current.get_fund_id();
                int amount = current.get_amount();
                Account *account;
                if (accounts_.Retrieve(account_id, account)) {
                    account->Deposit(current.get_transaction_type(), account_id, fund_id, 0, 0, amount);
                } else {
                    cerr << "ERROR: Account " << account_id << " not found (Deposit Refused)" << endl;
                }
                break;
            }
          case 'T': {
                if (current.get_status()) {
                    int fund_id = current.get_fund_id();
                    int transfer_account_id = current.get_transfer_account_id();
                    int transfer_fund_id = current.get_transfer_fund_id();
                    int amount = current.get_amount();
                    Account *tran1; 
                    Account *tran2; 
                    if ((accounts_.Retrieve(account_id, tran1)) && (accounts_.Retrieve(transfer_account_id, tran2))) {
                        if (tran1->Withdraw(current.get_transaction_type(), fund_id, account_id, transfer_account_id, transfer_fund_id, amount)) {
                            tran2->Deposit(current.get_transaction_type(), transfer_account_id, transfer_fund_id, account_id, fund_id, amount);
                        }
                    } else {
                        if (accounts_.Retrieve(account_id, tran1)) 
                        {
                              cerr << "ERROR: Account " << transfer_account_id << " not found (Transfer Failed)" << endl;
                        } else 
                        {
                          cerr << "ERROR: Account " << account_id << " not found (Tranfer Failed)" << endl;
                        }
                    }
                }
                break;
            }
            case 'O': {
                Account *account;
                if (accounts_.Retrieve(account_id, account)) {
                    cerr << "ERROR: Account " << account_id << " is already open (Transaction Refused)" << endl;
                } else {
                    Account *tran = new Account(current.get_account_id(), current.get_first_name(), current.get_last_name());
                    accounts_.Insert(tran);
                }
                break;
            }
            case 'H':
                MainAccountHistory(current, account_id); 
                break;
            case 'F':
                MainFundHistory(current, account_id); 
                break;
            default:
                cerr << "ERROR: Invalid transaction type: " << current.get_transaction_type() << endl;
        }
    }
}


