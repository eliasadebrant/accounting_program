#include <string>
#include <iostream>
#include "year.h"
#include "menuState.h"
#include "addpayment.h"

Year::Year(string state, string year, vector<Payment> payments, int year_index) :
    Programstate(state),
    year{year}, 
    payments{move(payments)},
    year_index  {year_index}
    {}

string Year::get_state() const {
    return state;
}

bool Year::handle_input(sf::Event& e, Context& c) {
    if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            float mouse_x = e.mouseButton.x;
            float mouse_y = e.mouseButton.y;

            if (mouse_x >= 1720.f && mouse_x <= 1870.f && mouse_y >= 20.f && mouse_y <= 70.f) {
                next_state = std::make_unique<AllYears>("AllYears");
                cout << "Nästa state satt till " << next_state->get_state() << endl;
            } else if (mouse_x >= 1670.f && mouse_x <= 1870.f && mouse_y >= 90.f && mouse_y <= 140.f){
                cout << "Lägger till betalning" << endl;
                next_state = std::make_unique<AddPaymentState>("AddPaymentstate", year_index, c, payments);
                
            }
        }
    }
    
   
   

    return true;
}
void Year::update(Context& c){
    return;
}
void Year::draw(Context& c){
    c.window.clear(sf::Color::White);
    sf::Text text("Year View: " + year, c.font, 24);
    text.setPosition(600.f, 20.f);
    text.setFillColor(sf::Color::Black);
    c.window.draw(text);

    
    vector<std::shared_ptr<sf::Drawable>> headbar_elements = ui_data.build_headbar(c);
    for (const std::shared_ptr<sf::Drawable>& element : headbar_elements) {
        c.window.draw(*element);
    }

    //Go back button
    vector<std::shared_ptr<sf::Drawable>> go_back_elements = ui_data.build_button(c, 1720, 20, 150, 50, "Go back");
    for (const std::shared_ptr<sf::Drawable>& element : go_back_elements) {
        c.window.draw(*element);
    }

    /*
    vector<std::shared_ptr<sf::Drawable>> add_payment_elements = ui_data.build_add_payment_button(c);
    for (const std::shared_ptr<sf::Drawable>& element : add_payment_elements) {
        c.window.draw(*element);
    }
    */
    vector<std::shared_ptr<sf::Drawable>> add_payment_elements = ui_data.build_button(c, 1670, 90, 200, 50, "Add Verificate");
    for (const std::shared_ptr<sf::Drawable>& element : add_payment_elements) {
        c.window.draw(*element);
    }
    vector<std::shared_ptr<sf::Drawable>> print_payment_elements = ui_data.draw_all_payments(c, year_index);
    for (const std::shared_ptr<sf::Drawable>& element : print_payment_elements) {
        c.window.draw(*element);
    }


}

string Year::get_year() const {
    return year;
}
const vector<Payment>& Year::get_payments() const{
    return payments;
}
void Year::add_payment(Payment&& payment){
    payments.emplace_back(move(payment));
}

void Year::remove_last_payment(){
    if (!payments.empty()) {
        payments.pop_back();
    }
}