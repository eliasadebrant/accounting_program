#include "context.h"
#include <vector>

DataContext::DataContext(vector<shared_ptr<Year>> all_years, vector<shared_ptr<Account>> all_accounts) :
    all_years{all_years},
    all_accounts{all_accounts}
    {}


Context::Context(sf::RenderWindow& window, sf::View& view, sf::Font& font, DataContext& data) :
    window(window), 
    view(view),
    font(font),
    data(data)
    {}
    
