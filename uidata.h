#ifndef UIDATA_H
#define UIDATA_H
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "context.h"
//#include "year.h"
using namespace std;


class UIData{
public:
    UIData();
    //For allyears state
    vector<shared_ptr<sf::Drawable>> build_year_list(Context& c);

    //For year state
    vector<std::shared_ptr<sf::Drawable>> build_add_payment_window(Context& c);
    vector<std::shared_ptr<sf::Drawable>> draw_all_payments(Context& c, int yearindex);


    //For all states
    vector<shared_ptr<sf::Drawable>> build_headbar(Context& c);
    vector<std::shared_ptr<sf::Drawable>> build_button(Context& c, 
        int x_pos, int y_pos, int x_size, int y_size, string text);
};


#endif