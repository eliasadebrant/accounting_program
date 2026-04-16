#ifndef ADDPAYMENTSTATE_H
#define ADDPAYMENTSTATE_H
#include <string>
#include <vector>
#include <memory>
#include "uidata.h"
#include "payment.h"
#include "account.h"
#include "programstate.h"
#include "inputbox.h"

using namespace std;

class Context;


class AddPaymentState : public Programstate {
public:
    AddPaymentState(string state, int yearindex, Context &c, vector<Payment> payments);

    
    
    string get_state() const override;
    bool handle_input(sf::Event& e, Context& c) override;
    void update(Context& c) override;
    void draw(Context&c) override;
    void create_payment(Context&c);
private:

    int yearindex;
    string year;
    UIData ui_data;
    vector<InputBox> inputBoxes;
    Context& c;
    vector<Payment> payments;



};

#endif