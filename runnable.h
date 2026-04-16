//Runnable.h
#ifndef RUNNABLE_H
#define RUNNABLE_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Context;


class Runnable
{
public:
    Runnable(/*float x, float y*/);
    virtual ~Runnable() = default;

    virtual void update(Context& c) = 0;
    virtual void draw(Context& c) = 0;
    virtual bool handle_input(sf::Event& e, Context& c) = 0;


    //protected:
    //float x;
    //float y;


    
};
#endif
