#include "wiring.h"
#include "../core/workspace.h"

void wireComponents(Electron& workspace)
{
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    for (int j = 0; j <  workspace.components[i].nrOfBonds; j++)
    {
      
      if (isMouseOnComponent(workspace, 
        workspace.components[i].x + workspace.components[i].bonds[0][j]*workspace.components[i].size - 10, 
        workspace.components[i].y + workspace.components[i].bonds[1][j]*workspace.components[i].size - 10, 
        workspace.components[i].x + workspace.components[i].bonds[0][j]*workspace.components[i].size + 10, 
        workspace.components[i].y + workspace.components[i].bonds[1][j]*workspace.components[i].size + 10))
      {
        setcolor(COLOR(0,255,0));
        rectangle(
          workspace.components[i].x*workspace.zoom + workspace.components[i].bonds[0][j]*workspace.components[i].size*workspace.zoom - 10*workspace.zoom + workspace.panningX, 
          workspace.components[i].y*workspace.zoom + workspace.components[i].bonds[1][j]*workspace.components[i].size*workspace.zoom - 10*workspace.zoom + workspace.panningY, 
          workspace.components[i].x*workspace.zoom + workspace.components[i].bonds[0][j]*workspace.components[i].size*workspace.zoom + 10*workspace.zoom + workspace.panningX, 
          workspace.components[i].y*workspace.zoom + workspace.components[i].bonds[1][j]*workspace.components[i].size*workspace.zoom + 10*workspace.zoom + workspace.panningY);
        strcpy(workspace.currentMessage, "add wire");
        if (ismouseclick(WM_LBUTTONDOWN))
        {
          int c;
          int b;
          workspace.wires[workspace.nrOfWires].points[0].id = -1;
          while (ismouseclick(WM_LBUTTONDOWN))
          {        
            cleardevice();
            draw(workspace);
            setcolor(COLOR(0,255,0));
            int x1 = workspace.panningX + workspace.components[i].x * workspace.zoom + workspace.components[i].bonds[0][j] * 15*workspace.zoom;
            int y1 = workspace.panningY + workspace.components[i].y * workspace.zoom + workspace.components[i].bonds[1][j] * 15*workspace.zoom;
            //   component.x = workspace.panningX + component.x * workspace.zoom;
            drawWire(workspace, x1, y1, mousex(), mousey(), j, 0);
            rectangle(
            workspace.components[i].x*workspace.zoom + workspace.components[i].bonds[0][j]*workspace.components[i].size*workspace.zoom - 10*workspace.zoom + workspace.panningX, 
            workspace.components[i].y*workspace.zoom + workspace.components[i].bonds[1][j]*workspace.components[i].size*workspace.zoom - 10*workspace.zoom + workspace.panningY, 
            workspace.components[i].x*workspace.zoom + workspace.components[i].bonds[0][j]*workspace.components[i].size*workspace.zoom + 10*workspace.zoom + workspace.panningX, 
            workspace.components[i].y*workspace.zoom + workspace.components[i].bonds[1][j]*workspace.components[i].size*workspace.zoom + 10*workspace.zoom + workspace.panningY); 
            c = activeComponent(workspace);
            b = activeBond(workspace);
            if (c != -1 && b != -1 && c != i)
            {
              setcolor(COLOR(0,255,0));
              workspace.wires[workspace.nrOfWires].points[1].id = c;
              workspace.wires[workspace.nrOfWires].points[1].id2 = b;
              workspace.wires[workspace.nrOfWires].points[1].direction = b;
              rectangle(
                workspace.components[c].x*workspace.zoom + workspace.components[c].bonds[0][b]*workspace.components[c].size*workspace.zoom - 10*workspace.zoom + workspace.panningX, 
                workspace.components[c].y*workspace.zoom + workspace.components[c].bonds[1][b]*workspace.components[c].size*workspace.zoom - 10*workspace.zoom + workspace.panningY, 
                workspace.components[c].x*workspace.zoom + workspace.components[c].bonds[0][b]*workspace.components[c].size*workspace.zoom + 10*workspace.zoom + workspace.panningX, 
                workspace.components[c].y*workspace.zoom + workspace.components[c].bonds[1][b]*workspace.components[c].size*workspace.zoom + 10*workspace.zoom + workspace.panningY);
            }
            refresh();
          }
          if (b != -1)
          {
            workspace.wires[workspace.nrOfWires].points[0].id = i;
            workspace.wires[workspace.nrOfWires].points[0].type = 'c';
            workspace.wires[workspace.nrOfWires].points[0].direction = j;
            workspace.wires[workspace.nrOfWires].points[0].id2 = j;

            workspace.wires[workspace.nrOfWires].points[1].type = 'c';

            workspace.wires[workspace.nrOfWires].nrOfPoints = 2;
            setUpWirePoints(workspace, workspace.nrOfWires);
            workspace.nrOfWires++;
          }
        }
      }
    }
  }
}

void setUpWirePoints(Electron& workspace, int id)
{
  // the number of points is dictated by the length of the wire
  int length = { 0 };
  length += abs(workspace.components[workspace.wires[id].points[0].id].x - workspace.components[workspace.wires[id].points[1].id].x);
  length += abs(workspace.components[workspace.wires[id].points[0].id].y - workspace.components[workspace.wires[id].points[1].id].y);

  // how many 20px segments we have
  length /= 20;
  // the first and last one
  length -= 6;
  int full = length / 3;
  int rest = length % 3;
  workspace.wires[id].nrOfPoints = 2 + full;
  for (int i = 2; i < workspace.wires[id].nrOfPoints; i++)
  {
    // move the last point
    workspace.wires[id].points[i] = workspace.wires[id].points[i-1];

    workspace.wires[id].points[i-1].type = 'n';
    workspace.wires[id].points[i-1].x = 60 * (i - 1);
  }
}

void drawWirePoints(Electron workspace, Wire wire)
{
  for (int i = 0; i < wire.nrOfPoints; i++)
  {
    setcolor(COLOR(0, 100, 100));
    if (wire.points[i].type == 'c')
    {
      rectangle(
          workspace.components[wire.points[i].id].x*workspace.zoom + workspace.components[wire.points[i].id].bonds[0][wire.points[i].id2]*workspace.zoom * workspace.components[wire.points[i].id].size - 10*workspace.zoom + workspace.panningX,
          workspace.components[wire.points[i].id].y*workspace.zoom + workspace.components[wire.points[i].id].bonds[1][wire.points[i].id2]*workspace.zoom * workspace.components[wire.points[i].id].size - 10*workspace.zoom + workspace.panningY, 
          workspace.components[wire.points[i].id].x*workspace.zoom + workspace.components[wire.points[i].id].bonds[0][wire.points[i].id2]*workspace.zoom * workspace.components[wire.points[i].id].size + 10*workspace.zoom + workspace.panningX, 
          workspace.components[wire.points[i].id].y*workspace.zoom + workspace.components[wire.points[i].id].bonds[1][wire.points[i].id2]*workspace.zoom * workspace.components[wire.points[i].id].size + 10*workspace.zoom + workspace.panningY);
    }
    else
    {

    }
  }
}

void drawWire(Electron workspace, int x1, int y1, int x2, int y2, bool direction1, bool direction2)
{
  // int direction1 = workspace.wires[i].points[0].direction;
  // int direction2 = workspace.wires[i].points[1].direction;
  // int x1;
  // int y1;
  // int x2;
  // int y2;


  // if (mouse)
  // {
  //   x1 = i;
  //   y1 = mouse;
  //   x2 = mousex();
  //   y2 = mousey();
  // }
  // else
  // {
  //   x1 = workspace.components[workspace.wires[i].points[0].id].x*workspace.zoom + workspace.components[workspace.wires[i].points[0].id].bonds[0][workspace.wires[i].points[0].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[0].id].size + workspace.panningX;
  //   y1 = workspace.components[workspace.wires[i].points[0].id].y*workspace.zoom + workspace.components[workspace.wires[i].points[0].id].bonds[1][workspace.wires[i].points[0].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[0].id].size + workspace.panningY;
  //   x2 = workspace.components[workspace.wires[i].points[1].id].x*workspace.zoom + workspace.components[workspace.wires[i].points[1].id].bonds[0][workspace.wires[i].points[1].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[1].id].size + workspace.panningX;
  //   y2 = workspace.components[workspace.wires[i].points[1].id].y*workspace.zoom + workspace.components[workspace.wires[i].points[1].id].bonds[1][workspace.wires[i].points[1].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[1].id].size + workspace.panningY;
  // }

  setcolor(COLOR(0,0,255));
  if (!direction1 && !direction2){
    if (x1 > x2)
    {
      line(x2, y2, x2, y1);
      line(x2, y1, x1, y1);
    }
    else {
      line(x1, y1, x1, y2);
      line(x1, y2, x2, y2);
    }
  }
  else if (direction1 && direction2)
  {
    if (x1 < x2)
    {
      line(x2, y2, x2, y1);
      line(x2, y1, x1, y1);
    }
    else {
      line(x1, y1, x1, y2);
      line(x1, y2, x2, y2);
    }
  }
  else if (!direction1 && direction2)
  {
    if (x1 < x2 && y1 < y2)
    {
      line(x1, y1, x1, y2 - 50*workspace.zoom);
      line(x1, y2 - 50*workspace.zoom, x2, y2 - 50*workspace.zoom);
      line(x2, y2-50*workspace.zoom, x2, y2);
    }
    else if (x1 < x2 && y1 > y2)
    {
      line(x1, y1, x1, y2 + 50*workspace.zoom);
      line(x1, y2 + 50*workspace.zoom, x2, y2 + 50*workspace.zoom);
      line(x2, y2 + 50*workspace.zoom, x2, y2);
    }
        else {
      line(x1, y1, x1, y2);
      line(x1, y2, x2, y2);
    }
  }
  else
  {
    if (x1 > x2 && y1 < y2)
    {
      line(x1, y1, x1, y2 - 50*workspace.zoom);
      line(x1, y2 - 50*workspace.zoom, x2, y2 - 50*workspace.zoom);
      line(x2, y2-50*workspace.zoom, x2, y2);
    }
    else if (x1 > x2 && y1 > y2)
    {
      line(x1, y1, x1, y2 + 50*workspace.zoom);
      line(x1, y2 + 50*workspace.zoom, x2, y2 + 50*workspace.zoom);
      line(x2, y2 + 50*workspace.zoom, x2, y2);
    }
    else{
      line(x1, y1, x1, y2);
      line(x1, y2, x2, y2);
    }
  }
}

void drawWires(Electron workspace)
{
  for (int i = 0; i < workspace.nrOfWires; i++)
  { 
    int x1 = workspace.components[workspace.wires[i].points[0].id].x*workspace.zoom + workspace.components[workspace.wires[i].points[0].id].bonds[0][workspace.wires[i].points[0].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[0].id].size + workspace.panningX;
    int y1 = workspace.components[workspace.wires[i].points[0].id].y*workspace.zoom + workspace.components[workspace.wires[i].points[0].id].bonds[1][workspace.wires[i].points[0].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[0].id].size + workspace.panningY;
    int x2 = workspace.components[workspace.wires[i].points[1].id].x*workspace.zoom + workspace.components[workspace.wires[i].points[1].id].bonds[0][workspace.wires[i].points[1].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[1].id].size + workspace.panningX;
    int y2 = workspace.components[workspace.wires[i].points[1].id].y*workspace.zoom + workspace.components[workspace.wires[i].points[1].id].bonds[1][workspace.wires[i].points[1].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[1].id].size + workspace.panningY;
    drawWire(workspace, x1, y1, x2, y2, workspace.wires[i].points[0].direction, workspace.wires[i].points[1].direction);
  }
}
