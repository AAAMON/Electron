#ifndef WORKSPACE_ELECTRON_H
#define WORKSPACE_ELECTRON_H
#include "project.h"
int activeWire(Electron workspace);
void activateZooming(Electron& workspace);
void activatePanning(Electron& workspace);
bool isMouseOnWorkspace(Electron workspace);
int activeComponent(Electron workspace);
int activeBond(Electron workspace);
void drawWorkspaceComponent(Electron workspace, Component component);
bool isMouseOnComponent(Electron workspace, int x1, int y1, int x2, int y2);
bool isMouseOnWire(Electron workspace, int i);
#endif