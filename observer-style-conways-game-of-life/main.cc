// Conway’s Game of Life (https://en.wikipedia.org/wiki/Conways_Game_of_Life)

#include <iostream>
#include <string>
#include "grid.h"
#include "info.h"
using namespace std;

int main() {
    string cmd;
    Grid g;

    while ( cin >> cmd ) {
        if ( cmd == "new" ) {
            int n;
            cin >> n; 
            g.init(n);
        } else if ( cmd == "neighbours" ) {
            g.printCellNeighbours();
        } else if ( cmd == "init" ) {
            int r, c;
            while ( cin >> r >> c ) {
                if ( r == -1 && c == -1 ) break;
                g.turnOn(r,c);
            } // while
        } else if ( cmd == "step" ) {
            g.tick();
        } else if ( cmd == "steps" ) {
            int n;
            cin >> n;
            for ( int i = 0; i < n; ++i ) g.tick();
        } else if ( cmd == "print" ) {
            cout << g;
        } // if
    } // while
} // main
