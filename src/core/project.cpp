#include "project.h"
#include "files.h"
#include <ctime>
#include "components.h"
#include "../gui/button.h"
#include "../gui/menu.h"
#include "../gui/boxes.h"
#include "../interactive/interactive.h"
#include "workspace.h"
#include "files.h"


//////////////////////////////////////////////////////////////////////////////
/// P R O G R A M   V A R I A B L E S ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

bool titleIsRunning = YEAH;


//////////////////////////////////////////////////////////////////////////////
/// I N I T   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// Initialises SDL_bgi graphics and window
void initSdlbgi()
{
  // windowed full screen size
  setwinoptions ((char *)"E L E C T R O N", 0, 0, SDL_WINDOW_FULLSCREEN);
  initwindow (WIDTH, HEIGHT); 
  // so it runs faster, but we need to put refresh() to draw graphics
  sdlbgifast();
  setbkrgbcolor (WORKSPACE);
}

// initialises the current workspace
void initElectron(Electron& workspace)
{
  // COMPONENTS
  workspace.nrOfComponents = 0;
  workspace.nrOfWires = 0;
  strcpy(workspace.currentFile, "test");
  loadFile(workspace, 1);
  // MENU
  initMenu(workspace.menu);
  initMenuBar(workspace.menuBar);
  // SCREEN
  workspace.panningX = 0;
  workspace.panningY = 0;
  workspace.zoom = 1;
  
  loadTheme(1);
  workspace.secrets = NOPE;
}


//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int scree[240][135];
// aux
void initAnimationPalette();
void activateTitleScreen(Button buttonStart, Button buttonCredits, bool& isRunning);
// TODO: make struct for animation, shit has too many variables,,,
void continueAnimation(int& i, int& px, int& py, int& dx, int& dy, float& diam, int scree[240][135], 
                       int& iterations, Button buttonStart, Button buttonCredits);
// Starts title screen
void titleScreen(bool& isRunning)
{
  // Initialization
  Button buttonStart;
  Button buttonCredits;
  createButton(buttonStart, WIDTH/2, HEIGHT/2, "Start", 9, &bVoid);
  createButton(buttonCredits, WIDTH/2, HEIGHT-200, "Credits", 7, &bCredits);

  // ANIMATION
  cleardevice();
  // number of particles
  int nrOfParticles = 10000;
  // screen

  // particle values
  int px;
  int py;
  // offsets
  int dx;
  int dy;
  float diam = 20;
  int iterations = 0;

  initAnimationPalette();

  // setting seed so every time it's random
  std::srand(time(NULL));
  // planting a single seed in the middle of the screen
  scree[120][65] = 1;

  int i = 0;

  // Run loop
  while(titleIsRunning)
  {
    // continue the animation if it isn't finished
    if (i < nrOfParticles)
    {
      continueAnimation(i, px, py, dx, dy, diam, scree, iterations, buttonStart, buttonCredits);
    }
    activateTitleScreen(buttonStart, buttonCredits, isRunning);

  }
  // type and pray strategy employed
  setalpha(BLACK, 255);
}


// draws the current workspace
void draw(Electron& workspace)
{
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    drawWorkspaceComponent(workspace, workspace.components[i]);
  }
   for (int i = 0; i < workspace.nrOfWires; i++)
    drawWirePoints(workspace, workspace.wires[i]);
  
  
  drawWires(workspace);
  drawMenu(workspace.menu);
  drawMenuBar(workspace.menuBar);
  drawStatusBar(workspace);

  //
  message("=== Esc button to exit ===");
}

// updates the current workspace
void logic(Electron& workspace)
{
  strcpy(workspace.currentMessage, "");
  activateMenuBarElement(workspace, workspace.menuBar);
  activateMenuBar(workspace);
  activateScrollMenu(workspace);
  activateMenuComponents(workspace);
  activateZooming(workspace);
  activatePanning(workspace);
  activateWires(workspace);
  if (activeWire(workspace) != -1)
    strcpy(workspace.currentMessage, "wire");
  activateComponents(workspace);

  //EASTER EGG
  if (isMouseOnBox(WIDTH-30, 0, WIDTH, 36) && ismouseclick(WM_LBUTTONDOWN))
  {
    
    if (workspace.secrets == NOPE)
    {      
      loadTheme(0);
      workspace.secrets = YEAH;
      delay(100);
    }
    else
    {
      loadTheme(6);
      workspace.secrets = NOPE;
      delay(100);
    }
  }

}



//////////////////////////////////////////////////////////////////////////////
/// A N I M A T I O N ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// aux aux,,,
void placePoint(int& px, int& py, int& dx, int& dy, float& diam, int scree[240][135], int& iterations);
void drawAnimation(int px, int py, int dx, int dy, float& diam, int iterations);
void drawTitleButtons(Button buttonStart, Button buttonCredits);
// self explanatory
void continueAnimation(int& i, int& px, int& py, int& dx, int& dy, float& diam, int scree[240][135], int& iterations, Button buttonStart, Button buttonCredits)
{
  placePoint(px, py, dx, dy, diam, scree, iterations);
  drawAnimation(px, py, dx, dy, diam, iterations);

  // once every 8 drawings so the pc doesn't explode
  if (i%8 == 0)
  {
    drawTitleButtons(buttonStart, buttonCredits);
    refresh();
  }
  i++;
}

// does what it says it does
void activateTitleScreen(Button buttonStart, Button buttonCredits, bool& isRunning)
{
  // so that lastkey() will work
  xkbhit ();

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

// for the titleScreen animation
void initAnimationPalette()
{
  // set up a palette
  int x;
  // initialise it to black
  for (x = 0; x < getrgbpalettesize (); x++)
    setrgbpalette (x, 0, 0, 0);
  
  // blue fading to red
  for (x = 0; x < 128; x++)
    setrgbpalette (x, 2*x, 0, 255-2*x);

  // red fading to blue
  for (x = 128; x < 256; x++)
    setrgbpalette (x, 255-(2*(x-128)), 0, 2*(x-128));
  
  // yellow fading to cyan
  for (x = 256; x < 512; x++)
    setrgbpalette (x, (x-256), 0, 255-(x-256));
  
  // red fading to black
  for (x = 512; x < 1024; x += 2)
    setrgbpalette (x, 1024 - 2*x, 0, 0);
}

// draws the point added by placePoint()
void drawAnimation(int px, int py, int dx, int dy, float& diam, int iterations)
{
  // DRAWING
  if (diam < 140)
    diam += 0.02;
  int color = iterations/30;
  if (color > 1024)
    color = 1024;
  setrgbcolor(color);

  // 1920x1080p FULL HD resolution
  if (WIDTH == 1920)
  {
  _putpixel((px-dx)*8,   (py-dy)*8);
  _putpixel((px-dx)*8+1, (py-dy)*8);
  _putpixel((px-dx)*8,   (py-dy)*8+1);
  _putpixel((px-dx)*8+1, (py-dy)*8+1);
  //outer
  _putpixel((px-dx)*8+2, (py-dy)*8);
  _putpixel((px-dx)*8+2, (py-dy)*8+1);
  _putpixel((px-dx)*8+2, (py-dy)*8+2);
  _putpixel((px-dx)*8+1, (py-dy)*8+2);
  _putpixel((px-dx)*8,   (py-dy)*8+2);
  // outerouter
  _putpixel((px-dx)*8+2, (py-dy)*8);
  _putpixel((px-dx)*8+2, (py-dy)*8+1);
  _putpixel((px-dx)*8+2, (py-dy)*8+2);
  _putpixel((px-dx)*8+1, (py-dy)*8+2);
  _putpixel((px-dx)*8,   (py-dy)*8+2);
  }
  // 1366x768 HD resolution??
  else
  {
  _putpixel((px-dx)*6,   (py-dy)*6);
  _putpixel((px-dx)*6+1, (py-dy)*6);
  _putpixel((px-dx)*6,   (py-dy)*6+1);
  _putpixel((px-dx)*6+1, (py-dy)*6+1);
  //outer
  _putpixel((px-dx)*6+2, (py-dy)*6);
  _putpixel((px-dx)*6+2, (py-dy)*6+1);
  _putpixel((px-dx)*6+2, (py-dy)*6+2);
  _putpixel((px-dx)*6+1, (py-dy)*6+2);
  _putpixel((px-dx)*6,   (py-dy)*6+2);
  }
}

// doesn't need a comment
void drawTitleButtons(Button buttonStart, Button buttonCredits)
{
  message("=== Esc button to exit ===");
  drawButton(buttonStart);
  drawButton(buttonCredits);


  setcolor(BLACK);
  setalpha (BLACK, 1); // has weird behaviour,,,
  setfillstyle (SOLID_FILL, getcolor ());
  bar(
      WIDTH/2 - WIDTH/6, HEIGHT/4 - 5*9, 
      WIDTH/2 + WIDTH/6, HEIGHT/4 + 8*9
    );
  // label
  settextstyle  (GOTHIC_FONT, HORIZ_DIR, 9);
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  setcolor      (WHITE);
  outtextxy(WIDTH/2, HEIGHT/4, (char*)"ELECTRON");
  outtextxy(WIDTH/2+1, HEIGHT/4, (char*)"ELECTRON");
}

// Places a point on screen for the brownian tree animation
void placePoint(int& px, int& py, int& dx, int& dy, float& diam, int scree[240][135], int& iterations)
{
  // set the particle's initial position
  px = 120 + std::rand() % ((int)diam + 50) - diam/2- 25;
  py = 65  + std::rand() % (int)diam        - diam/2;

  // if we landed on an existing point
  while(scree[px][py] == 1 
  // for optimization
    || (px  > 120-diam/4 && px < 120+diam/4 && py > 65-diam/4 && py < 65+diam/4))
  {
    // try another random position
    px = 120 + std::rand() % ((int)diam + 50)- diam/2 - 25;
    py = 65 + std::rand() % (int)diam - diam/2;
  }

  // put it in a valid random location
  while (1)
  {
    // random direction
    dx = std::rand() % 3 - 1;
    dy = std::rand() % 3 - 1;

    // check that it doesn't go out of bounds
    while (dx + px < 0 || dx + px >= 240 || dy + py < 0 || dy + py >= 135 || scree[px][py] == 1)
    {
      // try another random location
      px = std::rand() % 240;
      py = std::rand() % 135;
    }

    // for the else
    if (dx + px < 0 || dx + px >= 240 || dy + py < 0 || dy + py >= 135 || scree[px][py] == 1);
    else if (scree[px + dx][py + dy] != 0)
    {
      // bumped into a point
      scree[px][py] = 1;
      iterations++;
      // exit the loop after point was placed
      break;
    } else
    {
      // if not, keep walking
      py += dy;
      px += dx;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
/// M I S C //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void drawStatusBar(Electron workspace)
{
  char text[1000];
  setrgbcolor(STATUS_BAR);
  setfillstyle(SOLID_FILL, getcolor());
  bar(0, HEIGHT-24, WIDTH, HEIGHT);
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
  settextjustify (LEFT_TEXT, TOP_TEXT);
  strcat(text, workspace.currentFile);
  strcat(text, " > ");
  strcat(text, workspace.currentMessage);
  setrgbcolor(STATUS_BAR_TEXT);
  outtextxy(5, HEIGHT-15, text);
}


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
  setrgbcolor(MESSAGE);
  outtextxy (WIDTH / 2, HEIGHT - 33,(char*)text);
}



