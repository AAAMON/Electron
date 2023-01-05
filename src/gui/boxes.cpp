#include <iostream>
#include <cmath>
#include <graphics.h>
#include "boxes.h"
#include "../core/project.h"

void getColor(Color &color, int r, int g, int b)
{
  color.r=r;
  color.g=g;
  color.b=b;
}

int distance(int x1, int y1, int x2, int y2)
{
  int dis = { 0 };
  dis += (x1 - x2) * (x1 - x2); 
  dis += (y1 - y2) * (y1 - y2); 
  dis = sqrt(dis);
  return dis;
}

void bigBox(int x, int y, int w, int h, int size, Color color)
{
  // SOLID FILL
  setfillstyle(SOLID_FILL, COLOR(color.r,color.g,color.b));
  bar(x, y, x + w, y + h);
  int i = 0;
  // LEFT & TOP
  // OUTLINE 1
  setcolor(COLOR(color.r-52,color.g-50,color.b-57));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    //rectangle(x+i, y+i, x + w-i, y + h-i);
    setcolor(COLOR(color.r-102,color.g-97, color.b-116));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }


  // 2
  setcolor(COLOR(color.r+5,color.g+5, color.b+8));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    setcolor(COLOR(color.r/2, color.g/2, color.b/2));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }

  // 3
  setcolor(COLOR(color.r-78,color.g-75,color.b-89));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    setcolor(COLOR(color.r-46, color.g-50, color.b-52));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }

  // DARK LINE
  setcolor(COLOR(color.r-101, color.g-97, color.b-114));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    setcolor(COLOR(color.r+11, color.g+11, color.b+14));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
      setcolor(COLOR(color.r-101, color.g-97, color.b-114));
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);  
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }

  // 5
  setcolor(COLOR(color.r-51, color.g-49, color.b-56));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    setcolor(COLOR(color.r-101, color.g-97, color.b-114));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }
  // 6
  setcolor(COLOR(color.r+7, color.g+7, color.b+9));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    i++;
  }




  int r = color.r-6;
  int g = color.g-6;
  int b = color.b-6;
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
        putpixel(x1, y1, COLOR(nr, ng, nb));
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
        nr = r - 0.2*xy;
        ng = g - 0.2*xy;
        nb = b - 0.2*xy;
        putpixel(x1, y1, COLOR(nr, ng, nb));
      }
    }
  }

}

void smallBox(int x, int y, int x2, int y2,Color color)
{
  // SOLID FILL
  setfillstyle(SOLID_FILL, COLOR(color.r,color.g,color.b));
  bar(x, y, x2, y2);

  setcolor(COLOR(color.r-52, color.g-50,color.b-57));
  rectangle(x, y, x2, y2);
  
  setcolor(COLOR(color.r+5, color.g+5, color.b+8));
  rectangle(x, y, x2, y2);
}

void hollowBox(int x, int y, int x2, int y2,Color color)
{
  int r = color.r-51;
  int g = color.g-45;
  int b = color.b-68;
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
      putpixel(x1, y1, COLOR(nr, ng, nb));
    }
  }
}

void longButtonBox(int x, int y, int w, int h, bool reverse, Color color)
{

  setfillstyle(SOLID_FILL, RED);
  bar(x, y, x+w, y+h);
  int r = color.r-10;
  int g = color.g-9;
  int b = color.b-40;
  float nr = r;
  float ng = g;
  float nb = b;

  // OUTLINE
  int i = 0;
     if (!reverse)
  { 
  for (i = 0; i < 3; i++)
  {    
    r = color.r-10;
    g = color.g-9;
    b = color.b-40;
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
    }
   r = color.r-10;
   g = color.g-9;
   b = color.b-40;

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
    }
  }

  for (;i < 5; i++)
  {
  //    // OUTLINE 2

    r = color.r+44;
    g = color.g+43;
    b = color.b+11;

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
    }

    r = color.r+44;
    g = color.g+43;
    b = color.b+11;

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
    }
  }
 
// GRADIENT
    int xy;
    r = color.r-32;
    g = color.g-31;
    b = color.b-59;
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
    r = color.r-10;
    g = color.g-9;
    b = color.b-40;
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
    }
   r = color.r-10;
   g = color.g-9;
   b = color.b-40;

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
    }
  }

  for (;i < 5; i++)
  {
  //    // OUTLINE 2

    r = color.r+44;
    g = color.b+43;
    b = color.b+11;

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
    }
   
    r = color.r+44;
    g = color.b+43;
    b = color.b+11;


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
    }
  }
 
  int xy;
  r = color.r-32;
  g = color.g-31;
  b = color.b-59;
  for (int x1 = x+4; x1 < x+w-4; x1++)
  {
    for (int y1 = y+4; y1 < y+h-4; y1++)
    {
      xy = abs(distance(x1, y1, x+w, y+h));
      nr = r + 0.03*xy*log(xy);
      ng = g + 0.03*xy*log(xy);
      nb = b + 0.03*xy*log(xy);
      putpixel(x1, y1, COLOR(nr, ng, nb));
    }
  }
}

void buttonBox(int x, int y, int w, int h,Color color)
{
  setfillstyle(SOLID_FILL, RED);
  bar(x, y, x+w, y+h);
  int r = color.r-10;
  int g = color.g-9;
  int b = color.b-40;
  int nr = r;
  int ng = g;
  int nb = b;

  // OUTLINE
  int i = 0;
  for (i = 0; i < 3; i++)
  {    
   r = color.r-10;
   g = color.g-9;
   b = color.b-40;
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
    }
   r = color.r-10;
   g = color.g-9;
   b = color.b-40;
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
    }
  }

  for (;i < 5; i++)
  {
  //    // OUTLINE 2

    r = color.r+44;
    g = color.b+43;
    b = color.b+11;


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
    }

    r = color.r+44;
    g = color.b+43;
    b = color.b+11;

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
    }
  }

  // GRADIENT
  int xy;
  r = color.r-32;
  g = color.g-31;
  b = color.b-59;
  for (int x1 = x+4; x1 < x+w-4; x1++)
  {
    for (int y1 = y+4; y1 < y+h-4; y1++)
    {
      xy = abs(distance(x1, y1, x, y));
      nr = r + xy*log(xy);
      ng = g + xy*log(xy);
      nb = b + xy*log(xy);
      putpixel(x1, y1, COLOR(nr, ng, nb));
    }
  }
}