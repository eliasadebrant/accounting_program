#include "inputbox.h"
#include "iostream"

InputBox::InputBox(Context& c, string label):
    c {c},
    label {label}
{ 
    caret.setSize(sf::Vector2f(2.f, 30.f));
    caret.setFillColor(sf::Color::Black);
    text.setFont(c.font);
};

void InputBox::handleText(const sf::Event& event)
{
    if (!focused) {return;}

    if (event.text.unicode == 8) // backspace
    {
        if (!input.empty())
            input.pop_back();
    }
    else if (event.text.unicode >= 32 && event.text.unicode < 128)
    {
        input += static_cast<char>(event.text.unicode);
    }

    text.setString(input);
};

void InputBox::update()
{
    if (caretClock.getElapsedTime().asSeconds() > 0.5f)
    {
        showCaret = !showCaret;
        caretClock.restart();
    }
}

void InputBox::updateCaretPosition()
{
    sf::FloatRect textBounds = text.getGlobalBounds();
    caret.setPosition(
        textBounds.left + textBounds.width + 2,
        textBounds.top
    );
};

void InputBox::draw(Context & c)
{
    c.window.draw(box);
    c.window.draw(text);

    if (focused && showCaret)
        c.window.draw(caret);
}