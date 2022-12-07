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

  for (int i = 0; i < 12; i++)
  {
    strcpy(menu.elements[i], "");
  }

  
  std::ifstream menuFile("assets/menu.gui");
  menuFile >> menu.nrOfElements;
  // reading all the elements (category names and components)
  menuFile.getline(menu.elements[0], 30);
  for (int i = 0; i < menu.nrOfElements; i++)
    menuFile.getline(menu.elements[i], 30);
}

void drawMenu(Menu menu)
{
  setcolor(BLACK);
  rectangle(menu.width - menu.buttonWidth, 0, menu.width, HEIGHT);
  line(menu.width - menu.buttonWidth, HEIGHT/2, menu.width, HEIGHT/2);

  // draw all the 12 elements based on scroll
  int c = menu.scroll;
  for (int i = menu.scroll; i < 12;)
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
      std::cout << menu.elements[c] << "here\n";
      // ONE COMPONENT ON ROW
      if (strstr(menu.elements[c+1], "CATEGORY")) // odd number of components on line
      {
        if (strcmp(menu.elements[c], ""))
          outtextxy(0 + menu.width/4 - menu.buttonWidth/2, menu.elementHeigth * i + menu.elementHeigth/2, menu.elements[c]);
        c++;
        i++;
      }
      // TWO COMPONENTS ON ROW
      else
      {
        if (strcmp(menu.elements[c], ""))
        outtextxy(0 + menu.width/4 - menu.buttonWidth/2, menu.elementHeigth * i + menu.elementHeigth/2, menu.elements[c]);
        if (strcmp(menu.elements[c+1], ""))
        outtextxy(0 + menu.width/4*3 - menu.buttonWidth/2, menu.elementHeigth * i + menu.elementHeigth/2, menu.elements[c+1]);
        c+=2;
        i++;
      }
    }
  }

  refresh();
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

