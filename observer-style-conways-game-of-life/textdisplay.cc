#include "textdisplay.h"
#include "subject.h"
#include <iostream>

using namespace std;

TextDisplay::TextDisplay(size_t n) {
    theDisplay.resize(n, vector<char>(n, '_'));
}

void TextDisplay::notify(Subject &whoNotified) {
    Info info = whoNotified.getInfo();
    if (info.row < theDisplay.size() && info.col < theDisplay.size()) {
        theDisplay[info.row][info.col] = (info.state == State::Alive) ? 'X' : '_';
    }
}

std::string TextDisplay::getName() {
    return "TD";
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (const auto &row : td.theDisplay) {
        for (char c : row) {
            out << c;
        }
        out << endl;
    }
    return out;
}
