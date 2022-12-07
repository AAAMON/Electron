#include "../core/project.h"
#ifndef COMPONENTS_MENU_ELECTRON_H
#define COMPONENTS_MENU_ELECTRON_H


// merge component name with components

struct Menu
{
  int width;
  int height;
  int elementsPerView;
  int elementHeigth;
  int buttonWidth;

  int nrOfElements;
  char elements[50][30];

  int scroll;
};

void initMenu(Menu& menu);
void drawMenu(Menu menu);
void printMenu(Menu menu);
void activateScrollMenu(Menu& menu);
bool isMouseOnBox(int x1, int y1, int x2, int y2);

#endif