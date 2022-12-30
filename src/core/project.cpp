#include "project.h"
#include "files.h"
#include <ctime>
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


int scree[240][135];

// Starts title screen
void titleScreen(bool& isRunning)
{
  // Initialization
  Button buttonStart;
  Button buttonCredits;
  createButton(buttonStart, WIDTH/2, HEIGHT/2, "Start", 9, &bVoid);
  createButton(buttonCredits, WIDTH/2, HEIGHT-300, "Credits", 7, &bCredits);

  refresh();


  // ANIMATION
     cleardevice();
    // number of particles
    int nrOfParticles = 32000;
    // screen

    // particle values
    int px;
    int py;
    // offsets
    int dx;
    int dy;

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

  int iterations = 0;
    // int color;


  std::srand(time(NULL));

  scree[120][65] = 1;
  int i = 0;
  float diam = 20;
  // Run loop
  while(titleIsRunning)
  {


   

    if (i < nrOfParticles)
    {
      // set the particle's initial position
        px = 120 + std::rand() % ((int)diam + 50) - diam/2- 25;
        py = 65 + std::rand() % (int)diam - diam/2;

      // avoid center

      // while (px  > 240-diam/4 && px < 240+diam/4 && py > 135-diam/4 && py < 135+diam/4)
      // {

      // }
      while(scree[px][py] == 1 || (px  > 120-diam/4 && px < 120+diam/4 && py > 65-diam/4 && py < 65+diam/4))
      {
        px = 120 + std::rand() % ((int)diam + 50)- diam/2 - 25;
        py = 65 + std::rand() % (int)diam - diam/2;
      }
      while (1)
      {
          // random direction
          dx = std::rand() % 3 - 1;
          dy = std::rand() % 3 - 1;

          while (dx + px < 0 || dx + px >= 240 || dy + py < 0 || dy + py >= 135 || scree[px][py] == 1)
          {
              // put it in a random location
              px = std::rand() % 240;
              py = std::rand() % 135;
          }
          if (dx + px < 0 || dx + px >= 240 || dy + py < 0 || dy + py >= 135|| scree[px][py] == 1);
          else if (scree[px + dx][py + dy] != 0)
          {
              // bumped into something
              scree[px][py] = 1;
              iterations++;
              break;
          } else
          {
              py += dy;
              px += dx;
          }
      }
      // DRAWING
      if (diam < 140)
       diam+= 0.02;
      int color = iterations/30;
      if (color > 1024)
        color = 1024;
            setcolor(RED);
      //circle(WIDTH/2, HEIGHT/2, diam*4);
      setrgbcolor(color);
      //setcolor(WHITE);
      _putpixel((px-dx)*8,(py-dy)*8);
      _putpixel((px-dx)*8+1,(py-dy)*8);
      _putpixel((px-dx)*8,(py-dy)*8+1);
      _putpixel((px-dx)*8+1,(py-dy)*8+1);
      //outer
      _putpixel((px-dx)*8+2,(py-dy)*8);
      _putpixel((px-dx)*8+2,(py-dy)*8+1);
      _putpixel((px-dx)*8+2,(py-dy)*8+2);
      _putpixel((px-dx)*8+1,(py-dy)*8+2);
      _putpixel((px-dx)*8,(py-dy)*8+2);
      // outerouter
      _putpixel((px-dx)*8+2,(py-dy)*8);
      _putpixel((px-dx)*8+2,(py-dy)*8+1);
      _putpixel((px-dx)*8+2,(py-dy)*8+2);
      _putpixel((px-dx)*8+1,(py-dy)*8+2);
      _putpixel((px-dx)*8,(py-dy)*8+2);

      if (i%8 == 0)
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
        refresh();
      }
        
      i++;
    }

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
  setalpha(BLACK, 255);
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
  loadFile(workspace, 1);
  // MENU
  initMenu(workspace.menu);
  initMenuBar(workspace.menuBar);
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

void activateComponents(Electron& workspace)
{
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    if (isMouseOnComponent(workspace, workspace.components[i].x-100, workspace.components[i].y-100, workspace.components[i].x+100, workspace.components[i].y+100))
    {
      strcpy(workspace.currentMessage, workspace.components[i].name);
    }
  }
  moveComponents(workspace);
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
  drawMenuBar(workspace.menuBar);

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
    if (isMouseOnBox(2, 38 + workspace.menu.elementHeigth * i, workspace.menu.width/2 - workspace.menu.buttonWidth -2, 36 + workspace.menu.elementHeigth * (i + 1) - 2))
      strcpy(workspace.currentMessage, workspace.menu.components[(int)workspace.menu.columns[c+i].content[1]-'0'].name);
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
      if (isMouseOnBox(2 + workspace.menu.width/2 - workspace.menu.buttonWidth, 38 + workspace.menu.elementHeigth * i, workspace.menu.width - workspace.menu.buttonWidth - 2, 36 + workspace.menu.elementHeigth * (i + 1) - 2))
        strcpy(workspace.currentMessage, workspace.menu.components[(int)workspace.menu.columns[c+i].content[2]-'0'].name);
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
// Updates menu
void activateScrollMenu(Electron& workspace)
{
  //rectangle(menu.width - menu.buttonWidth, 0, menu.width, HEIGHT);
  if (workspace.menu.show && ismouseclick(WM_LBUTTONDOWN)&& isMouseOnBox(workspace.menu.width - workspace.menu.buttonWidth, 36, workspace.menu.width, 36 + workspace.menu.height/2-20) && workspace.menu.scroll > 0)
  {
    workspace.menu.scroll--;
    delay(100);
  }
  if (workspace.menu.show && isMouseOnBox(workspace.menu.width - workspace.menu.buttonWidth, 36, workspace.menu.width, 36 + workspace.menu.height/2-20))
  {
    strcpy(workspace.currentMessage, "scroll up");
  }
  if (workspace.menu.show && ismouseclick(WM_LBUTTONDOWN) && isMouseOnBox(workspace.menu.width - workspace.menu.buttonWidth, 36 + workspace.menu.height/2+20, workspace.menu.width, 36 + workspace.menu.height) && workspace.menu.scroll < workspace.menu.nrOfColumns-12)
  {
    workspace.menu.scroll++;
    delay(100);
  }
  if (workspace.menu.show && isMouseOnBox(workspace.menu.width - workspace.menu.buttonWidth, 36 + workspace.menu.height/2+20, workspace.menu.width, 36 + workspace.menu.height))
  {
    strcpy(workspace.currentMessage, "scroll down");
  }
  if (workspace.menu.show && ismouseclick(WM_LBUTTONDOWN) && isMouseOnBox(workspace.menu.width - workspace.menu.buttonWidth, 36 + workspace.menu.height/2-20, workspace.menu.width, 36 + workspace.menu.height/2+20))
  {
    workspace.menu.show = false;
    delay(100);
  }
  if (!workspace.menu.show && ismouseclick(WM_LBUTTONDOWN) && isMouseOnBox(0, 36, workspace.menu.buttonWidth, 36 + workspace.menu.height))
  {
    workspace.menu.show = true;
    delay(100);
  }
}
// updates the current workspace
void logic(Electron& workspace, bool& isRunning)
{

  k_bhit();
  if (lastkey() == KEY_ESC)
    isRunning = NOPE;
  activateMenuBarElement(workspace, workspace.menuBar);
  activateMenuBar(workspace);
  activateScrollMenu(workspace);
  activateMenuComponents(workspace);
  activateZooming(workspace);
  activatePanning(workspace);
  activateComponents(workspace);


  // EASTER EGG
  // if (isMouseOnBox(WIDTH-30, 0, WIDTH, 36) && ismouseclick(WM_LBUTTONDOWN))
  // {
  //   system("supertuxkart");
  //   //system("xdotool key alt+Tab");
  // }
  // if (SDL_GetWindowFlags(bgi_window) & SDL_WINDOW_HIDDEN)
  // {
  //   system("echo sdfsdf && xdotool keydown 0xffea + key 0xff09");
  //   delay(2000);
  //   system("xdotool keyup 0xffea");
  // }

}

void drawStatusBar(Electron workspace)
{
  char text[1000];
  setfillstyle(SOLID_FILL, BLUE);
  bar(0, HEIGHT-24, WIDTH, HEIGHT);
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
  settextjustify (LEFT_TEXT, TOP_TEXT);
  strcat(text, workspace.currentFile);
  strcat(text, " > ");
  strcat(text, workspace.currentMessage);
  outtextxy(5, HEIGHT-15, text);
}

//////////////////////////////////////////////////////////////////////////////
/// A U X   F U N C T I O N S ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


void activateMenuBarElement(Electron& workspace, MenuBar menuBar)
{
  
  for (int i = 0; i < menuBar.nrOfElements; i++)
  {
    if (menuBar.menuBarElement[i].open)
    {
      activateMenuBarOption(workspace, i);
    }
  }
}

void drawMenuBarOptions(MenuBarElement menuBarElement)
{
  for (int i = 0; i < menuBarElement.nrOfOptions; i++)
  {
    setcolor(COLOR(255,255,255));
    setfillstyle(SOLID_FILL, getcolor());
    bar(menuBarElement.x, 36 + 30*i, menuBarElement.x + menuBarElement.optionsWidth, 36 + 30*(i+1));
    setcolor(COLOR(0,0,0));
    rectangle(menuBarElement.x, 36 + 30*i, menuBarElement.x + menuBarElement.optionsWidth, 36 + 30*(i+1));
    settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
    settextjustify (LEFT_TEXT, CENTER_TEXT);
    outtextxy(menuBarElement.x + 10, 36+ 15 +30*i, menuBarElement.options[i].name);
  }
}


void activateMenuBar(Electron& workspace)
{
  for (int i = 0; i < workspace.menuBar.nrOfElements; i++)
  {  
    while (workspace.menuBar.menuBarElement[i].open && ismouseclick(WM_LBUTTONDOWN)) // if we click somewhere else
    {
      while (ismouseclick(WM_LBUTTONDOWN));
      workspace.menuBar.menuBarElement[i].open = NOPE;
      workspace.menuBar.open = -1;
    }
    if (workspace.menuBar.open == -1 && isMouseOnBox(workspace.menuBar.menuBarElement[i].x, 0, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].w, 36)
        && ismouseclick(WM_LBUTTONDOWN))
    {
      while (ismouseclick(WM_LBUTTONDOWN));
      workspace.menuBar.menuBarElement[i].open = YEAH;
      workspace.menuBar.open = i;
    }
    if (workspace.menuBar.open != -1 && !workspace.menuBar.menuBarElement[i].open && isMouseOnBox(workspace.menuBar.menuBarElement[i].x, 0, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].w, 36))
    {
      workspace.menuBar.menuBarElement[workspace.menuBar.open].open = NOPE;
      workspace.menuBar.menuBarElement[i].open = YEAH;
      workspace.menuBar.open = i;
    }
    if (ismouseclick(WM_MBUTTONDOWN) && isMouseOnBox(workspace.menuBar.menuBarElement[i].x, 0, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].w, 36)) //easter egg
    {
      int maxx = WIDTH;
      int minx = 0;
      // calculate the max x position
      for (int z = i; z < workspace.menuBar.nrOfElements; z++)
        maxx -= workspace.menuBar.menuBarElement[z].w;
      for (int z = 0; z < i; z++)
        minx += workspace.menuBar.menuBarElement[z].w;
      while (ismouseclick(WM_MBUTTONDOWN))
      {
        int m = mousex();
        if (m <= maxx && m >= minx) 
          workspace.menuBar.menuBarElement[i].x = m;
        else if (m > maxx)
          m = maxx;
        else if (m < minx)
          m = minx;
        // to the right
        
        for (int j = i; j < workspace.menuBar.nrOfElements-1; j++)
        {
          while (workspace.menuBar.menuBarElement[j].x + workspace.menuBar.menuBarElement[j].w >= workspace.menuBar.menuBarElement[j+1].x)
          {
            workspace.menuBar.menuBarElement[j+1].x++;
          }
        }
        for (int j = 1; j <= i; j++)
        {
          while (workspace.menuBar.menuBarElement[j].x <= workspace.menuBar.menuBarElement[j-1].x + workspace.menuBar.menuBarElement[j-1].w)
          {
            workspace.menuBar.menuBarElement[j-1].x--;
          }
        }
        
        
          
        cleardevice();
        draw(workspace);
        refresh();
      }
    }
  }
}

void activateMenuBarOption(Electron& workspace, int i)
{
  for (int j = 0; j < workspace.menuBar.menuBarElement[i].nrOfOptions; j++)
  {
    if (isMouseOnBox(workspace.menuBar.menuBarElement[i].x, 36 + 30*j, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].optionsWidth, 36 + 30*(j+1)))
    {
      setcolor(COLOR(0,0,255));
      rectangle(workspace.menuBar.menuBarElement[i].x+1, 36 + 30*j+1, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].optionsWidth-1, 36 + 30*(j+1)-1);
    }
    if (ismouseclick(WM_LBUTTONDOWN) && isMouseOnBox(workspace.menuBar.menuBarElement[i].x, 36 + 30*j, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].optionsWidth, 36 + 30*(j+1)))
    {
      workspace.menuBar.menuBarElement[i].open = false;
      workspace.menuBar.open = -1;
      setcolor(COLOR(255,0,0));
      rectangle(workspace.menuBar.menuBarElement[i].x, 36 + 30*j, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].optionsWidth, 36 + 30*(j+1));
      switch(workspace.menuBar.menuBarElement[i].options[j].functionId)
      {
        case 0: // NEW FILE
          std::cout << "newfile\n";
          cleardevice();
          draw(workspace);
          refresh();
          newFile(workspace);
          break;
        case 1: // LOAD FILE
          loadFile(workspace, 0);
          break;
        case 2: // SAVE FILE
          std::cout << "saving file...\n";
          saveFile(workspace, workspace.currentFile);
          break;
        default:
          std::cerr << "ERROR: in function activateMenuBarOption: Invalid function id\n";
      }

    }
  }
}

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
