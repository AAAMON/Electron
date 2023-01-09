#include <iostream>
#include <graphics.h>
#include "project.h"
#include "components.h"
#include "../gui/menu.h"
#include "files.h"
int r = 255;
int g = 0;
int b = 0;
int phase = 0;
// secret
void doSecretStuff()
{
  switch(phase)
  {
    case 0:
      r--;
      g++;
      if (!r)
        phase = 1;
      break;
    case 1:
      g--;
      b++;
      if (!g)
        phase = 2;
      break;
    case 2:
      b--;
      r++;
      if (!b)
        phase = 0;
      break;
    default:
      break;
  }

  setrgbpalette(4, r, g, b);
}
bool isRunning = YEAH;

// To compile (u need SDL_BGI):
// g++ -o bin/electron src/core/*.cpp src/gui/*.cpp src/interactive/*.cpp -std=c++20 -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -lSDL_bgi -lSDL2 -lstdc++ -lm

int main()
{
  //////////////////////////////////////////////////////////////////////////////
  /// T I T L E   S C R E E N //////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  initSdlbgi();
  titleScreen(isRunning);

  // even if it wouldn't execute the main loop, with this we can skip waiting
  // for the initializations
  if (!isRunning)
    return EXIT_SUCCESS;

  //////////////////////////////////////////////////////////////////////////////
  /// M A I N   S C R E E N ////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  cleardevice(); // if stuff takes too long just put a loading screen here...

  // INITIALIZATION
  Electron workspace;
  initElectron(workspace);
  // MAIN LOOP!
  while(isRunning == YEAH)
  {
    // checking if esc was pressed
    xkbhit();
    if (lastkey() == KEY_ESC)
      isRunning = NOPE;
    
    // without this, checking if ESC was pressed won't work.
    // Why? ,,,,I would like to know as well.
    delay(1);

    cleardevice();
    // Draws everyting on SDL_Surface
    draw(workspace);
    
    // Deals with all the input/updating
    logic(workspace, isRunning);
    if (workspace.secrets)
      doSecretStuff();

    // Updates screen
    // please please please don't modify this it didn't work before but one day
    // it miraculously started working and idk how or why so just leave it be
    refresh();
  }

  return EXIT_SUCCESS;
}

