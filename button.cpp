#include <cstring>
#include <graphics.h>
#include <cmath>
#include "button.h"

// function for Start button
void bStart(Button)
{
  cleardevice();
}

void createButton(Button button, int x, int y, const char* label, int size, void (*onClick)(Button))
{
  button.x = x;
  button.y = y;
  strcpy(button.label, label);
  button.size = size;
  button.onClick = onClick;
  drawButton(button);
}

void drawButton(Button button)
{
  // BOX
  setcolor(COLOR(250, 250, 250));
  setalpha (getcolor (), 80);
  setfillstyle (SOLID_FILL, getcolor ());
  // funky formula that sets the button width based on label and button size
  int magicX = pow(1.11, button.size)*log(button.size)*(int)strlen(button.label)*3.6+15;
  bar(button.x - magicX, button.y - 5*button.size, button.x + magicX, button.y + 8*button.size);
  
  // LABEL

  settextstyle (GOTHIC_FONT, HORIZ_DIR, button.size);
  settextjustify(CENTER_TEXT, CENTER_TEXT);;
  setcolor(COLOR(1, 0, 26));
  outtextxy(button.x, button.y, button.label);
  if (button.size == 9)
    outtextxy(button.x+1, button.y, button.label);
  refresh();
}
