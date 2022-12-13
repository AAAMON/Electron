#include <iostream>
#include <cmath>
#include <graphics.h>
#include "boxes.h"

void bigBox(int x, int y, int w, int h, int size)
{
  // SOLID FILL
  setfillstyle(SOLID_FILL, COLOR(138,132,155));
  bar(x, y, x + w, y + h);
  int i = 0;
  // OUTLINE
  setcolor(COLOR(78, 75, 88));
  for (int z = 0; z < size; z++)
  {
    rectangle(x+i, y+i, x + w-i, y + h-i);
    i++;
  }


  // outline highlight
  setcolor(COLOR(142, 136, 161));
  for (int z = 0; z < size; z++)
  {
    rectangle(x+i, y+i, x + w-i, y + h-i);
    i++;
  }

  // outline shadow
  setcolor(COLOR(64, 62, 71));
  for (int z = 0; z < size; z++)
  {
    rectangle(x+i, y+i, x + w-i, y + h-i);
    i++;
  }

  // DARK LINE
  setcolor(COLOR(37, 35, 41));
  for (int z = 0; z < size; z++)
  {
    rectangle(x+i, y+i, x + w-i, y + h-i);
    i++;
    rectangle(x+i, y+i, x + w-i, y + h-i);
    i++;
  }

  // again outline highlight
  setcolor(COLOR(78, 75, 88));
  for (int z = 0; z < size; z++)
  {
    rectangle(x+i, y+i, x + w-i, y + h-i);
    i++;
  }
  // outline highlight
  setcolor(COLOR(142, 136, 161));
  for (int z = 0; z < size; z++)
  {
    rectangle(x+i, y+i, x + w-i, y + h-i);
    i++;
  }

  int r = 71;
  int g = 68;
  int b = 79;
  // DETAILS
  for (int x1 = x+i; x1 < x+w-i; x1++)
  {
    for (int y1 = y+i; y1 < y+h-i; y1++)
    {
      putpixel(x1, y1, COLOR(r + 1.2*std::min(abs(x - x1), std::min(abs(x+w - x1), std::min(abs(y - y1), abs(y+h - y1)))), 
                             g + 1.2*std::min(abs(x - x1), std::min(abs(x+w - x1), std::min(abs(y - y1), abs(y+h - y1)))), 
                             b + 1.2*std::min(abs(x - x1), std::min(abs(x+w - x1), std::min(abs(y - y1), abs(y+h - y1))))));
    }
  }
}