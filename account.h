#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Account{
public:
    Account(int id, string name);
    string get_name() const;
    int get_id() const;

private:
    int id;
    string name;
};

#endif