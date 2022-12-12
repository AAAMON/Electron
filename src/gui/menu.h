#include "../core/project.h"
#include "../core/components.h"
#ifndef COMPONENTS_MENU_ELECTRON_H
#define COMPONENTS_MENU_ELECTRON_H


// merge component name with components

struct Category
{
  char name[30];
  int nrOfColumns;
};

struct Column
{
  char content[10]; // A for cAtegory, O for cOmponent, next 2 chars for indexes
  bool visible;
};

struct Menu
{
  int width;
  int height;
  int elementHeigth;
  int buttonWidth;

  int nrOfColumns;
  Column columns[50]; // maybe change this for a linked list?
  Category categories[10];
  Component components[80];

  int scroll;
  bool show;
};

void initMenu(Menu& menu);
void initMenuComponents(Menu& menu);
void drawMenu(Menu menu);
void printMenu(Menu menu);
void activateScrollMenu(Menu& menu);
bool isMouseOnBox(int x1, int y1, int x2, int y2);

#endif