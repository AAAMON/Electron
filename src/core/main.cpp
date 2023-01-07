#include <iostream>
#include <graphics.h>
#include "project.h"
#include "components.h"
#include "../gui/menu.h"
#include "files.h"


bool isRunning = YEAH;

// To compile (u need SDL_BGI):
// g++ -o bin/electron src/core/*.cpp src/gui/*.cpp -std=c++20 -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -lSDL_bgi -lSDL2 -lstdc++ -lm

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
    // Deals with all the input/updating
    
    cleardevice();
    // Draws everyting on SDL_Surface
    loadTheme(workspace,0);
    draw(workspace);
    strcpy(workspace.currentMessage, "");
    logic(workspace, isRunning);
    

    // Updates screen
    // please please please don't modify this it didn't work before but one day
    // it miraculously started working and idk how or why so just leave it be
    refresh();
  }

  return EXIT_SUCCESS;
}
