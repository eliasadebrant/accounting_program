#include "accounting.h"
#include "menuState.h"
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include "year.h"


Accounting::Accounting()
    {}
/*
Programstate* Accounting::change(Programstate* active_state, Context& c){
    if (active_state->get_next_state() == nullptr){
        return active_state;
    }

    if(active_state->get_state() == "MenuState"){


        if(active_state->get_next_state()->get_state() == "AllYears"){
            cout << "går in i allyears" << endl;
            return active_state->get_next_state();
        } else{
            return active_state;
        }




    }else if(active_state->get_state() == "AllYears"){


        if(active_state->get_next_state()->get_state() == "Year"){
            cout << "går in i year" << endl;
            return active_state->get_next_state();
        } else if(active_state->get_next_state()->get_state() == "MenuState"){
            cout << "går tillbaka till menu" << endl;
            return active_state->get_next_state();
        }else{
            return active_state;
        }



    }else if(active_state->get_state() == "Year"){


        if(active_state->get_next_state()->get_state() == "AllYears"){
            cout << "går tillbaka till allyears" << endl;
            return active_state->get_next_state();
        }else{
            return active_state;
        }
    }
    
    
    else{
        return active_state;
    }
    
}
*/
int Accounting::run(){

    sf::Event e;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Test Window");
    sf::View view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
    sf::Font font;
    if (!font.loadFromFile("resources/arial.ttf")) {
        std::cerr << "Error loading font\n";
    } 
    
    /////////////////////INITIALIZING SOME START VALUES////////////////////////
    vector<shared_ptr<Account>> accounts{make_shared<Account>(1920, "Plusgiro"), 
                                        make_shared<Account>(2440, "Leverantörsskulder")};


   vector<shared_ptr<Entry>> entries0{
    make_shared<Entry>(accounts[0], -100, "pengar"),
    make_shared<Entry>(accounts[1], 100, "skuld")
    };
    std::vector<Payment> payments0{{entries0, 20230701, "Elias Adebrant", "resourses/receipts/kvitto1", "betalning faktura"}};


    DataContext data{vector<shared_ptr<Year>>{std::make_shared<Year>("Year", "23/24", payments0, 0), 
                                            std::make_shared<Year>("Year", "24/25", std::vector<Payment>{}, 1), 
                                            std::make_shared<Year>("Year", "25/26", std::vector<Payment>{}, 2)}, 
                                            accounts}; 
    Context c{window, view, font, data};

    //////////////////////////////////////////////////////////////////////////////////

    stack <unique_ptr<Programstate>> state_stack;
    state_stack.push(make_unique<MenuState>("MenuState"));
    
    while(! state_stack.empty())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            break;  
        }
        
        
        
       
        while (window.isOpen())
        {  

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                
                break;  
            }
            

            c.window.setView(window.getDefaultView());
            Programstate* active_state = state_stack.top().get();
            
           
            
            c.window.clear(sf::Color::White); 

            active_state -> update(c); 
            
            active_state -> draw(c);

            // Event-loop: Kontrollera händelser
            while (window.pollEvent(e))
            {
                // Hantera fönsterstängning
                if (e.type == sf::Event::Closed)
                {
                    window.close();
                } 
                
                 active_state->handle_input(e, c);

            
            auto next = active_state->consume_next_state();

                if (next) {
                    state_stack.push(std::move(next));
                    active_state = state_stack.top().get();
                }
            }
 
            c.window.display();
        }
    }
    return 0;
}
    
    



int main()
{ 
    
    Accounting app;
    app.run();
    //state_regulator ->preloadresources();


   
  return 0;
  
};
