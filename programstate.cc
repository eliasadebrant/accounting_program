#include "programstate.h"

Programstate::Programstate(string state)
        : Runnable(/*x, y*/),
          state{state}
        {}

unique_ptr<Programstate> Programstate::consume_next_state() {
    return move(next_state);
}