#include <iostream>
#include "grid.h"
#include "textdisplay.h"
using namespace std;

Grid::~Grid() {
    theGrid.clear();
} // Grid::~Grid

void Grid::printCellNeighbours() {
    for (auto &row : theGrid) {
        for (auto &cell : row) {
            cout << cell.getName() << ": " << cell.getObserverNames() << endl;
        }
    }
} // Grid::printCellNeighbours

void Grid::turnOn( size_t r, size_t c ) { 
    if ( r < 0 || r >= theGrid.size() ||  c < 0 || c >= theGrid.size() ) return;
    theGrid[r][c].setLiving();
} // Grid::turnOn

void Grid::init( size_t n ) {
    theGrid.clear();

    if (!td) {
        td = new TextDisplay(n);
    } else {}

    // Create new NxN Cells
    theGrid.resize(n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            theGrid[i].emplace_back(i,j);
        }
    }

    // Attach td + cell neighbours
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            auto &self = theGrid[i][j];
            self.attach(td);

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
} // Grid::init

void Grid::reset() {} // Grid::reset

void Grid::notifyAll() {} // Grid::notifyAll

void Grid::updateDisplays() {} // Grid::updateDisplays

void Grid::tick() {} // Grid::tick

std::ostream &operator<<( std::ostream & out, const Grid & g ) {
    if (g.td) out << *(g.td);
    return out;
}
