#include "allyears.h"
#include "year.h"
#include "menuState.h"
AllYears::AllYears(string state) :
    Programstate(state)
    {}

string AllYears::get_state() const{
    return state;
}



bool AllYears::handle_input(sf::Event& e, Context& c) {
    //Year list börjar på 40, 140. Efter 50 kommer nästa element i all_years
    if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            float mouse_x = e.mouseButton.x;
            float mouse_y = e.mouseButton.y;

            if (mouse_x >= 40.f && mouse_x <= 340.f) {
                int index = (mouse_y - 140.f) / 50.f;
                if (index >= 0 && index < c.data.all_years.size()) {
                    next_state = std::make_unique<Year>("Year", 
                                                        c.data.all_years[index]->get_year(), 
                                                        c.data.all_years[index]->get_payments(),
                                                        index);
                    cout << "Nästa state satt till " << next_state->get_state() << endl;
                }
            }
        }
    }

     if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            float mouse_x = e.mouseButton.x;
            float mouse_y = e.mouseButton.y;

            if (mouse_x >= 1720.f && mouse_x <= 1870.f && mouse_y >= 20.f && mouse_y <= 70.f) {
                next_state = std::make_unique<MenuState>("MenuState");
                cout << "Nästa state satt till " << next_state->get_state() << endl;
            }
        }
    }
    if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            float mouse_x = e.mouseButton.x;
            float mouse_y = e.mouseButton.y;

            if (mouse_x >= 1730.f && mouse_x <= 1880.f && mouse_y >= 90.f && mouse_y <= 140.f) {
                typing = true;
                current_input = "";
                cout << "Lägger till år" << endl;
            }
        }
    }
    


    if (typing && e.type == sf::Event::TextEntered)
    {
        
        if (e.text.unicode == 8) // backspace
        {
            if (!current_input.empty())
                current_input.pop_back();
        }
        else if (e.text.unicode == 13) // enter
        {
            vector<Payment> payments;
            shared_ptr<Year> year = make_shared<Year>("Year", 
                                                    current_input, 
                                                    move(payments), 
                                                    static_cast<int>(c.data.all_years.size()));
            c.data.all_years.push_back(year);

            typing = false;
        }
        else if (e.text.unicode < 128) // vanlig text
        {
            current_input += static_cast<char>(e.text.unicode);
        }
    }

    return true;
};


void AllYears::update(Context& c){
    return;
}
void AllYears::draw(Context&c){
    c.window.clear(sf::Color::White);

    sf::Text text("All Years View", c.font, 48);
    text.setPosition(500.f, 200.f);
    text.setFillColor(sf::Color::Black);
    c.window.draw(text);

    vector<std::shared_ptr<sf::Drawable>> headbar_elements = ui_data.build_headbar(c);
    for (const std::shared_ptr<sf::Drawable>& element : headbar_elements) {
        c.window.draw(*element);
    }

    vector<std::shared_ptr<sf::Drawable>> year_list_elements = ui_data.build_year_list(c);
    for (const std::shared_ptr<sf::Drawable>& element : year_list_elements) {
        c.window.draw(*element);
    }

    vector<std::shared_ptr<sf::Drawable>> go_back_elements = ui_data.build_go_back_button(c);
    for (const std::shared_ptr<sf::Drawable>& element : go_back_elements) {
        c.window.draw(*element);
    }

    vector<std::shared_ptr<sf::Drawable>> add_year_elements = ui_data.build_add_year_button(c);
    for (const std::shared_ptr<sf::Drawable>& element : add_year_elements) {
        c.window.draw(*element);
    }
    vector<std::shared_ptr<sf::Drawable>> settings_button_elements = ui_data.build_settings_button(c);
    for (const std::shared_ptr<sf::Drawable>& element : settings_button_elements) {
        c.window.draw(*element);
    }




    if(typing){
       
        sf::RectangleShape box(sf::Vector2f(400.f, 60.f));
        box.setPosition(1500.f, 500.f);
        box.setFillColor(sf::Color(220,220,220));
        c.window.draw(box);

        sf::Text text("Enter new year name:", c.font, 24);
        text.setPosition(1510.f, 500.f);
        c.window.draw(text);


        sf::Text inputText(current_input, c.font, 30);
        inputText.setPosition(1510.f, 560.f);
        inputText.setFillColor(sf::Color::Black);
        c.window.draw(inputText);
    }



}