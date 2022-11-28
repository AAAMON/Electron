#include <iostream>
#include <graphics.h>
#include "button.h"

/*
 * To compile:
 * g++ -o electron *.cpp -std=c++20 -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -lSDL_bgi -lSDL2 -lstdc++ -lm
*/

// SCREEN DIMENSIONS
const int HEIGHT = getmaxheight();
const int WIDTH = getmaxwidth();
//bool exit = NOPE;

/// Initialises SDL_bgi graphics and window
void initSdlbgi()
{
  // windowed full screen size
  setwinoptions ((char *)"E L E C T R O N", 0, 0, SDL_WINDOW_RESIZABLE);
  initwindow (WIDTH, HEIGHT); 

  // so it runs faster, but we need to put refresh() to draw graphics
  sdlbgifast();
  setbkcolor (YELLOW);
}

void titleScreen()
{
  readimagefile((char*)"src/title.bmp", 0, 0, WIDTH, HEIGHT);
  Button button;
  createButton(button, WIDTH/2, HEIGHT/2, "Start", 9, &bStart);
  createButton(button, WIDTH/2, HEIGHT-300, "Credits", 7, &bStart);
}

int main(int argc, char *argv[])
{
  //////////////////////////////////////////////////////////////////////////////
  /// I N I T I A L I Z A T I O N //////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  // WINDOW ////////////////////////////////////////////////////////////////////
  initSdlbgi();
  titleScreen();
  
  // logic()
  // draw()
  // while(!exit)
  // {
  //   // logic()
  // }

  //readimagefile ((char*)"title.bmp", 0, 0, 1000, 118);

  getch ();
  return 0;
}
