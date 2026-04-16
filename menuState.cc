#include "menuState.h"
#include <string>

MenuState::MenuState(string state) : 
    Programstate(state)
    {}

string MenuState::get_state() const{
    return state;
}

bool MenuState::handle_input(sf::Event& e, Context& c) {
    if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            float mouseX = e.mouseButton.x;
            float mouseY = e.mouseButton.y;

            // Check if the click is within the "New Accounting" button
            if (mouseX >= 760.f && mouseX <= 1160.f && mouseY >= 490.f && mouseY <= 590.f) {
                next_state = std::make_unique<AllYears>("AllYears");
                cout << "Nästa state satt till " << next_state->get_state() << endl;
            } else if (mouseX >= 760.f && mouseX <= 1160.f && mouseY >= 690.f && mouseY <= 790.f) {
                // Handle "Load Accounting" button click (currently does nothing)
                next_state = nullptr; // Placeholder for future functionality
            }
        }
    }
    return true;
}

void MenuState::update(Context& c){
    return;
}
void MenuState::draw(Context&c){
    c.window.clear(sf::Color::White);

    sf::RectangleShape new_button(sf::Vector2f(400.f, 100.f));
    new_button.setFillColor(sf::Color::Green); 
    new_button.setPosition(760.f, 490.f);
    sf::Text new_button_text("New Accounting", c.font, 48);
    new_button_text.setPosition(760.f, 490.f);
    new_button_text.setFillColor(sf::Color::Black);


    sf::Color grey(128, 128, 128);
    sf::RectangleShape old_button(sf::Vector2f(400.f, 100.f));
    old_button.setFillColor(grey);
    old_button.setPosition(760.f, 690.f);
    sf::Text old_button_text("Load Accounting", c.font, 48);
    old_button_text.setPosition(760.f, 690.f);
    old_button_text.setFillColor(sf::Color::Black);

    sf::Text menutext("Accounting Program", c.font, 128);
    menutext.setPosition(500.f, 200.f);
    menutext.setFillColor(sf::Color::Black);


    c.window.draw(menutext);
    c.window.draw(new_button);
    c.window.draw(old_button);
    c.window.draw(new_button_text);
    c.window.draw(old_button_text);
    
}