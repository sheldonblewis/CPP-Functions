#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(int n) 
    : xw(500, 500), gridSize(n), cellSize(500 / n) {}

void GraphicsDisplay::notify(Subject &whoNotified) {
    Info info = whoNotified.getInfo();
    int x = info.col * cellSize;
    int y = info.row * cellSize;
    int color = (info.state == State::Alive) ? Xwindow::Black : Xwindow::White;

    xw.fillRectangle(x, y, cellSize, cellSize, color);
}

std::string GraphicsDisplay::getName() {
    return "GD";
}
