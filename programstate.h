#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <string>
#include "runnable.h"
#include <memory>

using namespace std;

class Context;

class Programstate : public Runnable
{
    public:
        Programstate(string state);
        virtual ~Programstate() = default;
        virtual string get_state() const = 0;
        virtual bool handle_input(sf::Event& e, Context& c) override = 0;
        virtual void update(Context& c) override = 0;
        virtual void draw(Context&c) override = 0;
        unique_ptr<Programstate> consume_next_state();


    protected:
        string state = "Programstate";
        std::unique_ptr<Programstate> next_state{nullptr};

};
#endif