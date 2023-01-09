#include <iostream>
#include <cmath>
#include <graphics.h>
#include "boxes.h"
#include "../core/project.h"



int distance(int x1, int y1, int x2, int y2)
{
  int dis = { 0 };
  dis += (x1 - x2) * (x1 - x2); 
  dis += (y1 - y2) * (y1 - y2); 
  dis = sqrt(dis);
  return dis;
}

void bigBox(int x, int y, int w, int h, int size, bool differentColor)
{
  int c;
  if (differentColor)
    c = MENU_BAR;
  else
    c = BIG_BOX;
  int i = 0;
  // LEFT & TOP
  // OUTLINE 1
  setrgbcolor(c);
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    setcolor(COLOR(RED_VALUE(c)-50, GREEN_VALUE(c)-50, BLUE_VALUE(c)-60));
    //setcolor(COLOR(36, 35, 39));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }


  // 2
  setcolor(COLOR(RED_VALUE(c)+60, GREEN_VALUE(c)+55, BLUE_VALUE(c)+65));
  //setcolor(COLOR(143, 137, 163));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    setcolor(COLOR(RED_VALUE(c)-17, GREEN_VALUE(c)-17, BLUE_VALUE(c)-21));
    //setcolor(COLOR(69, 66, 77));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }

  // 3
  setcolor(COLOR(RED_VALUE(c)-27, GREEN_VALUE(c)-27, BLUE_VALUE(c)-31));
  //setcolor(COLOR(60, 57, 66));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    setcolor(COLOR(RED_VALUE(c)+10, GREEN_VALUE(c)+10, BLUE_VALUE(c)+10));
    //setcolor(COLOR(92, 88, 103));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }

  // DARK LINE
  setcolor(COLOR(RED_VALUE(c)-50, GREEN_VALUE(c)-50, BLUE_VALUE(c)-60));
  //setcolor(COLOR(37, 35, 41));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    setcolor(COLOR(RED_VALUE(c)+60, GREEN_VALUE(c)+55, BLUE_VALUE(c)+65));
    //setcolor(COLOR(149, 143, 169));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
    setcolor(COLOR(RED_VALUE(c)-50, GREEN_VALUE(c)-50, BLUE_VALUE(c)-60));
    //setcolor(COLOR(37, 35, 41));
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);  
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }

  // 5
  setrgbcolor(c);
  //setcolor(COLOR(87, 83, 99));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    setcolor(COLOR(RED_VALUE(c)-50, GREEN_VALUE(c)-50, BLUE_VALUE(c)-60));
    //setcolor(COLOR(37, 35, 41));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }
  // 6
  setcolor(COLOR(RED_VALUE(c)+60, GREEN_VALUE(c)+55, BLUE_VALUE(c)+65));
  //setcolor(COLOR(145, 139, 164));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    i++;
  }




  int r = std::min(RED_VALUE(c)+50, 255);//RED_VALUE(c)132;
  int g = std::min(GREEN_VALUE(c)+45, 255);//GREEN_VALUE(c)126;
  int b =  std::min(BLUE_VALUE(c)+50, 255);//BLUE_VALUE(c)149;
  int nr;
  int ng;
  int nb;
  int xy;
  // DETAILS
  if (w > 500)
  {
    for (int x1 = x+i; x1 < x+w-i; x1++)
    {
      for (int y1 = y+i; y1 < y+h-i; y1++)
      {
        xy = abs(distance(x1, y1, x+w/2, y+h/2));
        nr = r - 0.1*xy;
        ng = g - 0.1*xy;
        nb = b - 0.1*xy;
        putpixel(x1, y1, COLOR(nr < 0? 0:nr, ng < 0? 0:ng, nb < 0? 0:nb));
      }
    }
  }
  else 
  {
    for (int x1 = x+i; x1 < x+w-i; x1++)
    {
      for (int y1 = y+i; y1 < y+h-i; y1++)
      {
        xy = abs(distance(x1, y1, x+w/2, y+h/2));
        nr = r - 0.4*xy;
        ng = g - 0.4*xy;
        nb = b - 0.4*xy;
        putpixel(x1, y1, COLOR(nr < 0? 0:nr, ng < 0? 0:ng, nb < 0? 0:nb));
      }
    }
  }

}

// void smallBox(int x, int y, int x2, int y2)
// {
//   // SOLID FILL
//   setfillstyle(SOLID_FILL, COLOR(138,132,155));
//   bar(x, y, x2, y2);
//   setcolor(COLOR(86, 82, 98));
//   rectangle(x, y, x2, y2);
//   setcolor(COLOR(143, 137, 163));
//   rectangle(x, y, x2, y2);
// }

void hollowBox(int x, int y, int x2, int y2)
{
  int r = RED_VALUE(HOLLOW_BOX);
  int g = GREEN_VALUE(HOLLOW_BOX);
  int b = BLUE_VALUE(HOLLOW_BOX);
  int nr;
  int ng;
  int nb;
  int xy;
  // DETAILS
  for (int x1 = x; x1 < x2; x1++)
  {
    for (int y1 = y; y1 < y2; y1++)
    {
      xy = abs(distance(x1, y1, x+(x2-x)/3*2, y+(y2-y)/3*2));
      nr = r - 0.07*xy*log(xy);
      ng = g - 0.07*xy*log(xy);
      nb = b - 0.07*xy*log(xy);
      putpixel(x1, y1, COLOR(nr < 0? 0:nr, ng < 0? 0:ng, nb < 0? 0:nb));
    }
  }
}

void longButtonBox(int x, int y, int w, int h, bool reverse)
{

  setfillstyle(SOLID_FILL, RED);
  bar(x, y, x+w, y+h);
  int r = RED_VALUE(BUTTON_BOX);
  int g = GREEN_VALUE(BUTTON_BOX);
  int b = BLUE_VALUE(BUTTON_BOX);
  float nr = r;
  float ng = g;
  float nb = b;

  // OUTLINE
  int i = 0;
     if (!reverse)
  { 
  for (i = 0; i < 3; i++)
  {    
    r = RED_VALUE(BUTTON_BOX);
    g = GREEN_VALUE(BUTTON_BOX);
    b = BLUE_VALUE(BUTTON_BOX);
    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+i; x1 < x+w-i+1; x1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+i, getcolor());
      nr+=0.15;
      ng+=0.15;
      nb+=0.15;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+i; y1 < y+h-i+1; y1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+i, y1, getcolor());
      nr+=0.15;
      ng+=0.15;
      nb+=0.15;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;
    }
    r = RED_VALUE(BUTTON_BOX);
    g = GREEN_VALUE(BUTTON_BOX);
    b = BLUE_VALUE(BUTTON_BOX);

    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+w-i; x1 > x+i-1; x1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+h-i, getcolor());
      nr-=0.15;
      ng-=0.15;
      nb-=0.15;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+h-i; y1 > y+i-1; y1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+w-i, y1, getcolor());
      nr-=0.15;
      ng-=0.15;
      nb-=0.15;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
  }

  for (;i < 5; i++)
  {
  //    // OUTLINE 2

    r = RED_VALUE(BUTTON_BOX)+55;
    g = GREEN_VALUE(BUTTON_BOX)+55;
    b = BLUE_VALUE(BUTTON_BOX)+55;
    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+i; x1 < x+w-i+1; x1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+i, getcolor());
      nr+=0.15;
      ng+=0.15;
      nb+=0.15;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+i; y1 < y+h-i+1; y1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+i, y1, getcolor());
      nr+=0.15;
      ng+=0.15;
      nb+=0.15;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;      
    }

    r = RED_VALUE(BUTTON_BOX)+55;
    g = GREEN_VALUE(BUTTON_BOX)+55;
    b = BLUE_VALUE(BUTTON_BOX)+55;

    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+w-i; x1 > x+i-1; x1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+h-i, getcolor());
      nr-=0.15;
      ng-=0.15;
      nb-=0.15;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+h-i; y1 > y+i-1; y1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+w-i, y1, getcolor());
      nr-=0.15;
      ng-=0.15;
      nb-=0.15;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
  }
// GRADIENT
    int xy;
    r = RED_VALUE(BUTTON_BOX)-20;
    g = GREEN_VALUE(BUTTON_BOX)-20;
    b = BLUE_VALUE(BUTTON_BOX)-20;
    for (int x1 = x+4; x1 < x+w-4; x1++)
    {
      for (int y1 = y+4; y1 < y+h-4; y1++)
      {
        xy = abs(distance(x1, y1, x, y));
        nr = r + 0.03*xy*log(xy);
        ng = g + 0.03*xy*log(xy);
        nb = b + 0.03*xy*log(xy);
        putpixel(x1, y1, COLOR(nr, ng, nb));
      }
    }
    return;
  }
  
  
  
  for (i = 0; i < 3; i++)
  {    
    r = RED_VALUE(BUTTON_BOX);
    g = GREEN_VALUE(BUTTON_BOX);
    b = BLUE_VALUE(BUTTON_BOX);
    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+w-i; x1 > x+i-1; x1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+i, getcolor());
      nr+=0.15;
      ng+=0.15;
      nb+=0.15;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+h-i; y1 > y+i-1; y1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+i, y1, getcolor());
      nr+=0.15;
      ng+=0.15;
      nb+=0.15;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;      
    }
    r = RED_VALUE(BUTTON_BOX);
    g = GREEN_VALUE(BUTTON_BOX);
    b = BLUE_VALUE(BUTTON_BOX);

    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+i; x1 < x+w-i+1; x1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+h-i, getcolor());
      nr-=0.15;
      ng-=0.15;
      nb-=0.15;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+i; y1 < y+h-i+1; y1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+w-i, y1, getcolor());
      nr-=0.15;
      ng-=0.15;
      nb-=0.15;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
  }

  for (;i < 5; i++)
  {
  //    // OUTLINE 2

    r = RED_VALUE(BUTTON_BOX)+55;
    g = GREEN_VALUE(BUTTON_BOX)+55;
    b = BLUE_VALUE(BUTTON_BOX)+55;

    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+w-i; x1 > x+i-1; x1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+i, getcolor());
      nr+=0.15;
      ng+=0.15;
      nb+=0.15;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+h-i; y1 > y+i-1; y1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+i, y1, getcolor());
      nr+=0.15;
      ng+=0.15;
      nb+=0.15;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;
    }

    r = RED_VALUE(BUTTON_BOX)+55;
    g = GREEN_VALUE(BUTTON_BOX)+55;
    b = BLUE_VALUE(BUTTON_BOX)+55;

    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+i; x1 < x+w-i+1; x1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+h-i, getcolor());
      nr-=0.15;
      ng-=0.15;
      nb-=0.15;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+i; y1 < y+h-i+1; y1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+w-i, y1, getcolor());
      nr-=0.15;
      ng-=0.15;
      nb-=0.15;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
  }
  
  int xy;
  r = RED_VALUE(BUTTON_BOX)-20;
  g = GREEN_VALUE(BUTTON_BOX)-20;
  b = BLUE_VALUE(BUTTON_BOX)-20;
  for (int x1 = x+4; x1 < x+w-4; x1++)
  {
    for (int y1 = y+4; y1 < y+h-4; y1++)
    {
      xy = abs(distance(x1, y1, x+w, y+h));
      nr = r + 0.03*xy*log(xy);
      ng = g + 0.03*xy*log(xy);
      nb = b + 0.03*xy*log(xy);
      putpixel(x1, y1, COLOR(nr > 255? 255:nr, ng > 255? 255:ng, nb > 255? 255:nb));
    }
  }
}

void buttonBox(int x, int y, int w, int h)
{
  setfillstyle(SOLID_FILL, RED);
  bar(x, y, x+w, y+h);
  int r = RED_VALUE(BUTTON_BOX);
  int g = GREEN_VALUE(BUTTON_BOX);
  int b = BLUE_VALUE(BUTTON_BOX);
  // int r = 128;
  // int g = 123;
  // int b = 115;
  int nr = r;
  int ng = g;
  int nb = b;

  // OUTLINE
  int i = 0;
  for (i = 0; i < 3; i++)
  {    
    r = RED_VALUE(BUTTON_BOX);
    g = GREEN_VALUE(BUTTON_BOX);
    b = BLUE_VALUE(BUTTON_BOX);
    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+i; x1 < x+w-i+1; x1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+i, getcolor());
      nr+=2;
      ng+=2;
      nb+=2;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+i; y1 < y+h-i+1; y1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+i, y1, getcolor());
      nr+=2;
      ng+=2;
      nb+=2;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;
    }
    r = RED_VALUE(BUTTON_BOX);
    g = GREEN_VALUE(BUTTON_BOX);
    b = BLUE_VALUE(BUTTON_BOX);

    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+w-i; x1 > x+i-1; x1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+h-i, getcolor());
      nr-=2;
      ng-=2;
      nb-=2;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+h-i; y1 > y+i-1; y1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+w-i, y1, getcolor());
      nr-=2;
      ng-=2;
      nb-=2;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
  }

  for (;i < 5; i++)
  {
  //    // OUTLINE 2
    r = RED_VALUE(BUTTON_BOX)+55;
    g = GREEN_VALUE(BUTTON_BOX)+55;
    b = BLUE_VALUE(BUTTON_BOX)+55;

    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+i; x1 < x+w-i+1; x1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+i, getcolor());
      nr+=2;
      ng+=2;
      nb+=2;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+i; y1 < y+h-i+1; y1++)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+i, y1, getcolor());
      nr+=2;
      ng+=2;
      nb+=2;
      if (nr > 255)
        nr = 255;
      if (ng > 255)
        ng = 255;
      if (nb > 255)
        nb = 255;
    }

    r = RED_VALUE(BUTTON_BOX)+55;
    g = GREEN_VALUE(BUTTON_BOX)+55;
    b = BLUE_VALUE(BUTTON_BOX)+55;

    nr = r;
    ng = g;
    nb = b;
    for (int x1 = x+w-i; x1 > x+i-1; x1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x1, y+h-i, getcolor());
      nr-=2;
      ng-=2;
      nb-=2;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
    nr = r;
    ng = g;
    nb = b;
    for (int y1 = y+h-i; y1 > y+i-1; y1--)
    {
      setcolor(COLOR(nr, ng, nb));
      putpixel(x+w-i, y1, getcolor());
      nr-=2;
      ng-=2;
      nb-=2;
      if (nr < 0)
        nr = 0;
      if (ng < 0)
        ng = 0;
      if (nb < 0)
        nb = 0;
    }
  }
  // GRADIENT
  int xy;
    r = RED_VALUE(BUTTON_BOX)-20;
    g = GREEN_VALUE(BUTTON_BOX)-20;
    b = BLUE_VALUE(BUTTON_BOX)-20;
  for (int x1 = x+4; x1 < x+w-4; x1++)
  {
    for (int y1 = y+4; y1 < y+h-4; y1++)
    {
      xy = abs(distance(x1, y1, x, y));
      nr = r + xy*log(xy);
      ng = g + xy*log(xy);
      nb = b + xy*log(xy);
      putpixel(x1, y1, COLOR(nr > 255? 255:nr, ng > 255? 255:ng, nb > 255? 255:nb));
    }
  }
}



void doSecretStuff(int& phase, int& r, int& g, int& b)
{
  switch(phase)
  {
    case 0:
      r--;
      g++;
      if (!r)
        phase = 1;
      break;
    case 1:
      g--;
      b++;
      if (!g)
        phase = 2;
      break;
    case 2:
      b--;
      r++;
      if (!b)
        phase = 0;
      break;
    default:
      break;
  }


  setrgbpalette(1, r, g, b);
  setrgbpalette(2, r, g, b);
  setrgbpalette(15, r, g, b);
  setrgbpalette(16, r, g, b);
  setrgbpalette(4, r, g, b);
}