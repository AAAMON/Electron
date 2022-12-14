#ifndef PROJECT_ELECTRON_H
#define PROJECT_ELECTRON_H
#include <graphics.h>
#include "components.h"
#include "../gui/menu.h"

//////////////////////////////////////////////////////////////////////////////
/// P R O G R A M   C O N S T A N T S ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

const int HEIGHT = getmaxheight();
const int WIDTH = getmaxwidth();


struct menuBarButton
{
  char text[10];
  int nrOfElements;
  int x;
  int y;
  int w;
};

// Workspace
struct Electron
{
  int nrOfComponents;
  Component components[50];
  float panningX;
  float panningY;
  float zoom;

  Menu menu;
  menuBarButton menuBarButtons[10];

  char currentFile[30];
};




//////////////////////////////////////////////////////////////////////////////
/// P R O G R A M   F U N C T I O N S ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void initSdlbgi();
void titleScreen(bool& isRunning);
void message(const char*);

//////////////////////////////////////////////////////////////////////////////
/// W O R K S P A C E   F U N C T I O N S ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void initElectron(Electron& workspace);
void activatePanning(Electron& workspace);
void activateZooming(Electron& workspace);
void drawWorkspaceComponent(Electron workspace, Component component);
void draw(Electron workspace);
void logic(Electron& workspace, bool& isRunning);
bool isMouseOnBox(int x1, int y1, int x2, int y2);
void drawStatusBar(Electron workspace);
bool isMouseOnComponent(Electron workspace, int x1, int y1, int x2, int y2);


#endif