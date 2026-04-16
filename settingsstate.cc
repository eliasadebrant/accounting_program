#include "settingsstate.h"

SettingsState::SettingsState(string state, int yearindex) :
    Programstate(state),
    yearindex {yearindex}

    {}

string SettingsState::get_state() const{
    return state;
};

bool SettingsState::handle_input(sf::Event& e, Context& c){

};
void SettingsState::update(Context& c){
    
};
void SettingsState::draw(Context&c){

};