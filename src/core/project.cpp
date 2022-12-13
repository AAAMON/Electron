#include "project.h"
#include "files.h"
#include "components.h"
#include "../gui/button.h"
#include "../gui/menu.h"
#include "../gui/boxes.h"


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
  setbkcolor (BLACK);
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
    kbhit();
    // apparently ismouseclick() is much faster than mouseclick()
    
    // can't use activateButton here because it's the only one that needs an argument
    // start main program
    if (ismouseclick(WM_LBUTTONDOWN) && IsMouseOnButton(buttonStart))
      titleIsRunning = NOPE;

    // show credits
    activateButton(buttonCredits);
    
    // exit the program
    if (lastkey() == KEY_ESC)
    {
      titleIsRunning = NOPE;
      isRunning = NOPE;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
/// W O R K S P A C E   F U N C T I O N S ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////



// initialises the current workspace
void initElectron(Electron& workspace, char* startFile)
{
  // COMPONENTS
  workspace.nrOfComponents = 0;
  loadFile(startFile, workspace);
  // MENU
  initMenu(workspace.menu);
  // SCREEN
  workspace.panningX = 0;
  workspace.panningY = 0;
  workspace.zoom = 1;
}

void activateZooming(Electron& workspace)
{
  int x = mousex();
  while (workspace.menu.show && isMouseOnBox(workspace.menu.width, 24, WIDTH, HEIGHT) && ismouseclick(WM_RBUTTONDOWN) && ismouseclick(WM_MBUTTONDOWN))
  {
    if (mousex() - x > 0)
    {
      workspace.zoom += 0.007;
      workspace.panningX -= 5;
      workspace.panningY -= 2.5;
    }
    if (mousex() - x < 0)
    {
      workspace.zoom -= 0.007;
      workspace.panningX += 5;
      workspace.panningY += 2.5;
    }
      
    draw(workspace);
    refresh();
  }
  while (!workspace.menu.show && isMouseOnBox(workspace.menu.buttonWidth, 24, WIDTH, HEIGHT) && ismouseclick(WM_RBUTTONDOWN) && ismouseclick(WM_MBUTTONDOWN))
  {
    if (mousex() - x > 0)
    {
      workspace.zoom += 0.007;
      workspace.panningX -= 5;
      workspace.panningY -= 2.5;
    }
    if (mousex() - x < 0)
    {
      workspace.zoom -= 0.007;
      workspace.panningX += 5;
      workspace.panningY += 2.5;
    }
      
    draw(workspace);
    refresh();
  }
}

void activatePanning(Electron& workspace)
{
  int panPrevX = workspace.panningX;
  int panPrevY = workspace.panningY;
  int x = mousex();
  int y = mousey();
  while (workspace.menu.show && isMouseOnBox(workspace.menu.width, 24, WIDTH, HEIGHT) && ismouseclick(WM_MBUTTONDOWN)  && !ismouseclick(WM_RBUTTONDOWN))
  {

    workspace.panningX = panPrevX + mousex() - x;
    workspace.panningY = panPrevY + mousey() - y;
    draw(workspace);
    refresh();
  }
  while (!workspace.menu.show && isMouseOnBox(workspace.menu.buttonWidth, 24, WIDTH, HEIGHT) && ismouseclick(WM_MBUTTONDOWN)  && !ismouseclick(WM_RBUTTONDOWN))
  {

    workspace.panningX = panPrevX + mousex() - x;
    workspace.panningY = panPrevY + mousey() - y;
    draw(workspace);
    refresh();
  }
}

void drawWorkspaceComponent(Electron workspace, Component component);
// draws the current workspace
void draw(Electron workspace)
{
  cleardevice();
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    drawWorkspaceComponent(workspace, workspace.components[i]);
  }
  drawMenu(workspace.menu);
  message("=== Esc button to exit ===");
}

// updates the current workspace
void logic(Electron& workspace, bool& isRunning)
{
  kbhit();
  if (lastkey() == KEY_ESC)
    isRunning = NOPE;
  
  activateScrollMenu(workspace.menu);
  activateZooming(workspace);
  activatePanning(workspace);
}


//////////////////////////////////////////////////////////////////////////////
/// A U X   F U N C T I O N S ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void drawWorkspaceComponent(Electron workspace, Component component)
{
  component.x = workspace.panningX + component.x * workspace.zoom;
  component.y = workspace.panningY + component.y * workspace.zoom;
  component.size = 15*workspace.zoom;
  drawComponent(component);
}

//////////////////////////////////////////////////////////////////////////////
/// M I S C //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// Immediately displays a red message on the bottom of the screen
void message(const char* text)
{
  // // message box
  // setcolor (WHITE);
  // setfillstyle (SOLID_FILL, getcolor ());
  // bar(WIDTH/2-350, HEIGHT-50, WIDTH/2+350, HEIGHT-10);

  // message text
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
  settextjustify (CENTER_TEXT, CENTER_TEXT);
  setcolor (RED);
  outtextxy (WIDTH / 2, HEIGHT - 30,(char*)text);
}

// Checks if the mouse is on a box
bool isMouseOnBox(int x1, int y1, int x2, int y2)
{
  if (mousex() > x1 && mousex() < x2)
    if (mousey() > y1 && mousey() < y2)
      {
        return YEAH;
      }
  return NOPE;
}