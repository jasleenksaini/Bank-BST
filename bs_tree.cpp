// Jasleen Kaur Saini
// Program 5

#include "bs_tree.h"
#include<iostream>
#include <cstdlib> // for cerr std? check 
using namespace std;

// default constructor
BSTree::BSTree() : root_(nullptr), size_(0) {}

// copy constructor
BSTree::BSTree(const BSTree& tree) {
    *this = tree;
}

// destructor
BSTree::~BSTree() {
    RecursiveDeleteStep(root_);
}

// NECCESSARY FUNCTIONS

// insert
bool BSTree::Insert(Account* account) {
    // check 
    if (account->get_account_id() < 0) {
        cerr << "ERROR: Invalid Account ID: " << account->get_account_id() << endl;
        return false;
    }
    // recursive step 
    return RecursiveInsertStep(account, root_);
}

bool BSTree::RecursiveInsertStep(Account* account, Node*& root) {
    // empty tree 
    if (root == nullptr) {
        root = new Node{account, nullptr, nullptr};
        size_++;
        return true; 
    }
    // insert logic + recursive step 
    int current_account_id = root->p_acct->get_account_id();
    int new_account_id = account->get_account_id();

    if (new_account_id < current_account_id) {
        return RecursiveInsertStep(account, root->left);
    } else if (new_account_id > current_account_id) {
        return RecursiveInsertStep(account, root->right);
    }
    // else (error handling)
    cerr << "ERROR: Account ID " << new_account_id << " already exists." << endl;
    return false; 
}

// retrieve 
bool BSTree::Retrieve(int account_id, Account*& account) const {
    return RecursiveRetrieveStep(account_id, account, root_);
}

bool BSTree::RecursiveRetrieveStep(int account_id, Account*& account, Node* root) const {
    // empty tree 
    if (root == nullptr) {
        return false; 
    }
    
    // traverse + recursive step 
    int root_account_id = root->p_acct->get_account_id();

    if (account_id == root_account_id) {
        account = root->p_acct;
        return true;
    }
    if (account_id < root_account_id) {
        return RecursiveRetrieveStep(account_id, account, root->left);
    } else {
        return RecursiveRetrieveStep(account_id, account, root->right);
    }
}

// display
void BSTree::Display() const {
    // check if empty (does not take in root_)
    if (isEmpty()) {
        cerr << "ERROR: Binary Search Tree is Empty" << endl;
    } else {
        // recursive step 
        RecursiveDisplayStep(root_);
    }
    cout << endl;
}

void BSTree::RecursiveDisplayStep(Node* root) const {
    // until fully displayed 
    if (root != nullptr) {
        RecursiveDisplayStep(root->left);
        cout << *(root->p_acct) << endl;
        RecursiveDisplayStep(root->right);
    }
}

// delete 
void BSTree::RecursiveDeleteStep(Node* root) {
    // if empty 
    if (root == nullptr) {
        return; // not bool
    }
    // recursive step 
    RecursiveDeleteStep(root->left);
    RecursiveDeleteStep(root->right);
    // data members 
    delete root->p_acct;
    delete root;
}

// Check if the tree is empty
bool BSTree::isEmpty() const {
    return (root_ == nullptr);
}

// EXTRA FUNCTIONS 

// Get the size of the tree
int BSTree::size() const {
    return size_;
}

// Stream output operator overloading to display the tree
ostream& operator<<(ostream& stream, const BSTree& tree) {
    // use display function from binary search tree class
    tree.Display();
    return stream;
}

// assignment operator 
BSTree& BSTree::operator=(const BSTree& tree) {
    if (this == &tree) {
        return *this;
    }
    // must delete current object 
    RecursiveDeleteStep(root_);
    // Copy tree recursively
    if (tree.root_ != nullptr) {
        root_ = new Node();
        RecursiveCopyStep(root_, tree.root_);
    } else {
        root_ = nullptr;
    }
    // link data memebers 
    size_ = tree.size_;
    return *this;
}

void BSTree::RecursiveCopyStep(Node*& destination, Node* source) {
    // empty rhs tree 
    if (source == nullptr) {
        destination = nullptr;
    // recursive step 
    } else {
        destination = new Node();
        destination->p_acct = new Account(*(source->p_acct)); 
        RecursiveCopyStep(destination->left, source->left);
        RecursiveCopyStep(destination->right, source->right);
    }
}
