#ifndef YEAR_H
#define YEAR_H
#include <string>
#include <vector>
#include <memory>
#include "uidata.h"
#include "payment.h"
#include "account.h"
#include "programstate.h"

using namespace std;

class Context;


class Year : public Programstate {
public:
    Year(string state, string year, vector<Payment> payments, int year_index);

    string get_year() const;
    const vector<Payment>& get_payments() const;
    void add_payment(Payment&& payment);
    void remove_last_payment();
    
    string get_state() const override;
    bool handle_input(sf::Event& e, Context& c) override;
    void update(Context& c) override;
    void draw(Context&c) override;
private:
    string year;
    
    vector<Payment> payments;
    UIData ui_data;
    int year_index;



};

#endif