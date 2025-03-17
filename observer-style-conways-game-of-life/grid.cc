#include <iostream>
#include "grid.h"
#include "graphicsdisplay.h"
using namespace std;

Grid::~Grid() {
    delete td;
    theGrid.clear();
}

void Grid::printCellNeighbours() {
    for (auto &row : theGrid) {
        for (auto &cell : row) {
            cout << cell.getName() << ": " << cell.getObserverNames() << endl;
        }
    }
}

void Grid::turnOn( size_t r, size_t c ) { 
    if ( r >= theGrid.size() ||  c >= theGrid.size() ) return;
    theGrid[r][c].setLiving();
}

void Grid::init( size_t n ) {
    theGrid.clear();
    
    // Ensure old TextDisplay is deleted
    delete td;  
    td = new TextDisplay(n);  // Now it's properly defined

    theGrid.resize(n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            theGrid[i].emplace_back(i, j);
        }
    }

    // Attach td + cell neighbours
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            auto &self = theGrid[i][j];
            self.attach(td);  // `td` is now fully defined

            for (int rr = i - 1; rr <= (int)i + 1; rr++) {
                for (int cc = j - 1; cc <= (int)j + 1; cc++) {
                    if ((rr != (int)i || cc != (int)j) &&
                         rr >= 0 && cc >= 0 &&
                         rr < (int)n && cc < (int)n) {
                        self.attach(&theGrid[rr][cc]);
                    }
                }
            }
        }
    }
}


void Grid::tick() {
    notifyAll();  // Step 1: Tell all live cells to broadcast their state

    // Step 2: Compute the new state for each cell
    std::vector<std::vector<State>> nextState(theGrid.size(), std::vector<State>(theGrid.size(), State::Dead));

    for (size_t r = 0; r < theGrid.size(); ++r) {
        for (size_t c = 0; c < theGrid.size(); ++c) {
            Cell &cell = theGrid[r][c];
            size_t aliveNeighbours = cell.getAliveNeighbours();  // Count of live neighbors

            // Apply Game of Life rules
            if (cell.getInfo().state == State::Alive) {
                if (aliveNeighbours < 2 || aliveNeighbours > 3) {
                    nextState[r][c] = State::Dead;
                } else {
                    nextState[r][c] = State::Alive;
                }
            } else { // Dead cell
                if (aliveNeighbours == 3) {
                    nextState[r][c] = State::Alive;
                }
            }
        }
    }

    // Step 3: Apply new states to all cells
    for (size_t r = 0; r < theGrid.size(); ++r) {
        for (size_t c = 0; c < theGrid.size(); ++c) {
            if (nextState[r][c] == State::Alive) {
                theGrid[r][c].setLiving();
            } else {
                theGrid[r][c].reset();
            }
        }
    }

    updateDisplays();  // Step 4: Notify the TextDisplay

    // Step 5: Reset `numAliveNeighbours` for next tick
    for (size_t r = 0; r < theGrid.size(); ++r) {
        for (size_t c = 0; c < theGrid.size(); ++c) {
            theGrid[r][c].reset();
        }
    }
}


void Grid::notifyAll() {
    for (auto &row : theGrid) {
        for (auto &cell : row) {
            cell.broadcastIfAlive();
        }
    }
}

void Grid::reset() {
    for (auto &row : theGrid) {
        for (auto &cell : row) {
            cell.reset();
        }
    }
}

void Grid::updateDisplays() {
    for (auto &row : theGrid) {
        for (auto &cell : row) {
            cell.notifyObservers();
        }
    }
}


std::ostream &operator<<( std::ostream &out, const Grid &g ) {
    if (g.td) out << *(g.td);
    return out;
}
