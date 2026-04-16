#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include <string>
#include <vector>
#include <stack>
#include "payment.h"
#include "programstate.h"
#include "context.h"
using namespace std;

class Accounting {
public:
    Accounting();

    int run();
    //Programstate* change(Programstate* active_state, Context& c);

private:
    //stack <Programstate*> state_stack;
};

#endif