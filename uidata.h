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
    vector<shared_ptr<sf::Drawable>> build_headbar(Context& c);
    vector<shared_ptr<sf::Drawable>> build_year_list(Context& c);

    vector<std::shared_ptr<sf::Drawable>> build_go_back_button(Context& c);
    vector<std::shared_ptr<sf::Drawable>> build_add_year_button(Context& c);
    vector<std::shared_ptr<sf::Drawable>> build_add_payment_button(Context& c);
    vector<std::shared_ptr<sf::Drawable>> build_add_payment_window(Context& c);
    vector<std::shared_ptr<sf::Drawable>> draw_all_payments(Context& c, int yearindex);


    vector<std::shared_ptr<sf::Drawable>> build_settings_button(Context& c);
};


#endif