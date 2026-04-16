#ifndef ALLYEARS_H
#define ALLYEARS_H
#include <memory>
#include "programstate.h"
#include "context.h"
#include "uidata.h"
using namespace std;


class AllYears : public Programstate{
public:
    AllYears(string state);
    string get_state() const override;
    bool handle_input(sf::Event& e, Context& c) override;
    void update(Context& c) override;
    void draw(Context&c) override;
    //void add_year(Context& c);

private:
    string active_year;
    UIData ui_data;
    string current_input = "";
    bool typing = false;

};


#endif 