#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "observer.h"
#include "window.h"
#include "subject.h"
#include "info.h"

class GraphicsDisplay : public Observer {
    Xwindow xw; // Composition relationship with Xwindow
    const int gridSize; // Grid size
    const int cellSize; // Size of each cell in pixels

public:
    explicit GraphicsDisplay(int n);
    void notify(Subject &whoNotified) override;
    std::string getName() override;
};

#endif
