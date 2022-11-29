#include <iostream>
#include <cstring>
#include <graphics.h>
#include <cmath>
#include "button.h"

// Void function for button (does nothing)
void bVoid()
{
  ;
}

// Test function for button
void bStart()
{
  cleardevice();
  refresh();
}

// Initialises the button
void createButton(Button &button, int x, int y, const char* label, int size, void (*onClick)())
{
  button.x = x;
  button.y = y;
  strcpy(button.label, label);
  button.size = size;
  button.onClick = onClick;

  // funky formula that sets the button width based on label and button size
  int magicX = pow(1.11, button.size)*log(button.size)*(int)strlen(button.label)*3.6+15;
  button.width = magicX * 2;

  drawButton(button);
}

// Draws the button on screen
void drawButton(Button button)
{
  // BOX
  setcolor(COLOR(250, 250, 250));
  // setalpha (getcolor (), 80); // has weird behaviour,,,
  setfillstyle (SOLID_FILL, getcolor ());
  bar(button.x - button.width/2, button.y - 5*button.size, button.x + button.width/2, button.y + 8*button.size);
  
  // LABEL

  settextstyle (GOTHIC_FONT, HORIZ_DIR, button.size);
  settextjustify(CENTER_TEXT, CENTER_TEXT);;
  setcolor(COLOR(1, 0, 26));
  outtextxy(button.x, button.y, button.label);
  if (button.size == 9)
    outtextxy(button.x+1, button.y, button.label);
  refresh();
}

// Checks if the mouse if hovering over the button
bool IsMouseOnButton(Button button)
{
  if (mousex() > button.x - button.width/2 && mousex() < button.x + button.width/2)
    if (mousey() > button.y - 5*button.size && mousey() < button.y + 8*button.size)
      {
        return YEAH;
      }
  return NOPE;
}

void activateButton(Button button)
{
  if (ismouseclick(WM_LBUTTONDOWN) && IsMouseOnButton(button))
    button.onClick(); 
}