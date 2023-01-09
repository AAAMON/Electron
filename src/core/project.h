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

enum {
  NEW_FILE, LOAD_FILE, SAVE_FILE, DELETE_FILE
};

enum {
  STATUS_BAR, STATUS_BAR_TEXT, MESSAGE, WORKSPACE, COMPONENTS, WIRES, 
  BIG_BOX, HOLLOW_BOX, BUTTON_BOX, MENU_BAR_TEXT, MENU_TEXT, 
  MENU_COMPONENT_TEXT, MENU_BAR, SCROLL_DETAIL, SELECTION_INACTIVE, SELECTION_ACTIVE,
  SELECTION
};


struct Color
{
  int r;
  int g;
  int b;
};

// Workspace
struct Electron
{
  int nrOfComponents;
  Component components[50];
  int nrOfWires;
  Wire wires[200];
  float panningX;
  float panningY;
  float zoom;

  Menu menu;
  MenuBar menuBar;

  char currentFile[100];
  char currentMessage[100];

  bool secrets;
  bool input;
  bool tutor;
};

//////////////////////////////////////////////////////////////////////////////
/// P R O G R A M   F U N C T I O N S ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void initSdlbgi();
void titleScreen(bool& isRunning);
void message(const char*);
void initElectron(Electron& workspace);
void draw(Electron& workspace);
void logic(Electron& workspace);
void drawStatusBar(Electron workspace);
void drawTutor(Electron workspace);
void showCredits();
void showHelp();
#endif