#include "programstate.h"
#include "allyears.h"
using namespace std;
class MenuState : public Programstate {
public:
    MenuState(string state);

    string get_state() const override;
    bool handle_input(sf::Event& e, Context& c) override;
    void update(Context& c) override;
    void draw(Context&c) override;
};