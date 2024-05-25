// Jasleen Kaur Saini
// Program 5

#ifndef BS_TREE_H_
#define BS_TREE_H_

#include "account.h"
#include <iostream>
using namespace std;

// used recursive logic for binary search tree implementation 
class BSTree 
{

public:
    // default constructor
    BSTree();

    // copy Constructor
    BSTree(const BSTree& tree);

    // destructor
    ~BSTree();

    // actions/functions
    bool Insert(Account* account);
    bool Retrieve(int account_id, Account*& account) const;

    // use on destructor 
    void DeleteList();

    void Display() const;
    bool isEmpty() const;
    int size() const;

    // use on copy constructor 
    BSTree& operator=(const BSTree& tree); 
    // stream 
    friend ostream& operator<<(ostream &out, const BSTree& tree);

private:
    // private node struct
    struct Node{
        Account* p_acct;
        Node* right = nullptr;
        Node* left = nullptr;
    };

    Node* root_ = nullptr;
    // use in size()
    int size_; 

    // recursive step functions  
    bool RecursiveInsertStep(Account* p_account, Node* &root);
    bool RecursiveRetrieveStep(int acct_ID, Account*& p_account, Node* root) const;
    void RecursiveDeleteStep(Node* root);

    void RecursiveDisplayStep(Node* root) const;
    void RecursiveCopyStep(Node*& destination, Node* source); 
};
#endif

