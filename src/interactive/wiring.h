#ifndef INTERACTIVE_WIRING_ELECTRON_H
#define INTERACTIVE_WIRING_ELECTRON_H
#include "../core/project.h"



void wireComponents(Electron& workspace);
void drawWirePoints(Electron workspace, Wire wire);
void drawWire(Electron& workspace, int id, int mouse);
void drawWire(Electron workspace, int x1, int y1, int x2, int y2, bool direction1, bool direction2);
void drawWires(Electron workspace);
void setUpWirePoints(Electron& workspace, int id);

#endif