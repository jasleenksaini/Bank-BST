// Jasleen Kaur Saini
// Program 5

#ifndef BANK_H_
#define BANK_H_

#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "account.h"
#include "bs_tree.h"
#include "transaction.h"
using namespace std;

class Bank 
{
public:
  // default constructors
  Bank();

  // Phase 1: read 
  bool ReadTransactions(const string& file_name);

  // Phase 2: execute 
  void ExecuteTransactions();

  // called to display history 
  void MainAccountHistory(const Transaction& current, int account_id);
  void MainFundHistory(const Transaction& current, int account_id);

  // Phase 3: display 
  void Print();

private:
  // Private data members
  BSTree accounts_;
  queue<Transaction> transactions_;
};
#endif





