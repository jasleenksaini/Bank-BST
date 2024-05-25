// Jasleen Kaur Saini
// Program 5

// ./a.out test.txt > cout.txt 2> cerr.txt

#include "bank.h"
#include <iostream>
using namespace std; 

int main(int argc, char *argv[]) {
  if(argc != 2){
    cerr << "ERROR: Command Line Format is Incorrect" << endl;
    return -1;
  }

  // runs main functions
  Bank JollyBanker;
  JollyBanker.ReadTransactions(argv[1]);
  JollyBanker.ExecuteTransactions();
  JollyBanker.Print();
  return 0; 
}




