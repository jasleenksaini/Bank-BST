// Jasleen Kaur Saini
// Program 5

#include "account.h"
#include "transaction.h"

#include <string>
#include <vector>

using namespace std;

// Default constructor
Account::Account() 
{

}

// constructor "O": creation of new account 
Account::Account(int account_id, string first_name, string last_name) 
{
  account_id_ = account_id;
  first_name_ = first_name;
  last_name_ = last_name;

  Transaction transaction('O', account_id, last_name, first_name, true);
  account_history_.push_back(transaction);

  // set fund characteristics 
  // fund name (0-8), $200 in fund 0 
  for (int i = 0; i < 9; i++) 
  {
    fund_[i] = kFundList_[i];
  }
  fund_[0].Add(200);
  // create transaction 
  Transaction d_transaction('D', account_id, 0, 200, true);
} 

// getters
string Account::get_fund_name(int fund_id) const 
{ 
  return kFundList_[fund_id]; 
} 

string Account::get_first_name() const 
{ 
  return first_name_; 
}

string Account::get_last_name() const 
{ 
  return last_name_; 
}

int Account::get_account_id() const 
{ 
  return account_id_; 
}

// actions/functions
bool Account::FundValid(int fund_id) 
{
  int fund_num = fund_id;

  if (fund_num < 0 || fund_num >= 9 ) 
  {
    return true;
  } else 
  {
    return false;
  }
}

// history functions
void Account::TotalAccountHistory() 
{
cout << "Transaction History for " << first_name_ << " " << last_name_  <<  " by fund" << endl;

  for (int i = 0; i < 9; i++) 
  {
    fund_[i].AccountHistory();
  }
cout << endl; 
}

void Account::TotalFundHistory(int fund_id) 
{

  if (FundValid(fund_id)) 
  {
    cerr << "ERROR: Invalid Fund ID: " << fund_id << endl;

  } else 
  {

    cout << "Transaction History for " << first_name_ << " " << last_name_ << " " << fund_[fund_id].get_fund_name() << ": $" << fund_[fund_id].get_balance() << endl;
    for (Transaction transaction : fund_[fund_id].get_transaction()) 
    {
      cout << "    " << transaction;
    }
    cout << endl; 
  }
}

// Overloaded stream insertion operator to print account information
ostream &operator<<(ostream &cout, const Account &rhs) {
  cout << rhs.get_first_name() << " " << rhs.get_last_name() << " Account ID: " << rhs.get_account_id() << endl;

  for (int i = 0; i < 9; i++) {
    cout << "    " << rhs.fund_[i].get_fund_name() << ": " << "$" << rhs.fund_[i].get_balance() << endl;
  }
  
  return cout;
}

// error handling: linked funds 
// getter to fund number 
// check if a fund is linked with another
// get the total balance of linked funds
int Account::get_linked_fund(int fund_id) const 
{
    if (fund_id == 0) 
    {
        return 1;
    } else if (fund_id == 1) 
    {
        return 0;
    } else if (fund_id == 2) 
    {
        return 3;
    } else if (fund_id == 3) 
    {
        return 2;
    } else 
    {
        return -1;
    }
} 
bool Account::linked_fund_check(int fund_id) const 
{
  return
  (fund_id == 0 && get_linked_fund(fund_id) == 1) || 
  (fund_id == 1 && get_linked_fund(fund_id) == 0) ||
  (fund_id == 2 && get_linked_fund(fund_id) == 3) || 
  (fund_id == 3 && get_linked_fund(fund_id) == 2);
}

int Account::linked_balance(int fund_id) const 
{
  int linked_fund = get_linked_fund(fund_id);
  return fund_[fund_id].get_balance() + fund_[linked_fund].get_balance();
} 


// main functions: test 

bool Account::Deposit(char transaction_type, int account_id, int fund_id, int transfer_account_id, int transfer_fund_id, int amount) 
{
  if (FundValid(fund_id)) 
  {
    cerr << "ERROR: Invalid Fund ID: " << fund_id << " for Account: " << account_id << " (Deposit or Transfer Failed)" << endl;
    return false;
  }
  if (transaction_type == 'D') 
  {
      return FundDeposit(fund_id, amount);
  } else if (transaction_type == 'T') 
  {
      return Transfer(fund_id, transfer_account_id, transfer_fund_id, amount);
  } else 
  {
      cerr << "ERROR: Invalid Transaction Type: '" << transaction_type << "' (Deposit or Transfer Failed)" << endl;
      return false;
}
} 

bool Account::FundDeposit(int fund_id, int amount) 
{
  // error handling 
  if (amount < 0) 
  {
    cerr << "ERROR: Unable to Deposit a Negative Value for Fund ID: " << get_fund_name(fund_id) << " for Account: " << first_name_ << " " << last_name_ << endl;
    return false;
  }
  fund_[fund_id].Add(amount);
  Transaction transaction('D', account_id_, fund_id, amount, true);
  fund_[fund_id].Record(transaction);
  account_history_.push_back(transaction);
  return true;
} 

bool Account::Transfer(int fund_id, int transfer_account_id, int transfer_fund_id,int amount) 
{
  // error handling 
   if (amount < 0) 
   {
    cerr << "ERROR: Unable to Deposit a Negative Value for Fund ID: "  << get_fund_name(fund_id)[fund_id] << " to " << get_fund_name(transfer_fund_id)[transfer_fund_id] << " for Account " << account_id_ << endl;
    return false;
  }
  if (FundValid(transfer_fund_id)) 
  {
    cerr << "ERROR: Invalid Transfer Fund ID: " << transfer_fund_id << " for Account: " << transfer_account_id << " (Transfer Failed)" << endl;
    return false;
  }
  fund_[fund_id].Add(amount);
  Transaction transaction('T', transfer_account_id, transfer_fund_id, account_id_, fund_id, amount, true);
  fund_[fund_id].Record(transaction);
  account_history_.push_back(transaction);
  return true;
} 

bool Account::FundWithdraw(int account_id, int transfer_account_id, int amount) 
{

  int fund1 = fund_[account_id].get_balance();
  // check for if 2nd withdraw needed 
  if (fund1 >= amount) 
  {
    fund_[account_id].Sub(amount);
    Transaction withdraw('W', account_id_, account_id, amount, true);
    account_history_.push_back(withdraw);
    fund_[account_id].Record(withdraw);
  } else 
  {
    fund_[account_id].Sub(fund1);
    Transaction withdraw('W', account_id_, account_id, fund1, true);
    account_history_.push_back(withdraw);
    fund_[account_id].Record(withdraw);
    int value = amount - fund1;
    fund_[transfer_account_id].Sub(value);
    Transaction withdraw2('W', account_id_, transfer_account_id, value, true);
    account_history_.push_back(withdraw2);
    fund_[transfer_account_id].Record(withdraw2);
  }

  return true;
} 

// withdraw function (use in bank.cpp)
// call functions from fund class (add/sub)
// error handling: balance below 0, link account balance, invalid ID 
bool Account::Withdraw(char transaction_type, int fund_id, int account_id, int transfer_account_id, int transfer_fund_id, int amount) 
{
  if (FundValid(fund_id)) 
  {
    cerr << "ERROR: Cannot Complete Transaction of $" << amount << " from account: " << account_id << " fund: " << fund_id  << endl;
    return false;
  } 
  // withdraw char command 
  if (transaction_type != 'T') 
  {
    if ((amount >= 0) && (amount <= fund_[fund_id].get_balance())) 
    {
            // call fund functions 
            Transaction transaction('W', account_id_, fund_id, amount, true);
            fund_[fund_id].Sub(amount);
            fund_[fund_id].Record(transaction);
            account_history_.push_back(transaction);
            return true;
    }
    else if (linked_fund_check(fund_id) && (amount >= 0) && (amount <= linked_balance(fund_id))) 
    {
            return FundWithdraw(fund_id, get_linked_fund(fund_id), amount);
    }
    else 
    {
            // error handling 
            if(amount < 0)
            {
              cerr << "ERROR: Cannot Withdraw Negative Value of $ " << amount << " from " << first_name_ << " " << last_name_ << " " << get_fund_name(fund_id) << endl;
              
            // else linked balance is not enough to cover transaction 
            }else
            {
              cerr << "ERROR: Insufficient Funds to withdraw $" << amount << " from " << first_name_ << " " << last_name_ << " " << get_fund_name(fund_id) << endl;
            }
            // log 
            Transaction transaction('W', account_id_, fund_id, amount, false);
            fund_[fund_id].Record(transaction);
            account_history_.push_back(transaction);
            return false;
          }
  }
  // out of if to else
  // else for transfer  
  else 
  {
      if (FundValid(transfer_fund_id)) 
      {
        cerr << "ERROR: Invalid Account " << transfer_account_id << " Fund ID " << transfer_fund_id << " (Transfer Failed)" << endl;
        return false;
      }
      // check for sufficient funds
      // funds can be brought from transfer 
      if ((amount >= 0) && (amount <= fund_[fund_id].get_balance())) 
      {
        Transaction transaction('T', account_id_, fund_id, transfer_account_id, transfer_fund_id, amount, true);
        fund_[fund_id].Sub(amount);
        fund_[fund_id].Record(transaction);
        account_history_.push_back(transaction);
        return true;
      }
      else if (linked_fund_check(fund_id) && (amount >= 0) && (amount <= linked_balance(fund_id))) 
      {
        return FundWithdraw(fund_id, get_linked_fund(fund_id), amount);
      }
      else 
      {
        // error handling, log 
        cerr << "ERROR: Transfer Failure of $" << amount << " from Account: " << account_id_ << " " << get_fund_name(fund_id) << " to Account: " << transfer_account_id << " " << get_fund_name(transfer_fund_id) << endl;
        Transaction transfer_transaction('T', account_id_, fund_id, transfer_account_id, transfer_fund_id, amount, false);
        fund_[fund_id].Record(transfer_transaction);
        account_history_.push_back(transfer_transaction);
        return false;
      }
  }
}



