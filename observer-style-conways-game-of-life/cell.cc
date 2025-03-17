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
    notifyObservers();
} // Cell::setLiving

void Cell::reset() {
    numAliveNeighbours = 0;
} // Cell::reset

std::string Cell::getName() {
    return "(" + std::to_string(r) + "," + std::to_string(c) + ")";
} // Cell::getName

void Cell::recalculate() {
    if (state == State::Alive) {
        if (numAliveNeighbours < 2 || numAliveNeighbours > 3) {
            state = State::Dead;
        }
    } else {
        if (numAliveNeighbours == 3) {
            state = State::Alive;
        }
    }
    notifyObservers();
} // Cell::recalculate

void Cell::broadcastIfAlive() {
    if (state == State::Alive) notifyObservers();
} // Cell::broadcastIfAlive

void Cell::notify(Subject &s) {
    if (s.getInfo().state == State::Alive) numAliveNeighbours++;
} // Cell::notify

size_t Cell::getAliveNeighbours() const {
    return numAliveNeighbours;
}
