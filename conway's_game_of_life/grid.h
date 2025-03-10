#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <stdexcept> // defines std::invalid_argument
#include "cell.h"

class TextDisplay;
class Observer;

// Grid is initially empty. Sets up a TextDisplay observer when init() is called
// and the grid is initialized with cell objects.
class Grid {
    std::vector<std::vector<Cell>> theGrid;  // The actual grid.
    TextDisplay *td = nullptr;               // The text display is an observer on each cell.
    Observer    *ob = nullptr;               // Graphical display observer attached to each cell.
                                             // Only needed for the bonus.

    // Add private members, if necessary.
 
    void reset();                       // Clears all counts of live neighbours in the grid.
    void notifyAll();                   // Tell all cells to broadcast if alive.
    void updateDisplays();              // On each cell's behalf, tell the displays to update their info.

  public:
    // Default ctor not needed, but may be added if you feel it is necessary.
    ~Grid();
  
    // Outputs the name of each cell, followed by its list of neighbours, to stdout.
    // Format for part a) is:
    // (0,0): (0,1) (1,0) (1,1) \n
    // (0,1): (0,0) (1,0) (0,2) (1,1) (1,2) \n
    // ...
    //
    // Format for part b) is:
    // (0,0): (0,1) (1,0) (1,1) TD \n
    // (0,1): (0,0) (1,0) (0,2) (1,1) (1,2) TD \n
    // ...
    void printCellNeighbours();

    // Sets up an n x n grid, and adds each cell's neighbour and the text display as observers. 
    // Clears old grid, if necessary. 
    void init( std::size_t n );       

    // Marks cell at row r, col c as alive by calling Cell::setLiving().
    void turnOn( std::size_t r, std::size_t c );  

    // Next tick of the simulation.
    void tick();
    
    friend std::ostream & operator<<( std::ostream & out, const Grid & g );
};

// Uses the TextDisplay to output the grid information.
std::ostream & operator<<( std::ostream & out, const Grid & g );

#endif
