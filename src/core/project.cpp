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
  workspace.input = NOPE;
  workspace.tutor = YEAH;
}


//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int scree[240][135];
// aux
void initAnimationPalette();
void activateTitleScreen(Button buttonStart, bool& isRunning);
// TODO: make struct for animation, shit has too many variables,,,
void continueAnimation(int& i, int& px, int& py, int& dx, int& dy, float& diam, int scree[240][135], 
                       int& iterations, Button buttonStart);
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
      continueAnimation(i, px, py, dx, dy, diam, scree, iterations, buttonStart);
    }
    activateTitleScreen(buttonStart, isRunning);

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
  drawTutor(workspace);
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
void drawTitleButtons(Button buttonStart);
// self explanatory
void continueAnimation(int& i, int& px, int& py, int& dx, int& dy, float& diam, int scree[240][135], int& iterations, Button buttonStart)
{
  placePoint(px, py, dx, dy, diam, scree, iterations);
  drawAnimation(px, py, dx, dy, diam, iterations);

  // once every 8 drawings so the pc doesn't explode
  if (i%8 == 0)
  {
    drawTitleButtons(buttonStart);
    refresh();
  }
  i++;
}

// does what it says it does
void activateTitleScreen(Button buttonStart, bool& isRunning)
{
  // so that lastkey() will work
  xkbhit ();

  // can't use activateButton here because it's the only one that needs an argument
  // start main program
  if (ismouseclick(WM_LBUTTONDOWN) && IsMouseOnButton(buttonStart))
    titleIsRunning = NOPE;

  // show credits
  //activateButton(buttonCredits);
  
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
void drawTitleButtons(Button buttonStart)
{
  message("=== Esc button to exit ===");
  drawButton(buttonStart);
  //drawButton(buttonCredits);


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


void drawTutor(Electron workspace)
{
  if (!workspace.tutor)
  return;
  int i;
  bigBox(WIDTH-250, 36, 250, 150, 1);
  setrgbcolor(MENU_TEXT);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
  settextjustify(LEFT_TEXT, TOP_TEXT);
  if (workspace.input)
  {
    outtextxy(WIDTH-230, 36 + 20, (char*)"INPUT");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(WIDTH-230, 36 + 50, (char*)"Type and press ENTER.");
    outtextxy(WIDTH-230, 36 + 70, (char*)"Or just ENTER to cancel.");
  }
  else if ( (i = activeComponent(workspace)) != -1)
  {
    outtextxy(WIDTH-230, 36 + 20, workspace.components[i].name);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(WIDTH-230, 36 + 50, (char*)"Click and drag to move.");
    outtextxy(WIDTH-230, 36 + 70, (char*)"Right click to rotate.");
    outtextxy(WIDTH-230, 36 + 90, (char*)"Click on bond point to-");
    outtextxy(WIDTH-230, 36 + 100, (char*)"start creating a wire.");
  }
  else if ( (i = activeWire(workspace)) != -1)
  {
    outtextxy(WIDTH-230, 36 + 20, (char*)"WIRE");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(WIDTH-230, 36 + 50, (char*)"Click to reverse.");
    outtextxy(WIDTH-230, 36 + 70, (char*)"Right click to remove.");
  }
  else
  {
    outtextxy(WIDTH-230, 36 + 20, (char*)"WORKSPACE");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(WIDTH-230, 36 + 50, (char*)"Middle click to pan.");
    outtextxy(WIDTH-230, 36 + 70, (char*)"Middle and Right click to-");
    outtextxy(WIDTH-230, 36 + 80, (char*)"zoom by dragging mouse-");
    outtextxy(WIDTH-230, 36 + 90, (char*)"along the X axis.");
  }
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

void showHelp()
{
  bigBox(WIDTH/2 - 200, HEIGHT/2 - 75, 400, 170, 1);
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
  settextjustify (CENTER_TEXT, TOP_TEXT);
  setrgbcolor(MENU_TEXT);
  outtextxy(WIDTH/2, HEIGHT/2 - 50, (char*)"HELP");
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
  settextjustify (LEFT_TEXT, TOP_TEXT);
  outtextxy(WIDTH/2 - 170, HEIGHT/2 -20, (char*)"== Electron ==");
  outtextxy(WIDTH/2 - 170, HEIGHT/2,    (char*)"This program is an electronic circuit-");
  outtextxy(WIDTH/2 - 170, HEIGHT/2+10, (char*)"viewer and editor.");
  outtextxy(WIDTH/2 - 170, HEIGHT/2+20, (char*)"Drag and drop components from the menu.");
  outtextxy(WIDTH/2 - 170, HEIGHT/2+30, (char*)"For more instructions, make sure Tutor-");
  outtextxy(WIDTH/2 - 170, HEIGHT/2+40, (char*)"mode is on.");
  settextjustify (CENTER_TEXT, TOP_TEXT);
  outtextxy(WIDTH/2, HEIGHT/2+70, (char*)"PRESS ANY KEY TO CONTINUE");
  refresh();
  getch();
}

void showCredits()
{
  bigBox(WIDTH/2 - 200, HEIGHT/2 - 75, 400, 170, 1);
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
  settextjustify (CENTER_TEXT, TOP_TEXT);
  setrgbcolor(MENU_TEXT);
  outtextxy(WIDTH/2, HEIGHT/2 - 50, (char*)"CREDITS");
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
  settextjustify (LEFT_TEXT, TOP_TEXT);
  outtextxy(WIDTH/2 - 170, HEIGHT/2 -20, (char*)"== Electron ==");
  outtextxy(WIDTH/2 - 170, HEIGHT/2, (char*)"Project realized by:");
  outtextxy(WIDTH/2 - 170, HEIGHT/2+10, (char*)" Ciobanu Andra and Petcu Andreea;");
  outtextxy(WIDTH/2 - 170, HEIGHT/2+20, (char*)"2022.11.22 - 2023.01.09;");
  outtextxy(WIDTH/2 - 170, HEIGHT/2+30, (char*)"UAIC Year 1, Semester 1;");
  outtextxy(WIDTH/2 - 170, HEIGHT/2+40, (char*)"Coordinating teacher: Bogdan Patrut;");
  settextjustify (CENTER_TEXT, TOP_TEXT);
  outtextxy(WIDTH/2, HEIGHT/2+70, (char*)"PRESS ANY KEY TO CONTINUE");
  refresh();
  getch();
}

  //             "Project realised by Ciobanu Andra and Petcu Andreea;\n"
  //             "2022.11.22 -                                        \n" 
  //             "UAIC Year 1 Semester 1;                             \n"
  //             "Coordinating teacher: Bogdan Patrut."