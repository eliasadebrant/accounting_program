#ifndef INPUTBOX_H
#define INPUTBOX_H

#include "context.h"

class InputBox{

public:
    InputBox(Context& c, string label);
    void handleText(const sf::Event& event);
    void update();
    void updateCaretPosition();
    void draw(Context & c);


    sf::RectangleShape box;
    Context& c;
    sf::Text text;
    std::string input;
    bool focused = false;
    string label;
    sf::RectangleShape caret;
    sf::Clock caretClock;
    bool showCaret = true;
};
#endif