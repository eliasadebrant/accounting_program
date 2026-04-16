#ifndef CONTEXT_H    
#define CONTEXT_H 
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
//#include "year.h"
//#include "account.h"

using namespace std;

class Year;
class Account;

class DataContext{
public:
    vector<shared_ptr<Year>> all_years;
    vector<shared_ptr<Account>> all_accounts;
    
    DataContext(vector<shared_ptr<Year>> all_years, vector<shared_ptr<Account>> all_accounts);
       

};


class Context {
public:
    sf::RenderWindow& window;
    sf::View& view;
    sf::Font& font;
    DataContext& data;

    Context(sf::RenderWindow& window, sf::View& view, sf::Font& font, DataContext& data);
};

#endif
