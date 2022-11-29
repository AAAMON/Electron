#include "project.h"
#include "button.h"

bool titleIsRunning;
bool isRunning = YEAH;

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

// Starts title screen
void titleScreen()
{
  readimagefile((char*)"src/title.bmp", 0, 0, WIDTH, HEIGHT);
  Button buttonStart;
  Button buttonCredits;
  createButton(buttonStart, WIDTH/2, HEIGHT/2, "Start", 9, &bVoid);
  createButton(buttonCredits, WIDTH/2, HEIGHT-300, "Credits", 7, &bCredits);
  message();
  refresh();

  titleIsRunning = YEAH;
  while(titleIsRunning)
  {
    // apparently ismouseclick() is much faster than mouseclick()

    // can't use activateButton here because it's the only one that needs an argument
    if (ismouseclick(WM_LBUTTONDOWN) && IsMouseOnButton(buttonStart))
    {
      titleIsRunning = NOPE;
    }
    activateButton(buttonCredits);
    if (ismouseclick(WM_RBUTTONDOWN))
      break;
  }

}

void message()
{
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
  settextjustify (CENTER_TEXT, TOP_TEXT);
  //outtextxy (WIDTH / 2, 10, str); // custom message
  setcolor (WHITE);
  setfillstyle (SOLID_FILL, getcolor ());
  bar(WIDTH/2-350, HEIGHT-120, WIDTH/2+350, HEIGHT-70);
  setcolor (RED);
  outtextxy (WIDTH / 2, HEIGHT - 100,(char*)"=== Start button or right click to exit ===");
  refresh ();
}