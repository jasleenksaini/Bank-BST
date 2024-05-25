// Jasleen Kaur Saini
// Program 5

#include "fund.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// default constructor
Fund::Fund()
{
  balance_ = 0;
}

// constructor 
Fund::Fund(string name) 
{
  fund_name_ = name;
  balance_ = 0;
}

// getters
string Fund::get_fund_name() const 
{ 
  return fund_name_; 
}

int Fund::get_balance() const 
{ 
  return balance_; 
}

vector<Transaction> Fund::get_transaction() 
{ 
  return fund_transactions_; 
}

// actions/functions 
bool Fund::Add(int amount)
{
  if(amount < 0){
    return false;
  }
  balance_ += amount;
  return true;
}

bool Fund::Sub(int amount) 
{
  if (amount < 0 || amount > balance_) 
  {
    return false;
  }
  balance_ -= amount;
  return true;
}

// pushes transaction into vector
bool Fund::Record(Transaction tran) 
{
  fund_transactions_.push_back(tran);
  return true;
}

// history functions 
// used for 'H' implementation 
void Fund::AccountHistory() {
  if (!fund_transactions_.empty()) 
  {
    cout << get_fund_name() << ": $" << get_balance() << endl;
    for (const Transaction &transaction : fund_transactions_) 
    {
      cout << "   " << transaction;
    }
  }
}

// used for 'F' implementation 
void Fund::FundHistory() {
  for (const Transaction &transaction : fund_transactions_) 
  {
    cout << "   " << transaction;
  }
}