// Jasleen Kaur Saini
// Program 5

#ifndef FUND_H_
#define FUND_H_

#include "transaction.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Fund 
{
public:
  // default constructor
  Fund(); 

  // constructor 
  Fund(string name);

  // getters
  string get_fund_name() const;
  int get_balance() const;
  vector<Transaction> get_transaction();

  // actions/functions 
  bool Add(int amount);
  bool Sub(int amount);
  bool Record(Transaction tran);  

  void FundHistory();
  void AccountHistory();

private:
  // data members
  int balance_;
  string fund_name_;
  vector<Transaction> fund_transactions_;
};
#endif