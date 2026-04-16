#include "account.h"

Account::Account(int id, string name) :
    id{id}, 
    name{name}
    {}

string Account::get_name() const {
    return name;
}
int Account::get_id() const {
    return id;
}