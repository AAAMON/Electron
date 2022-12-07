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
  if (!isRunning)
    return EXIT_SUCCESS;


  

  //////////////////////////////////////////////////////////////////////////////
  /// M A I N   S C R E E N ////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  cleardevice();
  Menu menu;
  initMenu(menu);
  //setenv((char*)SDL_RENDERER_ACCELERATED, "auto", 1);
  while(isRunning == YEAH)
  {
    cleardevice();
    //logic();
    //draw();
    // put this in logic();
    kbhit();
    if (lastkey() == KEY_ESC)
      isRunning = NOPE;
    
    // put this in draw();
    
    drawMenu(menu);
    message("=== Esc button to exit ===");
    refresh();
  }

  return EXIT_SUCCESS;
}
