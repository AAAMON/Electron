#include "project.h"
#include "../gui/button.h"
#include "../gui/menu.h"

//////////////////////////////////////////////////////////////////////////////
/// P R O G R A M   V A R I A B L E S ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

bool titleIsRunning = YEAH;

//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// Initialises SDL_bgi graphics and window
void initSdlbgi()
{
  // windowed full screen size
  setwinoptions ((char *)"E L E C T R O N", 0, 0, SDL_WINDOW_FULLSCREEN);
  initwindow (WIDTH, HEIGHT); 

  // so it runs faster, but we need to put refresh() to draw graphics
  sdlbgifast();
  setbkcolor (YELLOW);
}

// Starts title screen
void titleScreen(bool& isRunning)
{
  // Initialization
  Button buttonStart;
  Button buttonCredits;
  createButton(buttonStart, WIDTH/2, HEIGHT/2, "Start", 9, &bVoid);
  createButton(buttonCredits, WIDTH/2, HEIGHT-300, "Credits", 7, &bCredits);

  // Drawing
  // since nothing needs to get redrawn, it's safe to draw everything only once
  // the image path must be relative to compile location (aka folder "Electron")
  readimagefile((char*)"assets/title.bmp", 0, 0, WIDTH, HEIGHT);
  message("=== Esc button to exit ===");
  drawButton(buttonStart);
  drawButton(buttonCredits);
  refresh();

  // Run loop
  while(titleIsRunning)
  {
    int ev = getevent();
    // apparently ismouseclick() is much faster than mouseclick()
    
    // can't use activateButton here because it's the only one that needs an argument
    // start main program
    if (WM_LBUTTONDOWN == ev && IsMouseOnButton(buttonStart))
      titleIsRunning = NOPE;

    // show credits
    activateButton(buttonCredits);
    
    // exit the program
    if (KEY_ESC == ev || QUIT == ev)
    {
      titleIsRunning = NOPE;
      isRunning = NOPE;
    }
  }
}




//////////////////////////////////////////////////////////////////////////////
/// M I S C //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// Immediately displays a red message on the bottom of the screen
void message(const char* text)
{
  // message box
  setcolor (WHITE);
  setfillstyle (SOLID_FILL, getcolor ());
  bar(WIDTH/2-350, HEIGHT-50, WIDTH/2+350, HEIGHT-10);

  // message text
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
  settextjustify (CENTER_TEXT, CENTER_TEXT);
  setcolor (RED);
  outtextxy (WIDTH / 2, HEIGHT - 30,(char*)text);
  //refresh();
}
