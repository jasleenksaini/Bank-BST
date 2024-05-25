// Jasleen Kaur Saini
// Program 5

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "fund.h"
#include "transaction.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// k constant list of fund names
// global declared outside of class 
const vector<string> kFundList_{
    "Money Market",       
    "Prime Money Market",
    "Long-Term Bond",
    "Short-Term Bond",    
    "500 Index Fund",     
    "Capital Value Fund",
    "Growth Equity Fund", 
    "Growth Index Fund",  
    "International Fund"};

class Account 
{
public:
  // default constructor
  Account();

  // constructor 
  Account(int account_id, string first_name, string last_name);

  // getters 
  string get_first_name() const;
  string get_last_name() const;
  int get_account_id() const;
  string get_fund_name(int fund_id) const;

  // error handling
   bool FundValid(int fund_id);

  // history functions 
  void TotalAccountHistory();
  void TotalFundHistory(int fund_id);

  // error handling: linking funds 
  bool linked_fund_check(int fund_id) const; // Check if a fund is linked
  int get_linked_fund(int fund_id) const; // Get the linked fund ID
  int linked_balance(int fund_id) const; // Get the total balance of linked funds
  
  // stream operator 
  friend ostream &operator<<(ostream &stream, const Account &rhs);

  // actions/functions
  bool Deposit(char transaction_type, int account_id, int fund_id, int transfer_account_id, int transfer_fund_id, int amount);
  bool Withdraw(char transaction_type, int fund_id, int account_id, int transfer_account_id, int transfer_fund_id, int amount);

  bool FundDeposit(int fund_id, int amount); 
  bool FundWithdraw(int account_id, int transfer_account_id, int amount);
  
  bool Transfer(int fund_id, int transfer_account_id, int transfer_fund_id, int amount);

private:
  // data members
  string last_name_;
  string first_name_;
  int account_id_;

  Fund fund_[9];
  // set vector with fund names 
  vector<Transaction> account_history_;
};
#endif

