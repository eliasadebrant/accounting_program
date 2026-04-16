#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H
#include "allyears.h"

class SettingsState : public Programstate{
public:
    SettingsState(string state, int yearindex);
    string get_state() const override;
    bool handle_input(sf::Event& e, Context& c) override;
    void update(Context& c) override;
    void draw(Context&c) override;

private:
    int yearindex;
};

#endif;