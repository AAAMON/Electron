#ifndef COMPONENTS_MENU_ELECTRON_H
#define COMPONENTS_MENU_ELECTRON_H
#include <iostream>
#include <fstream>
#include <graphics.h>
#include "../core/components.h"
#include "button.h"
#include "boxes.h"
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

struct MenuBarOption
{
  char name[50];
  int functionId; // for the function that will get called on click
};

struct MenuBarElement
{
  char name[20];
  int x;
  int w;
  bool open;
  int nrOfOptions;
  MenuBarOption options[5];
  int optionsWidth;
};

struct MenuBar
{
  MenuBarElement menuBarElement[10];
  int nrOfElements;
  int open;
};

struct menuBarButton
{
  char text[10];
  int nrOfElements;
  int x;
  int y;
  int w;
};

//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void initMenu(Menu& menu);
void initMenuBar(MenuBar& menuBar); 
void drawMenu(Menu menu);

void drawMenuBar(MenuBar menuBar);

/*  //

*/

//////////////////////////////////////////////////////////////////////////////
/// M I S C //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

bool isMouseOnBox(int x1, int y1, int x2, int y2);

//////////////////////////////////////////////////////////////////////////////
/// D E B U G ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void printMenu(Menu menu);


#endif