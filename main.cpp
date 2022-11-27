#include <iostream>
#include <graphics.h>

/*
 * To compile:
 * g++ -o electron *.cpp -std=c++20 -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -lSDL_bgi -lSDL2 -lstdc++ -lm
*/

// SCREEN DIMENSIONS
const int HEIGHT = getmaxheight();
const int WIDTH = getmaxwidth();


int main(int argc, char *argv[])
{
  //////////////////////////////////////////////////////////////////////////////
  /// I N I T I A L I Z A T I O N //////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  // WINDOW ////////////////////////////////////////////////////////////////////
  setwinoptions ((char *)"E L E C T R O N", 0, 0, SDL_WINDOW_RESIZABLE);
  initwindow (WIDTH, HEIGHT); // screen size
  setbkcolor (YELLOW);
  cleardevice ();             // clears the screen and draws bg color

  //readimagefile ((char*)"title.bmp", 0, 0, 1000, 118);

  getch ();
  return 0;
}
