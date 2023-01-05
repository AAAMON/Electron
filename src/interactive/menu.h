#ifndef INTERACTIVE_MENU_ELECTRON_H
#define INTERACTIVE_MENU_ELECTRON_H
#include "../core/project.h"


void activateMenuComponents(Electron& workspace);
void activateScrollMenu(Electron& workspace);
void activateMenuBarElement(Electron& workspace, MenuBar menuBar);
void drawMenuBarOptions(MenuBarElement menuBarElement);
void activateMenuBar(Electron& workspace);
void activateMenuBarOption(Electron& workspace, int i);
bool isMouseOnBox(int x1, int y1, int x2, int y2);
#endif