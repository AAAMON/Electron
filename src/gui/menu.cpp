#include <iostream>
#include <fstream>
#include "menu.h"


//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


void initMenu(Menu& menu)
{
  menu.width = WIDTH/5;
  menu.height = HEIGHT;
  menu.elementsPerView = 12;
  menu.elementHeigth = HEIGHT/12;
  menu.scroll = 0;
  menu.buttonWidth = 20;

  for (int i = 0; i < 24; i++)
  {
    strcpy(menu.elements[i], " ");
  }

  
  std::ifstream menuFile("assets/menu.gui");
  menuFile >> menu.nrOfElements;
  // reading all the elements (category names and components)
  menuFile.getline(menu.elements[0], 30);
  for (int i = 0; i < menu.nrOfElements; i++)
    menuFile.getline(menu.elements[i], 30);
}

// Draws the menu on the built-in SDL_Surface
void drawMenu(Menu menu)
{
  setcolor(BLACK);
  // SCROLL BAR
  rectangle(menu.width - menu.buttonWidth, 0, menu.width, HEIGHT);
  line(menu.width - menu.buttonWidth, HEIGHT/2, menu.width, HEIGHT/2);
  // plz replace this with some arrows...
  outtextxy(menu.width - menu.buttonWidth/2, menu.buttonWidth/2, (char*)"n");
  outtextxy(menu.width - menu.buttonWidth/2, menu.buttonWidth/2*3, (char*)"n");
  outtextxy(menu.width - menu.buttonWidth/2, menu.buttonWidth/2*5, (char*)"n");
  outtextxy(menu.width - menu.buttonWidth/2, menu.height - menu.buttonWidth/2*5, (char*)"u");
  outtextxy(menu.width - menu.buttonWidth/2, menu.height - menu.buttonWidth/2*3, (char*)"u");
  outtextxy(menu.width - menu.buttonWidth/2, menu.height - menu.buttonWidth/2, (char*)"u");

  // MENU ELEMENTS
  int c = 0;
  for (int i = 0; i < menu.scroll; i++)
  {
    if (strstr(menu.elements[c], "CATEGORY"))
      c++;
    else if (strstr(menu.elements[c+1], "CATEGORY")) 
      c++;
    else
      c+=2;
  }
  for (int i = 0; i < 12;)
  {
    // IF THE ELEMENT IS A CATEGORY NAME
    if (strstr(menu.elements[c], "CATEGORY"))
    {
      setcolor(BLACK);
      settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
      settextjustify (CENTER_TEXT, CENTER_TEXT);
      rectangle(0, menu.elementHeigth * i, menu.width - menu.buttonWidth, menu.elementHeigth * (i + 1));
      outtextxy(0 + menu.width/2 - menu.buttonWidth/2, menu.elementHeigth * i + menu.elementHeigth/2, menu.elements[c]);
      c++;
      i++;
    }
    // IF THE ELEMENT IS A COMPONENT
    else
    {
      setcolor(BLACK);
      settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
      settextjustify (CENTER_TEXT, CENTER_TEXT);
      rectangle(0, menu.elementHeigth * i, menu.width - menu.buttonWidth, menu.elementHeigth * (i + 1));
      line(menu.width/2 - menu.buttonWidth, menu.elementHeigth * i, menu.width/2 - menu.buttonWidth, menu.elementHeigth * (i + 1));
      // ONE COMPONENT ON ROW
      if (strstr(menu.elements[c+1], "CATEGORY")) // odd number of components on line
      {
        if (strcmp(menu.elements[c], " "))
          outtextxy(0 + menu.width/4 - menu.buttonWidth/2, menu.elementHeigth * i + menu.elementHeigth/2, menu.elements[c]);
        c++;
        i++;
      }
      // TWO COMPONENTS ON ROW
      else
      {
        if (strcmp(menu.elements[c], " "))
          outtextxy(0 + menu.width/4 - menu.buttonWidth/2, menu.elementHeigth * i + menu.elementHeigth/2, menu.elements[c]);
        if (strcmp(menu.elements[c+1], " "))
          outtextxy(0 + menu.width/4*3 - menu.buttonWidth/2, menu.elementHeigth * i + menu.elementHeigth/2, menu.elements[c+1]);
        c+=2;
        i++;
      }
    }
  }
}

void activateScrollMenu(Menu& menu)
{
  //rectangle(menu.width - menu.buttonWidth, 0, menu.width, HEIGHT);
  if (ismouseclick(WM_LBUTTONDOWN) && isMouseOnBox(menu.width - menu.buttonWidth, 0, menu.width, menu.height/2) && menu.scroll > 0)
  {
    menu.scroll--;
    delay(100);
  }
    
  // fix the -5, we need the nr or categories...
  if (ismouseclick(WM_LBUTTONDOWN) && isMouseOnBox(menu.width - menu.buttonWidth, menu.height/2, menu.width, menu.height) && menu.scroll < menu.nrOfElements-5)
  {
    menu.scroll++;
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
  std::cout << menu.nrOfElements << '\n';
  for (int i = 0; i < menu.nrOfElements; i++)
  {
    std::cout << menu.elements[i] << "e\n";
  }
}

