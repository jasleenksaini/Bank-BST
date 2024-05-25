// Jasleen Kaur Saini
// Program 5

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction
{

public:
    // default 
    Transaction();

    // account history 
    Transaction(char transaction_type, int account_id, bool status);

    // fund history 
    Transaction(char transaction_type, int account_id, int fund_id, bool status);

    // deposit or withdraw
    Transaction(char transaction_type, int account_id, int fund_id, int amount, bool status);

    // open 
    Transaction(char transaction_type, int account_id, string last_name, string first_name, bool status);


    // transfer 
    Transaction(char transaction_type, int account_id, int fund_id, int transfer_acc_id, int transfer_fund_id, int amount, bool status);

    //getters
    string get_first_name() const;
    string get_last_name() const;

    bool get_status() const;

    char get_transaction_type() const;

    int get_account_id() const;
    int get_fund_id() const;
    int get_transfer_account_id() const;
    int get_transfer_fund_id() const;
    int get_amount() const;

    // stream overload
    friend ostream& operator<<(ostream& stream, const Transaction& tran);

private:
    // Private data members
    char transaction_type_;

    string last_name_;
    string first_name_;

    int account_id_;
    int fund_id_;
    int transfer_account_id_;
    int transfer_fund_id_;
    int amount_;

    bool status_; 
};
#endif