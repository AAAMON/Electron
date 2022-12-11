#include <graphics.h>
#include "project.h"
#include "components.h"
#include "../gui/menu.h"


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
  // if (!isRunning)
  //   return EXIT_SUCCESS;

  //////////////////////////////////////////////////////////////////////////////
  /// M A I N   S C R E E N ////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  cleardevice(); // if stuff takes too long just put some loading screen here...
  
  // INITIALIZATIONS...
  Menu menu;
  initMenu(menu);
  //printMenu(menu);

  // MAIN LOOP!
  while(isRunning == YEAH)
  {
    cleardevice();
    //logic();
    //draw();
    
    // put this in logic();
    kbhit();
    if (lastkey() == KEY_ESC)
      isRunning = NOPE;
    activateScrollMenu(menu);

    bar(menu.width - menu.buttonWidth, 0, menu.width, menu.height/2);
    bar(menu.width - menu.buttonWidth, menu.height/2, menu.width, menu.height);
    // put this in draw();
    drawMenu(menu);
    message("=== Esc button to exit ===");

    // please please please don't modify this it didn't work before but one day
    // it miraculously started working and idk how or why so just leave it be
    refresh();
  }

  return EXIT_SUCCESS;
}
