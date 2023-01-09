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

bool isRunning = YEAH;

// To compile (u need SDL_BGI):
// g++ -o bin/electron src/core/*.cpp src/gui/*.cpp src/interactive/*.cpp -std=c++20 -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -lSDL_bgi -lSDL2 -lstdc++ -lm
void doSecretStuff(int& a, int& b, int& c, int& d);

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
    logic(workspace);
    if (workspace.secrets)
      doSecretStuff(phase, r, g, b);

    // Updates screen
    // please please please don't modify this it didn't work before but one day
    // it miraculously started working and idk how or why so just leave it be
    refresh();
  }

  return EXIT_SUCCESS;
}

