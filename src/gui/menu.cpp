#include <iostream>
#include <fstream>
#include "menu.h"
#include "../core/components.h"


//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


void initMenu(Menu& menu)
{
  menu.show = true;
  menu.width = WIDTH/5;
  menu.height = HEIGHT-48;
  menu.elementHeigth = menu.height/12;
  menu.buttonWidth = 20;
  menu.scroll = 0;
  
  std::ifstream menuFile("assets/menu.gui");
  menuFile >> menu.nrOfColumns;

  char text[30];
  int cat = -1; // iterator for categories
  int com = 0; // iterator for components
  // reading all the columns
  menuFile.getline(text, 30); // reads a space or smth
  for (int i = 0; i < menu.nrOfColumns; i++)
  {
    menuFile.getline(text, 30);
    if (strstr(text, "CATEGORY"))
    {
      // CREATE NEW CATEGORY
      cat++;
      strcpy(menu.categories[cat].name, text + 9); // +9 so it skips "CATEGORY "
      menu.categories[cat].nrOfColumns = 0;
      // UPDATE COLUMN
      char content[3] = { "A" };
      content[1] = { '0' };
      content[1] += cat;
      strcpy(menu.columns[i].content, content); 
      menu.columns[i].visible = true;
    }
    else
    {
      // CREATE NEW COMPONENT
      menu.categories[cat].nrOfColumns++; // add column to current category
      char* componentName;
      componentName = strtok(text, " ");
      // first one
      initComponent(menu.components[com], componentName);
      // UPDATE COLUMN
      char content[3] = { "O" };
      content[1] = { '0' };
      content[1] += com;
      com++;
      componentName = strtok(NULL, " "); // next component
      if (componentName != NULL)
      {
        initComponent(menu.components[com], componentName);
        content[2] = { '0' };
        content[2] += com;
        com++;
      }
      content[3] = '\0'; // don't ask why, just leave it here
      strcpy(menu.columns[i].content, content); 
      menu.columns[i].visible = true;
    }
  }
}


// // Draws the menu on the built-in SDL_Surface
void drawMenu(Menu menu)
{
  if (menu.show) {
    // BACKGROUND
    setfillstyle(SOLID_FILL, COLOR(138,132,155));
    bar(0, 24, menu.width, 24 + menu.height);
    // SCROLL BAR
    setcolor(COLOR(36,35,39));
    setfillstyle(SOLID_FILL, COLOR(176,168,159));
    bar(menu.width - menu.buttonWidth, 24, menu.width, 24 + menu.height);
    setcolor(COLOR(36,35,39));
    rectangle(menu.width - menu.buttonWidth, 24, menu.width, 24 + menu.height);
    line(menu.width - menu.buttonWidth, 24 + menu.height/2-20, menu.width, 24 + menu.height/2-20);
    line(menu.width - menu.buttonWidth, 24 + menu.height/2+20, menu.width, 24 + menu.height/2+20);
    // plz replace this with some arrows...
    setcolor(COLOR(36,35,39));
    outtextxy(menu.width - menu.buttonWidth/2, 24 + menu.buttonWidth/2, (char*)"n");
    outtextxy(menu.width - menu.buttonWidth/2, 24 + menu.buttonWidth/2*3, (char*)"n");
    outtextxy(menu.width - menu.buttonWidth/2, 24 + menu.buttonWidth/2*5, (char*)"n");
    outtextxy(menu.width - menu.buttonWidth/2, 24 + menu.height/2, (char*)"<");
    outtextxy(menu.width - menu.buttonWidth/2, 24 + menu.height - menu.buttonWidth/2*5, (char*)"u");
    outtextxy(menu.width - menu.buttonWidth/2, 24 + menu.height - menu.buttonWidth/2*3, (char*)"u");
    outtextxy(menu.width - menu.buttonWidth/2, 24 + menu.height - menu.buttonWidth/2, (char*)"u");

    // MENU ELEMENTS
    int c = menu.scroll;
    for (int i = 0; i < 12; i++)
    {
      // IF THE COLUMN IS A C(A)TEGORY NAME
      if (menu.columns[c+i].content[0] == 'A')
      {
        setcolor(COLOR(36,35,39));
        settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
        settextjustify (CENTER_TEXT, CENTER_TEXT);
        rectangle(0, 24 + menu.elementHeigth * i, menu.width - menu.buttonWidth, 24 + menu.elementHeigth * (i + 1));
        setcolor(WHITE);
        outtextxy(0 + menu.width/2 - menu.buttonWidth/2, 24 + menu.elementHeigth * i + menu.elementHeigth/2, menu.categories[(int)menu.columns[c+i].content[1]-'0'].name);
      }
      // IF THE ELEMENT IS A C(O)MPONENT
      else
      {
        setcolor(COLOR(36,35,39));
        settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
        settextjustify (CENTER_TEXT, CENTER_TEXT);
        rectangle(0, 24 + menu.elementHeigth * i, menu.width - menu.buttonWidth, 24 + menu.elementHeigth * (i + 1));
        line(menu.width/2 - menu.buttonWidth, 24 + menu.elementHeigth * i, menu.width/2 - menu.buttonWidth, 24 + menu.elementHeigth * (i + 1));
        // black bars
        setfillstyle(SOLID_FILL, COLOR(87,87,87));
        bar(2, 26 + menu.elementHeigth * i, menu.width/2 - menu.buttonWidth -2, 24 + menu.elementHeigth * (i + 1) - 2);
        bar(2 + menu.width/2 - menu.buttonWidth, 26 + menu.elementHeigth * i, menu.width - menu.buttonWidth - 2, 24 + menu.elementHeigth * (i + 1) - 2);
        // TWO COMPONENT ON ROW
        if (menu.columns[c+i].content[2])
        {
          moveComponent(menu.components[(int)menu.columns[c+i].content[1]-'0'], 0 + menu.width/4 - menu.buttonWidth/2, 24 + menu.elementHeigth * i + menu.elementHeigth/2 - 10);
          moveComponent(menu.components[(int)menu.columns[c+i].content[2]-'0'], 0 + menu.width/4*3 - menu.buttonWidth/2, 24 + menu.elementHeigth * i + menu.elementHeigth/2 - 10);
          setcolor(COLOR(153,200,153));
          drawComponent(menu.components[(int)menu.columns[c+i].content[1]-'0']);
          drawComponent(menu.components[(int)menu.columns[c+i].content[2]-'0']);
          setcolor(WHITE);
          outtextxy(0 + menu.width/4 - menu.buttonWidth/2, 24 + menu.elementHeigth * i + menu.elementHeigth - 10, menu.components[(int)menu.columns[c+i].content[1]-'0'].name);
          outtextxy(0 + menu.width/4*3 - menu.buttonWidth/2, 24 + menu.elementHeigth * i + menu.elementHeigth - 10, menu.components[(int)menu.columns[c+i].content[2]-'0'].name);
        }
        // ONE COMPONENTS ON ROW
        else
        {
          moveComponent(menu.components[(int)menu.columns[c+i].content[1]-'0'], 0 + menu.width/4 - menu.buttonWidth/2, 24 + menu.elementHeigth * i + menu.elementHeigth/2 - 10);
          setcolor(COLOR(153,200,153));
          drawComponent(menu.components[(int)menu.columns[c+i].content[1]-'0']);
          setcolor(WHITE);
          outtextxy(0 + menu.width/4 - menu.buttonWidth/2, 24 + menu.elementHeigth * i + menu.elementHeigth - 10, menu.components[(int)menu.columns[c+i].content[1]-'0'].name);
        }
      }
    }
  }
  else
  {
    setfillstyle(SOLID_FILL, COLOR(138,132,155));
    setcolor(COLOR(36,35,39));
    bar(0, 24, menu.buttonWidth, 24 + menu.height);
    setfillstyle(SOLID_FILL, COLOR(176,168,159));
    bar(0, 24 + menu.height/2 - 20, menu.buttonWidth, 24 + menu.height/2 + 20);
    rectangle(0, 24, menu.buttonWidth, 24 + menu.height);
    line(0, 24 + menu.height/2-20, menu.buttonWidth, 24 + menu.height/2-20);
    line(0, 24 + menu.height/2+20, menu.buttonWidth, 24 + menu.height/2+20);
    outtextxy(menu.buttonWidth/2, 24 + menu.height/2, (char*)">");
  }
}

void activateScrollMenu(Menu& menu)
{
  //rectangle(menu.width - menu.buttonWidth, 0, menu.width, HEIGHT);
  if (menu.show && ismouseclick(WM_LBUTTONDOWN)&& isMouseOnBox(menu.width - menu.buttonWidth, 24, menu.width, 24 + menu.height/2-20) && menu.scroll > 0)
  {
    menu.scroll--;
    delay(100);
  }
  if (menu.show && ismouseclick(WM_LBUTTONDOWN) && isMouseOnBox(menu.width - menu.buttonWidth, 24 + menu.height/2+20, menu.width, 24 + menu.height) && menu.scroll < menu.nrOfColumns-12)
  {
    menu.scroll++;
    delay(100);
  }
  if (menu.show && ismouseclick(WM_LBUTTONDOWN) && isMouseOnBox(menu.width - menu.buttonWidth, 24 + menu.height/2-20, menu.width, 24 + menu.height/2+20))
  {
    menu.show = false;
    delay(100);
  }
  if (!menu.show && ismouseclick(WM_LBUTTONDOWN) && isMouseOnBox(0, 24, menu.buttonWidth, 24 + menu.height))
  {
    menu.show = true;
    delay(100);
  }
}

bool isMouseOnBox(int x1, int y1, int x2, int y2)
{
  if (mousex() > x1 && mousex() < x2)
    if (mousey() > y1 && mousey() < y2)
      {
        return YEAH;
      }
  return NOPE;
}

//////////////////////////////////////////////////////////////////////////////
/// D E B U G ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void printMenu(Menu menu)
{
  std::cout << menu.nrOfColumns << '\n';
  for (int i = 0; i < menu.nrOfColumns; i++)
  {
    std::cout << menu.columns[i].content << "\n";
  }
}

