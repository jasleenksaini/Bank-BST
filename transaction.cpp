// Jasleen Kaur Saini
// Program 5

#include "transaction.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// default constructor 
Transaction::Transaction() {

}

// input-type constructors 
Transaction::Transaction(char transaction_type, int account_id, bool status) 
{
  transaction_type_ = transaction_type;
  account_id_ = account_id;
  status_ = status;
}

Transaction::Transaction(char transaction_type, int account_id, int fund_id, bool status) 
{
  transaction_type_ = transaction_type;
  account_id_ = account_id;
  fund_id_ = fund_id;
  status_ = status;
}

Transaction::Transaction(char transaction_type, int account_id, int fund_id, int amount, bool status) 
{
  transaction_type_ = transaction_type;
  account_id_ = account_id;
  fund_id_ = fund_id;
  amount_ = amount;
  status_ = status;
}

Transaction::Transaction(char transaction_type, int account_id, string last_name, string first_name, bool status) 
{
  transaction_type_ = transaction_type;
  account_id_ = account_id;
  last_name_ = last_name;
  first_name_ = first_name;
  status_ = status;
}

Transaction::Transaction(char transaction_type, int account_id, int fund_id, int transfer_acc_id, int transfer_fund_id, int amount, bool status) 
{
  transaction_type_ = transaction_type;
  account_id_ = account_id;
  fund_id_ = fund_id;
  transfer_account_id_ = transfer_acc_id;
  transfer_fund_id_ = transfer_fund_id;
  amount_ = amount;
  status_ = status;
}


// getters
string Transaction::get_first_name() const 
{ 
    return first_name_; 
}
string Transaction::get_last_name() const 
{ 
    return last_name_; 
}

char Transaction::get_transaction_type() const 
{ 
    return transaction_type_; 
}

int Transaction::get_account_id() const 
{ 
    return account_id_; 
}

int Transaction::get_fund_id() const 
{ 
    return fund_id_; 
}

int Transaction::get_transfer_account_id() const 
{ 
    return transfer_account_id_; 
}

int Transaction::get_transfer_fund_id() const 
{ 
    return transfer_fund_id_; 
}

int Transaction::get_amount() const 
{ 
    return amount_; 
}

bool Transaction::get_status() const 
{ 
    return status_; 
}

// stream overload 
ostream &operator<<(ostream &stream, const Transaction &tran) 
{
    if (tran.get_status()) 
    {
        char transaction_type = tran.get_transaction_type();
        if (transaction_type == 'D' || transaction_type == 'W') 
        {
            stream << ' ' << transaction_type << ' ' << tran.get_account_id() << ' ' << tran.get_fund_id() << ' ' << tran.get_amount();
       
       
        } 
        else if (transaction_type == 'T') 
        {
            stream << ' ' << transaction_type << ' ' << tran.get_account_id() << ' ' << tran.get_fund_id() << ' '
                   << tran.get_transfer_account_id() << ' ' << tran.get_transfer_fund_id() << ' ' << tran.get_amount();
        
        
        } 
        else if (transaction_type == 'O') 
        {
            stream << "Opened an account for " << tran.get_account_id() << endl;
        
        
        } 
        else 
        {
            stream << ' ' << transaction_type << " is an invalid transaction type.";
        }
    } 
    else 
    {
        char transaction_type = tran.get_transaction_type();
        if (transaction_type == 'O') 
        {
            stream << "Account " << tran.get_account_id() << " already exists" << endl;
        
        
        } 
        else 
        {
            
            stream << ' ' << transaction_type << ' ' << tran.get_account_id() << ' ';
            
            if (transaction_type == 'T') 
            {
                stream << tran.get_fund_id() << ' ' << tran.get_transfer_account_id() << ' ' << tran.get_transfer_fund_id() << ' ';
            
            
            } 
            else 
            {
                stream << tran.get_fund_id() << ' ';
            }

            stream << tran.get_amount() << " (Transaction Failed)";
        }
    }
    return stream << endl;
}

