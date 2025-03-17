#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include "cell.h"
#include "graphicsdisplay.h"

class TextDisplay;
class Observer;

class Grid {
    std::vector<std::vector<Cell>> theGrid;
    TextDisplay *td = nullptr;
    GraphicsDisplay *gd = nullptr; // NEW: Graphics Display
    Observer *ob = nullptr;

    void reset();
    void notifyAll();
    void updateDisplays();

public:
    ~Grid();
    void printCellNeighbours();
    void init(std::size_t n);
    void turnOn(std::size_t r, std::size_t c);
    void tick();
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

std::ostream &operator<<(std::ostream &out, const Grid &g);

#endif
