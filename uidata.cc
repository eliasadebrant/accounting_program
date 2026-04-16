#include "uidata.h"
#include "year.h"

UIData::UIData()
    {}

vector<std::shared_ptr<sf::Drawable>>UIData::build_headbar(Context& c){ 
    vector<std::shared_ptr<sf::Drawable>> headbar_elements;

    auto headbar = std::make_shared<sf::RectangleShape>(sf::Vector2f(1920.f, 100.f));
    headbar->setFillColor(sf::Color(200, 200, 200));
    headbar->setPosition(0.f, 0.f);
    headbar_elements.push_back(headbar);

    auto title = std::make_shared<sf::Text>();
    title->setFont(c.font);
    title->setString("Accounting Software");
    title->setPosition(20.f, 30.f);
    title->setFillColor(sf::Color::Black);
    headbar_elements.push_back(title);

    return headbar_elements;
}

vector<std::shared_ptr<sf::Drawable>> UIData::build_year_list(Context& c){
    vector<std::shared_ptr<sf::Drawable>> year_list_elements;

    float y_offset = 150.f; 
    for (const std::shared_ptr<Year>& year : c.data.all_years) {
       
        auto year_text = std::make_shared<sf::Text>();
        year_text->setFont(c.font);
        year_text->setString(year->get_year());
        year_text->setPosition(50.f, y_offset);
        year_text->setFillColor(sf::Color::Black);
        year_list_elements.push_back(year_text);
        y_offset += 50.f; 
    }

    auto box = make_shared<sf::RectangleShape>();
    box->setFillColor(sf::Color::Transparent);
    box->setOutlineColor(sf::Color::Black);
    box->setOutlineThickness(2.f);

    box->setPosition(40.f, 140.f);
    box->setSize(sf::Vector2f(200.f, 50.f * c.data.all_years.size()));
    year_list_elements.push_back(box);

    return year_list_elements;
};

vector<std::shared_ptr<sf::Drawable>> UIData::build_go_back_button(Context& c){
    vector<std::shared_ptr<sf::Drawable>> go_back_elements;

    auto button = std::make_shared<sf::RectangleShape>(sf::Vector2f(150.f, 50.f));
    button->setFillColor(sf::Color::Transparent);
    button->setOutlineColor(sf::Color::Black);
    button->setOutlineThickness(2.0f);
    button->setPosition(1720.f, 20.f);
    go_back_elements.push_back(button);

    auto text = std::make_shared<sf::Text>();
    text->setFont(c.font);
    text->setString("Go Back");
    text->setPosition(1730.f, 30.f);
    text->setFillColor(sf::Color::Black);
    go_back_elements.push_back(text);

    return go_back_elements;
};

vector<std::shared_ptr<sf::Drawable>> UIData::build_add_year_button(Context& c){
    vector<std::shared_ptr<sf::Drawable>> add_year_button_elements;

    auto button = std::make_shared<sf::RectangleShape>(sf::Vector2f(150.f, 50.f));
    button->setFillColor(sf::Color::Transparent);
    button->setOutlineColor(sf::Color::Black);
    button->setOutlineThickness(2.0f);
    button->setPosition(1720.f, 90.f);
    add_year_button_elements.push_back(button);

    auto text = std::make_shared<sf::Text>();
    text->setFont(c.font);
    text->setString("Add Year");
    text->setPosition(1730.f, 100.f);
    text->setFillColor(sf::Color::Black);
    add_year_button_elements.push_back(text);

    return add_year_button_elements;
};

vector<std::shared_ptr<sf::Drawable>> UIData::build_add_payment_button(Context& c){
    vector<std::shared_ptr<sf::Drawable>> add_payment_button_elements;

    auto button = std::make_shared<sf::RectangleShape>(sf::Vector2f(200.f, 50.f));
    button->setFillColor(sf::Color::Transparent);
    button->setOutlineColor(sf::Color::Black);
    button->setOutlineThickness(2.0f);
    button->setPosition(1670.f, 90.f);
    add_payment_button_elements.push_back(button);

    auto text = std::make_shared<sf::Text>();
    text->setFont(c.font);
    text->setString("Add Payment");
    text->setPosition(1680.f, 100.f);
    text->setFillColor(sf::Color::Black);
    add_payment_button_elements.push_back(text);

    return add_payment_button_elements;
}

vector<std::shared_ptr<sf::Drawable>> UIData::draw_all_payments(Context& c, int yearindex){
    vector<std::shared_ptr<sf::Drawable>> print_all_payments_elements;

    //Adding background and title
    auto background = std::make_shared<sf::RectangleShape>(sf::Vector2f(1700.f, 750.f));
    background->setFillColor(sf::Color::Transparent);
    background->setOutlineColor(sf::Color::Black);
    background->setOutlineThickness(2.0f);
    background->setPosition(100.f, 150.f);
    print_all_payments_elements.push_back(background);

    auto title = std::make_shared<sf::Text>();
    title->setFont(c.font);
    title->setString("All Verificates");
    title->setPosition(110.f, 170.f);
    title->setFillColor(sf::Color::Black);
    print_all_payments_elements.push_back(title);

    vector<Payment> payments = c.data.all_years[yearindex]->get_payments();
    int y_change = 90;
    int x = 100;
    int y_start = 270;

    for (Payment& payment : payments){
        //Adding box

        auto verificatebox = make_shared<sf::RectangleShape>();
        verificatebox->setFillColor(sf::Color::Transparent);
        verificatebox->setOutlineColor(sf::Color::Black);
        verificatebox->setOutlineThickness(2.f);
        verificatebox->setPosition(x, y_start);
        verificatebox->setSize(sf::Vector2f(1700.f, 90));
        print_all_payments_elements.push_back(verificatebox);

        y_start += y_change;



        //Adding info
        auto text = std::make_shared<sf::Text>();
        text->setFont(c.font);
        text->setCharacterSize(24);

        string entries_text = "";
        for (shared_ptr<Entry> entry : payment.get_entries()){
            entries_text += " Account ID: " + to_string(entry->account->get_id()) + 
                            " Entry amount: " + to_string(entry->amount);
        }

        string verificate_text = " Description: " + payment.get_description() + 
                                " Date: " + to_string(payment.get_date()) + 
                                 entries_text; 
        text->setString(verificate_text);
        text->setPosition(110.f, 190.f + y_change);
        text->setFillColor(sf::Color::Black);
        print_all_payments_elements.push_back(text);
        y_change += 90;
    }

    return print_all_payments_elements;

}

vector<std::shared_ptr<sf::Drawable>> UIData::build_add_payment_window(Context& c){
    vector<std::shared_ptr<sf::Drawable>> add_payment_window_elements;

    //Adding background and title
    auto background = std::make_shared<sf::RectangleShape>(sf::Vector2f(1400.f, 700.f));
    background->setFillColor(sf::Color::Transparent);
    background->setOutlineColor(sf::Color::Black);
    background->setOutlineThickness(2.0f);
    background->setPosition(200.f, 200.f);
    add_payment_window_elements.push_back(background);

    auto title = std::make_shared<sf::Text>();
    title->setFont(c.font);
    title->setString("Add New Payment");
    title->setPosition(210.f, 220.f);
    title->setFillColor(sf::Color::Black);
    add_payment_window_elements.push_back(title);



    //Adding lines
    int x = 1;
    while(x <= 5){
        auto horizontal_line = std::make_shared<sf::RectangleShape>(sf::Vector2f(1200.f, 3.f));
        horizontal_line->setFillColor(sf::Color::Black);
        horizontal_line->setPosition(300 , 300 + x*80);
        add_payment_window_elements.push_back(horizontal_line);
        x += 1;
    }

    x = 0;
    while(x <= 5){
        auto vertical_line = std::make_shared<sf::RectangleShape>(sf::Vector2f(3.f, 400.f));
        vertical_line->setFillColor(sf::Color::Black);
        vertical_line->setPosition(300 + x*200 , 350);
        add_payment_window_elements.push_back(vertical_line);
        x += 1;
    }

    //Adding labels
    auto account_number = std::make_shared<sf::Text>();
    account_number->setFont(c.font);
    account_number->setCharacterSize(24);
    account_number->setString("Account number");
    account_number->setPosition(320.f, 350.f);
    account_number->setFillColor(sf::Color::Black);
    add_payment_window_elements.push_back(account_number);

    auto account = std::make_shared<sf::Text>();
    account->setFont(c.font);
    account->setCharacterSize(24);
    account->setString("Account name");
    account->setPosition(520.f, 350.f);
    account->setFillColor(sf::Color::Black);
    add_payment_window_elements.push_back(account);

    auto debit = std::make_shared<sf::Text>();
    debit->setFont(c.font);
    debit->setCharacterSize(24);
    debit->setString("Debit");
    debit->setPosition(720.f, 350.f);
    debit->setFillColor(sf::Color::Black);
    add_payment_window_elements.push_back(debit);

    auto credit = std::make_shared<sf::Text>();
    credit->setFont(c.font);
    credit->setCharacterSize(24);
    credit->setString("Credit");
    credit->setPosition(920.f, 350.f);
    credit->setFillColor(sf::Color::Black);
    add_payment_window_elements.push_back(credit);

    auto sum = std::make_shared<sf::Text>();
    sum->setFont(c.font);
    sum->setCharacterSize(24);
    sum->setString("sum");
    sum->setPosition(1120.f, 350.f);
    sum->setFillColor(sf::Color::Black);
    add_payment_window_elements.push_back(sum);

    auto comment = std::make_shared<sf::Text>();
    comment->setFont(c.font);
    comment->setCharacterSize(24);
    comment->setString("Comment");
    comment->setPosition(1320.f, 350.f);
    comment->setFillColor(sf::Color::Black);
    add_payment_window_elements.push_back(comment);

    auto date = std::make_shared<sf::Text>();
    date->setFont(c.font);
    date->setCharacterSize(24);
    date->setString("Date: ");
    date->setPosition(210.f, 290.f);
    date->setFillColor(sf::Color::Black);
    add_payment_window_elements.push_back(date);

    auto description = std::make_shared<sf::Text>();
    description->setFont(c.font);
    description->setCharacterSize(24);
    description->setString("Description: ");
    description->setPosition(580.f, 240.f);
    description->setFillColor(sf::Color::Black);
    add_payment_window_elements.push_back(description);


    auto save_button = std::make_shared<sf::RectangleShape>(sf::Vector2f(250.f, 50.f));
    save_button->setFillColor(sf::Color::Transparent);
    save_button->setOutlineColor(sf::Color::Black);
    save_button->setOutlineThickness(2.0f);
    save_button->setPosition(1300.f, 830.f);
    add_payment_window_elements.push_back(save_button);

    auto save_text = std::make_shared<sf::Text>();
    save_text->setFont(c.font);
    save_text->setString("Save verificate");
    save_text->setPosition(1305.f, 835.f);
    save_text->setFillColor(sf::Color::Black);
    add_payment_window_elements.push_back(save_text);

    return add_payment_window_elements;

    //här bör även läggas till kostnadsställen
}

vector<std::shared_ptr<sf::Drawable>> UIData::build_settings_button(Context& c){
    vector<std::shared_ptr<sf::Drawable>> build_settings_button_elements;


    auto button = std::make_shared<sf::RectangleShape>(sf::Vector2f(150.f, 50.f));
    button->setFillColor(sf::Color::Transparent);
    button->setOutlineColor(sf::Color::Black);
    button->setOutlineThickness(2.0f);
    button->setPosition(1720.f, 220.f);
    build_settings_button_elements.push_back(button);

    auto text = std::make_shared<sf::Text>();
    text->setFont(c.font);
    text->setString("Settings");
    text->setPosition(1730.f, 230.f);
    text->setFillColor(sf::Color::Black);
    build_settings_button_elements.push_back(text);

    return build_settings_button_elements;
}


