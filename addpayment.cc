
#include "addpayment.h"
#include "year.h"


//////////////////CONSTRUCTOR////////////////////////////////
AddPaymentState::AddPaymentState(string state, int yearindex, Context& c, vector<Payment> payments):
    Programstate(state),
    yearindex {yearindex},
    c {c},
    payments {payments}
    {
        float startX = 320;
        float startY = 400;
        float spacingX = 200;  // avstånd mellan kolumner
        float spacingY = 80;   // avstånd mellan rader

        //col 0: id 1:name 2:debit 3:credit 4:sum 5:comment
        for (int col = 0; col < 6; col++)
        {
            if (col == 1 || col == 4 ){ continue;}
            for (int row = 0; row < 5; row++)
            {
                string label;
                if (col == 0){ label = to_string(row) + "Account ID";} 
                else if (col == 1){ label = to_string(row) + " Account name";}
                else if (col == 2){ label = to_string(row) + " Debit sum";}
                else if (col == 3){label = to_string(row) + " Credit sum";}
                else if (col == 4){label = to_string(row) + " Sum";}
                else if (col == 5){label = to_string(row) + " Comment";}

                InputBox box(c, label);
                box.box.setSize(sf::Vector2f(140.f, 50.f));
                box.box.setFillColor(sf::Color(200,200,200));
               
                float x = startX + col * spacingX;
                float y = startY + row * spacingY;

                box.box.setPosition(x, y);

                box.text.setPosition(x + 5, y + 5);

                inputBoxes.push_back(box);
            }
        }
        //Adding boxes for date, title
        InputBox DateBox(c, "Date");
        DateBox.box.setSize(sf::Vector2f(140.f, 50.f));
        DateBox.box.setFillColor(sf::Color(200,200,200));
        DateBox.box.setPosition(280, 280);
        DateBox.text.setPosition(285, 285);
        inputBoxes.push_back(DateBox);

        InputBox DescriptionBox(c, "Description");
        DescriptionBox.box.setSize(sf::Vector2f(300.f, 50.f));
        DescriptionBox.box.setFillColor(sf::Color(200,200,200));
        DescriptionBox.box.setPosition(720, 230);
        DescriptionBox.text.setPosition(725, 235);
        inputBoxes.push_back(DescriptionBox);
    }

///////////////////////////////////////////////////////////////////////
string AddPaymentState::get_state() const {
    return state;
};

bool AddPaymentState::handle_input(sf::Event& e, Context& c){
    if (e.type == sf::Event::MouseButtonPressed) {

        sf::Vector2f mousePos = c.window.mapPixelToCoords(sf::Mouse::getPosition(c.window));

        //put all to false
        for (InputBox& box : inputBoxes) {
            box.focused = false;
        }

        for(InputBox& inputBox: inputBoxes){
            if (inputBox.box.getGlobalBounds().contains(mousePos)){
                cout << "har tryckt på en grå ruta med label " << inputBox.label << endl;
                inputBox.focused = true;
                break;
            }
        }
        if (e.mouseButton.button == sf::Mouse::Left) {
            float mouse_x = e.mouseButton.x;
            float mouse_y = e.mouseButton.y;

            if (mouse_x >= 1720.f && mouse_x <= 1870.f && mouse_y >= 20.f && mouse_y <= 70.f) {
                next_state = std::make_unique<Year>("Year", c.data.all_years[yearindex]->get_year(), 
                                                        c.data.all_years[yearindex]->get_payments(),
                                                    yearindex);
                cout << "Nästa state satt till " << next_state->get_state() << endl;
            }


            else if (mouse_x >= 1300.f && mouse_x <= 1550.f && mouse_y >= 830.f && mouse_y <= 880.f) {
                cout << "vi ska spara payment" << endl;
                create_payment(c);
                 //Change state
                next_state = std::make_unique<Year>("Year", c.data.all_years[yearindex]->get_year(), 
                                                                c.data.all_years[yearindex]->get_payments(),
                                                                yearindex);
                            cout << "Nästa state satt till " << next_state->get_state() << endl;
            }






        }
    }


    if (e.type == sf::Event::TextEntered)
    {
        for (auto& box : inputBoxes)
            box.handleText(e);
    }
    return true;
}

void AddPaymentState::update(Context& c){
    for (InputBox& InputBox : inputBoxes)
    {
        InputBox.update();
        InputBox.updateCaretPosition();
    }
};

void AddPaymentState::draw(Context&c) {
    c.window.clear(sf::Color::White);


    //Go back button
    vector<std::shared_ptr<sf::Drawable>> go_back_elements = ui_data.build_button(c, 1720, 20, 150, 50, "Go back");
    for (const std::shared_ptr<sf::Drawable>& element : go_back_elements) {
        c.window.draw(*element);
    }
    vector<std::shared_ptr<sf::Drawable>> add_payment_elements = ui_data.build_add_payment_window(c);
    for (const std::shared_ptr<sf::Drawable>& element : add_payment_elements) {
        c.window.draw(*element);
    }
    for (auto& box : inputBoxes){
        box.draw(c);
    }
};

void AddPaymentState::create_payment(Context& c){
    //En Payment innehåller entries, date, owner, receipt path. entries innehåller en Account
    //och en double sum. En account innehåller en id och ett name
    cout << "vi kör create payment" << endl;
    int date = 0;
    string owner = "";
    string receipt_path = "";
    string description = "";

    
    
    vector<shared_ptr<Entry>> entries;

    // Hämta date först
    for (InputBox& box : inputBoxes) {
        if (box.label == "Date" && !box.input.empty()) {
            date = stoi(box.input);
            cout << "vi har satt date till " << date << endl;
        }
    }
    // Hämta date
    for (InputBox& box : inputBoxes) {
        if (box.label == "Description" && !box.input.empty()) {
            description = box.input;
            cout << "vi har satt descripiton till " << date << endl;
        }
    }

    for (int row = 0; row < 5; row++) //går igenom alla rader
    {
        int account_id = 0; //varje rad ska ha dessa variabler ifyllda
        string account_name = "";
        shared_ptr<Account> account;

        int sum = 0;
        string comment = "";
        
        
        
        for (InputBox& box : inputBoxes){ //går igenom alla boxar
        
            if (box.label.find(to_string(row)) != string::npos){ //om boxen ligger på raden
                //Här skapar vi vår entry. Vi söker account_id,account_name,
              
                if(box.label.find("Account ID") != string::npos){//om typen är account id
                  
                    //Tilldelar account id samt hittar dess namn genom att kolla context datan
                    if (!box.input.empty()){
                    account_id = std::stoi(box.input);
                    }else{continue;}
                   
                    for (shared_ptr<Account> account : c.data.all_accounts){
                        if (account->get_id() == account_id){
                            account_name = account->get_name();
                        }
                    }
                    
   
                } else if (box.label.find("Debit sum") != string::npos){//Om typen är debit
                    //skapa double sum för denna entry
                    if (!box.input.empty()){
                        sum = std::stoi(box.input);
                    }else{continue;}
                    

                } else if (box.label.find("Credit sum") != string::npos){//Om typen är credit
                    //skapa double sum för denna entry
                     if (!box.input.empty()){
                        sum = -1*stoi(box.input) ;
                    }else{continue;}
                   

                } else if (box.label.find("Comment") != string::npos){//Om typen är comment
                    //skapa double sum för denna entry
                     if (!box.input.empty()){
                        comment = box.input ;
                    }else{continue;}

                } 
            
            }
            
        };
        if (account_id == 0){
            continue;
        };
        account = make_shared<Account>(account_id, account_name);
        entries.push_back(make_shared<Entry>(account, sum, comment));
        
    };
    //Create payment
    //payments.push_back(Payment(entries, date, owner, receipt_path));
    cout << "skapar payment med date: " << to_string(date) << endl;
    c.data.all_years[yearindex]->add_payment(Payment(entries, date, owner, receipt_path, description));
   
    
    
};