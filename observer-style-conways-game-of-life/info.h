#ifndef _INFO_H
#define _INFO_H
#include <cstddef> // defines std::size_t i.e. an unsigned int

// State of the cell i.e. either dead or alive.
enum class State { Dead, Alive };

// Information for the cell to return i.e. its state (Alive/Dead) and position in grid.
struct Info {
    State state;
    std::size_t row, col;  
};

#endif
