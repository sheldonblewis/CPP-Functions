#include <cstddef>
#include "cell.h"
#include <iostream>
using namespace std;

Cell::Cell(size_t r, size_t c): r{r}, c{c}, numAliveNeighbours{0}, state{State::Dead} {} // Cell::Cell

Info Cell::getInfo() const {
    Info i;
    i.row = r;
    i.col = c;
    i.state = state;
    return i;
} // Cell::getInfo

void Cell::setLiving() {
    state = State::Alive;
} // Cell::setLiving

void Cell::reset() {
    numAliveNeighbours = 0;
} // Cell::reset

std::string Cell::getName() {
    return "(" + std::to_string(r) + "," + std::to_string(c) + ")";
} // Cell::getName

void Cell::recalculate() {} // Cell::recalculate

void Cell::broadcastIfAlive() {} // Cell::broadcastIfAlive

void Cell::notify( Subject & s ) {} // Cell::notify
