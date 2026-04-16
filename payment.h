#ifndef PAYMENT_H
#define PAYMENT_H

#include "account.h"
using namespace std;

struct Entry{
public:
    Entry(shared_ptr<Account> acc, double amt, string comment)
        : account(acc), amount(amt), comment(comment) {}

    shared_ptr<Account> account;
    double amount;
    string comment;

      
};


class Payment {

public:
    Payment (vector<shared_ptr<Entry>> entries, int date, string owner, string receipt_path, string description);
    bool is_balanced();
    int get_date();
    vector<shared_ptr<Entry>> get_entries();
    string get_description();

private:
    vector<shared_ptr<Entry>> entries;
    int date{};
    string owner{};
    string receipt_path{};
    string description{};

};
#endif