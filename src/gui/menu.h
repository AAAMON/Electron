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
  char elements[24][30];

  int scroll;
};

void initMenu(Menu& menu);
void drawMenu(Menu menu);
void printMenu(Menu menu);

#endif