#include "menu.h"
#include "../core/workspace.h"
#include "../core/files.h"
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
    if (workspace.menu.columns[c+i].content[0] == 'A')
      i++;
    
    // ONE COMPONENT
    // menu.components[(int)menu.columns[c+i].content[1]-'0']
    if (isMouseOnBox(2, 38 + workspace.menu.elementHeigth * i, workspace.menu.width/2 - workspace.menu.buttonWidth -2, 36 + workspace.menu.elementHeigth * (i + 1) - 2))
    {
      strcpy(workspace.currentMessage, workspace.menu.components[(int)workspace.menu.columns[c+i].content[1]-'0'].name);
      setrgbcolor(SELECTION);
      if (workspace.menuBar.open == -1)
      rectangle (2, 38 + workspace.menu.elementHeigth * i, workspace.menu.width/2 - workspace.menu.buttonWidth -2, 36 + workspace.menu.elementHeigth * (i + 1) - 2);
    }
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
        setrgbcolor(SELECTION);
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
      {
        strcpy(workspace.currentMessage, workspace.menu.components[(int)workspace.menu.columns[c+i].content[2]-'0'].name);
        setrgbcolor(SELECTION);
        if (workspace.menuBar.open == -1)
          rectangle (2 + workspace.menu.width/2 - workspace.menu.buttonWidth, 38 + workspace.menu.elementHeigth * i, workspace.menu.width - workspace.menu.buttonWidth - 2, 36 + workspace.menu.elementHeigth * (i + 1) - 2);
      }
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
          moveComponent(workspace.components[workspace.nrOfComponents-1], (mousex() - workspace.panningX)/workspace.zoom, (mousey() - workspace.panningY)/workspace.zoom);
          cleardevice();
          draw(workspace);
          drawWorkspaceComponent(workspace, workspace.components[workspace.nrOfComponents-1]);
          setrgbcolor(SELECTION);
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
    
    setrgbcolor(HOLLOW_BOX);
    setfillstyle(SOLID_FILL, getcolor());
    //bar(menuBarElement.x, 36 + 30*i, menuBarElement.x + menuBarElement.optionsWidth, 36 + 30*(i+1));
    hollowBox(menuBarElement.x, 36 + 30*i, menuBarElement.x + menuBarElement.optionsWidth, 36 + 30*(i+1));

    int j = 0;
    setcolor(BLACK);
    rectangle(menuBarElement.x + j, 36 + 30*i + j, menuBarElement.x + menuBarElement.optionsWidth-j, 36 + 30*(i+1)-j);
    j++;
    setrgbcolor(BIG_BOX);
    //setrgbcolor(COLOR(RED_VALUE(BIG_BOX) + 70, GREEN_VALUE(BIG_BOX) + 70, BLUE_VALUE(BIG_BOX) + 70));
    rectangle(menuBarElement.x + j, 36 + 30*i + j, menuBarElement.x + menuBarElement.optionsWidth-j, 36 + 30*(i+1)-j);
    


    settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
    settextjustify (LEFT_TEXT, CENTER_TEXT);
    setrgbcolor(MENU_COMPONENT_TEXT);
    outtextxy(menuBarElement.x + 10, 36+ 15 +30*i, menuBarElement.options[i].name);
  }
}

void activateMenuBar(Electron& workspace)
{
  for (int i = 0; i < workspace.menuBar.nrOfElements; i++)
  {  
    if (isMouseOnBox(workspace.menuBar.menuBarElement[i].x, 0, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].w, 36))
    {
      setrgbcolor(SELECTION);
      //setcolor(BLACK);
      rectangle(workspace.menuBar.menuBarElement[i].x+1, 1, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].w-1, 35);
      refresh();
    }
    while (workspace.menuBar.menuBarElement[i].open && ismouseclick(WM_LBUTTONDOWN)) // if we click somewhere else
    {
      while (ismouseclick(WM_LBUTTONDOWN));
      workspace.menuBar.menuBarElement[i].open = NOPE;
      workspace.menuBar.open = -1;
    }
    if (workspace.menuBar.open == -1 && isMouseOnBox(workspace.menuBar.menuBarElement[i].x, 0, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].w, 36)
        && ismouseclick(WM_LBUTTONDOWN))
    {
      setalpha(BLACK, 50);
      setfillstyle(SOLID_FILL, BLACK);
      bar(workspace.menuBar.menuBarElement[i].x+6, 6, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].w-6, 30);
      refresh();
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
      setalpha(BLACK, 50);
      setfillstyle(SOLID_FILL, BLACK);
      bar(workspace.menuBar.menuBarElement[i].x+6, 6, workspace.menuBar.menuBarElement[i].x + workspace.menuBar.menuBarElement[i].w-6, 30);
      refresh();
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
      setrgbcolor(SELECTION);
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
        case 3: // DELETE FILE
          std::cout << "deleting file...\n";
          deleteFile(workspace);
          break;
        case 4: // TUTOR ON
          workspace.tutor = YEAH;
          break;
        case 5: // TUTOR OFF
          workspace.tutor = NOPE;
          break;
        case 6:
          std::cout << "changing theme...\n";
          loadTheme(6);
          break;
        case 7:
          std::cout << "changing theme...\n";
          loadTheme(7);
          break;
        case 8:
          std::cout << "changing theme...\n";
          loadTheme(8);
          break;
        case 9: // help
          showHelp();
          break;
        case 10:
          showCredits();
          break;
        default:
          std::cerr << workspace.menuBar.menuBarElement[i].options[j].functionId << "ERROR: in function activateMenuBarOption: Invalid function id\n";
      }

    }
  }
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