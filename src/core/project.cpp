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
void initElectron(Electron& workspace)
{
  // COMPONENTS
  workspace.nrOfComponents = 0;
  strcpy(workspace.currentFile, "test");
  loadFile(workspace.currentFile, workspace);
  // MENU
  initMenu(workspace.menu);
  strcpy(workspace.menuBarButtons[0].text, "File");
  workspace.menuBarButtons[0].x = 0;
  workspace.menuBarButtons[0].y = 0;
  workspace.menuBarButtons[0].w = 50;
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
    cleardevice();
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
    cleardevice();
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
    cleardevice();
    draw(workspace);
    refresh();
  }
  while (!workspace.menu.show && isMouseOnBox(workspace.menu.buttonWidth, 24, WIDTH, HEIGHT) && ismouseclick(WM_MBUTTONDOWN)  && !ismouseclick(WM_RBUTTONDOWN))
  {

    workspace.panningX = panPrevX + mousex() - x;
    workspace.panningY = panPrevY + mousey() - y;
    cleardevice();
    draw(workspace);
    refresh();
  }
}

bool isMouseOnWorkspace(Electron workspace)
{
  if (workspace.menu.show)
  {
    if (isMouseOnBox(workspace.menu.width, 0, WIDTH, HEIGHT))
      return YEAH;
    return NOPE;
  }
  else
  {
    if (isMouseOnBox(workspace.menu.buttonWidth, 0, WIDTH, HEIGHT))
      return YEAH;
    return NOPE;
  }
}

void moveComponents(Electron& workspace)
{
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    while (isMouseOnWorkspace(workspace) && isMouseOnComponent(workspace, workspace.components[i].x-100, workspace.components[i].y-100, workspace.components[i].x+100, workspace.components[i].y+100) 
           && ismouseclick(WM_LBUTTONDOWN))
    { 
      workspace.components[i].x = (mousex() - workspace.panningX)/workspace.zoom;
      workspace.components[i].y = (mousey() - workspace.panningY)/workspace.zoom;
      cleardevice();
      draw(workspace);
      setcolor(RED);
      //workspace.panningX + component.x * workspace.zoom
      rectangle(          
        workspace.components[i].x*workspace.zoom-75*workspace.zoom + workspace.panningX, 
        workspace.components[i].y*workspace.zoom-75*workspace.zoom + workspace.panningY,
        workspace.components[i].x*workspace.zoom+75*workspace.zoom + workspace.panningX, 
        workspace.components[i].y*workspace.zoom+75*workspace.zoom + workspace.panningY);
      refresh();
    }
  }
}

void drawWorkspaceComponent(Electron workspace, Component component);
// draws the current workspace
void draw(Electron workspace)
{
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {

    drawWorkspaceComponent(workspace, workspace.components[i]);
  }
  drawMenu(workspace.menu);
  drawStatusBar(workspace);
  drawMenuBar();
  //
  bigBox(workspace.menuBarButtons[0].x, 0, workspace.menuBarButtons[0].w, 36, 1);
  setcolor(WHITE);
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
  settextjustify (CENTER_TEXT, CENTER_TEXT);
  outtextxy(workspace.menuBarButtons[0].x + workspace.menuBarButtons[0].w/2, 18, workspace.menuBarButtons[0].text);

  // TUX PLZ PUT THIS ON A BUTTON THX 
  bigBox(WIDTH-30, 0, 30, 36, 1);

  //
  message("=== Esc button to exit ===");
}

// Allows for drag and drop
void activateMenuComponents(Electron& workspace)
{
  // if the menu is hidden, this doesn't need to run
  if (!workspace.menu.show)
    return;
  
  int c = workspace.menu.scroll;
  for (int i = 0; i < 12; i++)
  {
    // if the column is a category name, skip it
    if (workspace.menu.columns[i].content[0] == 'A')
      i++;
    
    // ONE COMPONENT
    // menu.components[(int)menu.columns[c+i].content[1]-'0']
    if (isMouseOnBox(2, 38 + workspace.menu.elementHeigth * i, workspace.menu.width/2 - workspace.menu.buttonWidth -2, 36 + workspace.menu.elementHeigth * (i + 1) - 2) && ismouseclick(WM_LBUTTONDOWN))
    {
      // daca nu e asta aici o sa dea eroare drawComponent
      // nu intreba dc
      delay(100);
      // CREATING NEW COMPONENT
      workspace.nrOfComponents++;
      initComponent(workspace.components[workspace.nrOfComponents-1], workspace.menu.components[(int)workspace.menu.columns[c+i].content[1]-'0'].name);
      /// DRAG
      while (ismouseclick(WM_LBUTTONDOWN))
      {
        setcolor(RED);
        
        moveComponent(workspace.components[workspace.nrOfComponents-1], (mousex() - workspace.panningX)/workspace.zoom, (mousey() - workspace.panningY)/workspace.zoom);
        cleardevice();
        draw(workspace);
        drawWorkspaceComponent(workspace, workspace.components[workspace.nrOfComponents-1]);
        rectangle (2, 38 + workspace.menu.elementHeigth * i, workspace.menu.width/2 - workspace.menu.buttonWidth -2, 36 + workspace.menu.elementHeigth * (i + 1) - 2);
        refresh();
      }
      /// DROP
      moveComponent(workspace.components[workspace.nrOfComponents-1], (mousex() - workspace.panningX)/workspace.zoom, (mousey() - workspace.panningY)/workspace.zoom);
    }

    // TWO COMPONENTS
    if (workspace.menu.columns[c+i].content[2])
    {
      if (isMouseOnBox(2 + workspace.menu.width/2 - workspace.menu.buttonWidth, 38 + workspace.menu.elementHeigth * i, workspace.menu.width - workspace.menu.buttonWidth - 2, 36 + workspace.menu.elementHeigth * (i + 1) - 2) && ismouseclick(WM_LBUTTONDOWN))
      {
        // daca nu e asta aici o sa dea eroare drawComponent
        // nu intreba dc
        delay(100);
        // CREATING NEW COMPONENT
        workspace.nrOfComponents++;
        initComponent(workspace.components[workspace.nrOfComponents-1], workspace.menu.components[(int)workspace.menu.columns[c+i].content[2]-'0'].name);
        /// DRAG
        while (ismouseclick(WM_LBUTTONDOWN))
        {
          setcolor(RED);
          
          moveComponent(workspace.components[workspace.nrOfComponents-1], (mousex() - workspace.panningX)/workspace.zoom, (mousey() - workspace.panningY)/workspace.zoom);
          cleardevice();
          draw(workspace);
          drawWorkspaceComponent(workspace, workspace.components[workspace.nrOfComponents-1]);
          rectangle (2 + workspace.menu.width/2 - workspace.menu.buttonWidth, 38 + workspace.menu.elementHeigth * i, workspace.menu.width - workspace.menu.buttonWidth - 2, 36 + workspace.menu.elementHeigth * (i + 1) - 2);
          refresh();
        }
        /// DROP
        moveComponent(workspace.components[workspace.nrOfComponents-1], (mousex() - workspace.panningX)/workspace.zoom, (mousey() - workspace.panningY)/workspace.zoom);
      }
    }
  }
}

// updates the current workspace
void logic(Electron& workspace, bool& isRunning)
{
  kbhit();
  if (lastkey() == KEY_ESC)
    isRunning = NOPE;
  
  activateScrollMenu(workspace.menu);
  activateMenuComponents(workspace);
  activateZooming(workspace);
  activatePanning(workspace);
  moveComponents(workspace);
  if (isMouseOnBox(WIDTH-30, 0, WIDTH, 36) && ismouseclick(WM_LBUTTONDOWN))
  {
    system("supertuxkart");
    //system("xdotool key alt+Tab");
  }
  if (SDL_GetWindowFlags(bgi_window) & SDL_WINDOW_HIDDEN)
  {
    system("echo sdfsdf && xdotool keydown 0xffea + key 0xff09");
    delay(2000);
    system("xdotool keyup 0xffea");
  }
}

void drawStatusBar(Electron workspace)
{
  setfillstyle(SOLID_FILL, BLUE);
  bar(0, HEIGHT-24, WIDTH, HEIGHT);
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
  settextjustify (LEFT_TEXT, TOP_TEXT);
  outtextxy(5, HEIGHT-15, workspace.currentFile);
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
  outtextxy (WIDTH / 2, HEIGHT - 33,(char*)text);
}

bool isMouseOnComponent(Electron workspace, int x1, int y1, int x2, int y2)
{
  if ((mousex() - workspace.panningX)/workspace.zoom > x1 && (mousex() - workspace.panningX)/workspace.zoom < x2)
    if ((mousey() - workspace.panningY)/workspace.zoom > y1 && (mousey() - workspace.panningY)/workspace.zoom < y2)
      {
        return YEAH;
      }
  return NOPE;
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




/* 

*/