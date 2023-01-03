#ifndef ELECTRON_ELECTRON_H
#define ELECTRON_ELECTRON_H
#include <graphics.h>
//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

const int HEIGHT = getmaxheight();
const int WIDTH = getmaxwidth();

enum {
  NEW_FILE, LOAD_FILE, SAVE_FILE, DELETE_FILE
};

struct Status
{
  bool titleIsRunning;
  bool isRunning;
  bool menuShow;
  char currentFile[100];
  char currentMessage[100];
};

#endif