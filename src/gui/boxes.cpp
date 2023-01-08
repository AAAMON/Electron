#include <iostream>
#include <cmath>
#include <graphics.h>
#include "boxes.h"



int distance(int x1, int y1, int x2, int y2)
{
  int dis = { 0 };
  dis += (x1 - x2) * (x1 - x2); 
  dis += (y1 - y2) * (y1 - y2); 
  dis = sqrt(dis);
  return dis;
}

void bigBox(int x, int y, int w, int h, int size)
{
  // SOLID FILL
  if(RED_VALUE(0)==0)
  setfillstyle(SOLID_FILL, COLOR(138,132,155));
  else
  setfillstyle(SOLID_FILL, COLOR(255,255,102));
  bar(x, y, x + w, y + h);
  int i = 0;
  // LEFT & TOP
  // OUTLINE 1
    if(RED_VALUE(0)==0)
  setcolor(COLOR(86, 82, 98));
  else
    setcolor(COLOR(247, 247, 78));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    //rectangle(x+i, y+i, x + w-i, y + h-i);
      if(RED_VALUE(0)==0)
    setcolor(COLOR(36, 35, 39));
    else
    setcolor(COLOR(198,198,48));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }


  // 2
  if(RED_VALUE(0)==0)
  setcolor(COLOR(143, 137, 163));
  else
   setcolor(COLOR(255,255,78));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    if(RED_VALUE(0)==0)
    setcolor(COLOR(69, 66, 77));
    else
    setcolor(COLOR(246,246,81));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }

  // 3
     if(RED_VALUE(0)==0)
  setcolor(COLOR(60, 57, 66));
  else
    setcolor(COLOR(232,232,85));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    if(RED_VALUE(0)==0)
    setcolor(COLOR(92, 88, 103));
    else
     setcolor(COLOR(226,226,88));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }

  // DARK LINE
   if(RED_VALUE(0)==0)
  setcolor(COLOR(37, 35, 41));
  else
    setcolor(COLOR(198,198,48));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
       if(RED_VALUE(0)==0)
    setcolor(COLOR(149, 143, 169));
    else
     setcolor(COLOR(255,255,78));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
     if(RED_VALUE(0)==0)
      setcolor(COLOR(37, 35, 41));
      else
      setcolor(COLOR(198,198,48));
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);  
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }

  // 5
     if(RED_VALUE(0)==0)
  setcolor(COLOR(87, 83, 99));
  else
  setcolor(COLOR(255,255,85));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    if(RED_VALUE(0)==0)
    setcolor(COLOR(37, 35, 41));
    else
    setcolor(COLOR(198,198,48));
    line(x+w-i, y+h-i, x+w-i, y+i);
    line(x+w-i, y+h-i, x+i, y+h-i);
    i++;
  }
  // 6
    if(RED_VALUE(0)==0)
  setcolor(COLOR(145, 139, 164));
  else
   setcolor(COLOR(255,255,78));
  for (int z = 0; z < size; z++)
  {
    line(x+i, y+i, x+w-i, y+i);
    line(x+i, y+i, x+i, y+h-i);
    i++;
  }

int r,g,b;
  if(RED_VALUE(0)==0)
{
   r = 132;
  g = 126;
   b = 149;
}
else
{
   r=250,g=250,b=133;
}
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

void smallBox(int x, int y, int x2, int y2)
{
  // SOLID FILL
  if(RED_VALUE(0)==0)
  setfillstyle(SOLID_FILL, COLOR(138,132,155));
  else
  setfillstyle(SOLID_FILL,COLOR(255,255,102));
  bar(x, y, x2, y2);
if(RED_VALUE(0)==0)
  setcolor(COLOR(86, 82, 98));
  else 
  setcolor(COLOR(247,247,78));
  rectangle(x, y, x2, y2);
  if(RED_VALUE(0)==0)
  setcolor(COLOR(143, 137, 163));
  else
  setcolor(COLOR(255,255,78));
  rectangle(x, y, x2, y2);
}

void hollowBox(int x, int y, int x2, int y2)
{
  int r,g,b;
    if(RED_VALUE(0)==0)
  {r = 87;
   g = 87;
   b = 87;}
  else
  {
   r=233,g=233,b=80;
  }
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

void longButtonBox(int x, int y, int w, int h, bool reverse)
{

  setfillstyle(SOLID_FILL, RED);
  bar(x, y, x+w, y+h);
  int r,g,b;
  if(RED_VALUE(0)==0)
   {r = 128;
   g = 123;
   b = 115;
   }
   else
   {r=255,g=135,b=143;
   }
  float nr = r;
  float ng = g;
  float nb = b;

  // OUTLINE
  int i = 0;
     if (!reverse)
  { 
  for (i = 0; i < 3; i++)
  {    
     if(RED_VALUE(0)==0)
   {r = 128;
   g = 123;
   b = 115;
   }
   else
   {r=255,g=135,b=143;
   }
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
  if(RED_VALUE(0)==0)
   {r = 128;
   g = 123;
   b = 115;
   }
   else
   {r=255,g=135,b=143;
   }

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
 if(RED_VALUE(0)==0)
    {r = 182;
    g = 175;
    b = 166;}
    else
    {
      r=255, g=183,b=188;
    }

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

 if(RED_VALUE(0)==0)
    {r = 182;
    g = 175;
    b = 166;}
    else
    {
      r=255, g=183,b=188;
    }

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
     if(RED_VALUE(0)==0)
    {r = 106;
    g = 101;
    b = 96;}
    else
    {
      r=255;
      g=129;
      b=138;
    }
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
    if(RED_VALUE(0)==0)
   {r = 128;
   g = 123;
   b = 115;
   }
   else
   {r=255,g=135,b=143;
   }

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
  if(RED_VALUE(0)==0)
   {r = 128;
   g = 123;
   b = 115;
   }
   else
   {r=255,g=135,b=143;
   }

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

 if(RED_VALUE(0)==0)
    {r = 182;
    g = 175;
    b = 166;}
    else
    {
      r=255, g=183,b=188;
    }

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
 if(RED_VALUE(0)==0)
    {r = 182;
    g = 175;
    b = 166;}
    else
    {
      r=255, g=183,b=188;
    }

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
     if(RED_VALUE(0)==0)
    {r = 106;
    g = 101;
    b = 96;}
    else
    {
      r=255;
      g=129;
      b=138;
    }
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

void buttonBox(int x, int y, int w, int h)
{
  setfillstyle(SOLID_FILL, RED);
  bar(x, y, x+w, y+h);
  int r,g,b;
  if(RED_VALUE(0)==0)
   {r = 128;
   g = 123;
   b = 115;
   }
   else
   {r=255,g=135,b=143;
   }
  int nr = r;
  int ng = g;
  int nb = b;

  // OUTLINE
  int i = 0;
  for (i = 0; i < 3; i++)
  {    
  if(RED_VALUE(0)==0)
   {r = 128;
   g = 123;
   b = 115;
   }
   else
   {r=255,g=135,b=143;
   }
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
  if(RED_VALUE(0)==0)
   {r = 128;
   g = 123;
   b = 115;
   }
   else
   {r=255,g=135,b=143;
   }
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

 if(RED_VALUE(0)==0)
    {r = 182;
    g = 175;
    b = 166;}
    else
    {
      r=255, g=183,b=188;
    }

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

 if(RED_VALUE(0)==0)
    {r = 182;
    g = 175;
    b = 166;}
    else
    {
      r=255, g=183,b=188;
    }


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
     if(RED_VALUE(0)==0)
    {r = 106;
    g = 101;
    b = 96;}
    else
    {
      r=255;
      g=129;
      b=138;
    }
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