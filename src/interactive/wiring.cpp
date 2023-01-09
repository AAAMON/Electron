#include "wiring.h"
#include "../core/workspace.h"


void wireComponents(Electron& workspace)
{
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    for (int j = 0; j <  workspace.components[i].nrOfBonds; j++)
    {
      
      if (
        isMouseOnWorkspace(workspace) && 
        isMouseOnComponent(workspace, 
        workspace.components[i].x + workspace.components[i].bonds[0][j]*workspace.components[i].size - 10, 
        workspace.components[i].y + workspace.components[i].bonds[1][j]*workspace.components[i].size - 10, 
        workspace.components[i].x + workspace.components[i].bonds[0][j]*workspace.components[i].size + 10, 
        workspace.components[i].y + workspace.components[i].bonds[1][j]*workspace.components[i].size + 10))
      {
        
        setrgbcolor(SELECTION_ACTIVE);
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
          while (ismouseclick(WM_LBUTTONDOWN))
          {        
            cleardevice();
            draw(workspace);
            setrgbcolor(SELECTION_ACTIVE);
            int x1 = workspace.panningX + workspace.components[i].x * workspace.zoom + workspace.components[i].bonds[0][j] * 15*workspace.zoom;
            int y1 = workspace.panningY + workspace.components[i].y * workspace.zoom + workspace.components[i].bonds[1][j] * 15*workspace.zoom;
            //   component.x = workspace.panningX + component.x * workspace.zoom;
            drawCustomWire(workspace, x1, y1, mousex(), mousey(), j, 0);
            rectangle(
            workspace.components[i].x*workspace.zoom + workspace.components[i].bonds[0][j]*workspace.components[i].size*workspace.zoom - 10*workspace.zoom + workspace.panningX, 
            workspace.components[i].y*workspace.zoom + workspace.components[i].bonds[1][j]*workspace.components[i].size*workspace.zoom - 10*workspace.zoom + workspace.panningY, 
            workspace.components[i].x*workspace.zoom + workspace.components[i].bonds[0][j]*workspace.components[i].size*workspace.zoom + 10*workspace.zoom + workspace.panningX, 
            workspace.components[i].y*workspace.zoom + workspace.components[i].bonds[1][j]*workspace.components[i].size*workspace.zoom + 10*workspace.zoom + workspace.panningY); 
            c = activeComponent(workspace);
            b = activeBond(workspace);
            if (c != -1 && b != -1 && c != i)
            {
              setrgbcolor(SELECTION_ACTIVE);
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
          if (b != -1 && c != i)
          {
            workspace.wires[workspace.nrOfWires].points[0].id = i;
            workspace.wires[workspace.nrOfWires].points[0].type = 'c';
            workspace.wires[workspace.nrOfWires].points[0].direction = j;
            workspace.wires[workspace.nrOfWires].points[0].id2 = j;

            workspace.wires[workspace.nrOfWires].points[1].type = 'c';

            workspace.wires[workspace.nrOfWires].nrOfPoints = 2;
            workspace.nrOfWires++;
          }
        }
      }
    }
  }
}

void drawWirePoints(Electron workspace, Wire wire)
{
  for (int i = 0; i < wire.nrOfPoints; i++)
  {
    int x = workspace.components[wire.points[i].id].x*workspace.zoom + workspace.components[wire.points[i].id].bonds[0][wire.points[i].id2]*workspace.zoom * workspace.components[wire.points[i].id].size;
    int y = workspace.components[wire.points[i].id].y*workspace.zoom + workspace.components[wire.points[i].id].bonds[1][wire.points[i].id2]*workspace.zoom * workspace.components[wire.points[i].id].size;
    setrgbcolor(SELECTION_INACTIVE);
    if (wire.points[i].type == 'c')
    {
      rectangle(
          x - 10*workspace.zoom + workspace.panningX,
          y - 10*workspace.zoom + workspace.panningY, 
          x + 10*workspace.zoom + workspace.panningX, 
          y + 10*workspace.zoom + workspace.panningY);
    }
    else
    {
      // had no time to finish wiring,,,
    }
  }
}

void drawWire(Electron& workspace, int i)
{
  setrgbcolor(WIRES);
  int direction1 = workspace.wires[i].points[0].direction;
  int direction2 = workspace.wires[i].points[1].direction;
  int x1 = workspace.components[workspace.wires[i].points[0].id].x*workspace.zoom + workspace.components[workspace.wires[i].points[0].id].bonds[0][workspace.wires[i].points[0].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[0].id].size + workspace.panningX;
  int y1 = workspace.components[workspace.wires[i].points[0].id].y*workspace.zoom + workspace.components[workspace.wires[i].points[0].id].bonds[1][workspace.wires[i].points[0].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[0].id].size + workspace.panningY;
  int x2 = workspace.components[workspace.wires[i].points[1].id].x*workspace.zoom + workspace.components[workspace.wires[i].points[1].id].bonds[0][workspace.wires[i].points[1].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[1].id].size + workspace.panningX;
  int y2 = workspace.components[workspace.wires[i].points[1].id].y*workspace.zoom + workspace.components[workspace.wires[i].points[1].id].bonds[1][workspace.wires[i].points[1].id2]*workspace.zoom * workspace.components[workspace.wires[i].points[1].id].size + workspace.panningY;

  workspace.wires[i].drawPoints[0].x = x1;
  workspace.wires[i].drawPoints[0].y = y1;
  workspace.wires[i].drawPoints[1].x = x2;
  workspace.wires[i].drawPoints[1].y = y2;

  if (!direction1 && !direction2){
    if (x1 > x2)
    {
      workspace.wires[i].drawPoints[2] = workspace.wires[i].drawPoints[1];
      workspace.wires[i].drawPoints[1].x = x1;
      workspace.wires[i].drawPoints[1].y = y1;
      line(x2, y2, x2, y1);
      line(x2, y1, x1, y1);
      workspace.wires[i].nrOfDrawPoints = 3;
    }
    else {
      workspace.wires[i].drawPoints[2] = workspace.wires[i].drawPoints[1];
      workspace.wires[i].drawPoints[1].x = x1;
      workspace.wires[i].drawPoints[1].y = y2;
      workspace.wires[i].nrOfDrawPoints = 3;
      line(x1, y1, x1, y2);
      line(x1, y2, x2, y2);
    }
  }
  else if (direction1 && direction2)
  {
    if (x1 < x2)
    {
      workspace.wires[i].drawPoints[2] = workspace.wires[i].drawPoints[1];
      workspace.wires[i].drawPoints[1].x = x2;
      workspace.wires[i].drawPoints[1].y = y1;
      workspace.wires[i].nrOfDrawPoints = 3;
      line(x2, y2, x2, y1);
      line(x2, y1, x1, y1);
    }
    else {
      workspace.wires[i].drawPoints[2] = workspace.wires[i].drawPoints[1];
      workspace.wires[i].drawPoints[1].x = x1;
      workspace.wires[i].drawPoints[1].y = y2;
      workspace.wires[i].nrOfDrawPoints = 3;
      line(x1, y1, x1, y2);
      line(x1, y2, x2, y2);
    }
  }
  else if (!direction1 && direction2)
  {
    if (x1 < x2 && y1 < y2)
    {
      workspace.wires[i].drawPoints[3] = workspace.wires[i].drawPoints[1];
      workspace.wires[i].drawPoints[1].x = x1;
      workspace.wires[i].drawPoints[1].y = y2 - 50*workspace.zoom;
      workspace.wires[i].drawPoints[2].x = x2;
      workspace.wires[i].drawPoints[2].y = y2 - 50*workspace.zoom;
      workspace.wires[i].nrOfDrawPoints = 4;
      line(x1, y1, x1, y2 - 50*workspace.zoom);
      line(x1, y2 - 50*workspace.zoom, x2, y2 - 50*workspace.zoom);
      line(x2, y2-50*workspace.zoom, x2, y2);
    }
    else if (x1 < x2 && y1 > y2)
    {
      workspace.wires[i].drawPoints[3] = workspace.wires[i].drawPoints[1];
      workspace.wires[i].drawPoints[1].x = x1;
      workspace.wires[i].drawPoints[1].y = y2 + 50*workspace.zoom;
      workspace.wires[i].drawPoints[2].x = x2;
      workspace.wires[i].drawPoints[2].y = y2 + 50*workspace.zoom;
      workspace.wires[i].nrOfDrawPoints = 4;
      line(x1, y1, x1, y2 + 50*workspace.zoom);
      line(x1, y2 + 50*workspace.zoom, x2, y2 + 50*workspace.zoom);
      line(x2, y2 + 50*workspace.zoom, x2, y2);
    }
    else {
      workspace.wires[i].drawPoints[2] = workspace.wires[i].drawPoints[1];
      workspace.wires[i].drawPoints[1].x = x1;
      workspace.wires[i].drawPoints[1].y = y2;
      workspace.wires[i].nrOfDrawPoints = 3;
      line(x1, y1, x1, y2);
      line(x1, y2, x2, y2);
    }
  }
  else
  {
    if (x1 > x2 && y1 < y2)
    {
      workspace.wires[i].drawPoints[3] = workspace.wires[i].drawPoints[1];
      workspace.wires[i].drawPoints[1].x = x1;
      workspace.wires[i].drawPoints[1].y = y2 - 50*workspace.zoom;
      workspace.wires[i].drawPoints[2].x = x2;
      workspace.wires[i].drawPoints[2].y = y2 - 50*workspace.zoom;
      workspace.wires[i].nrOfDrawPoints = 4;
      line(x1, y1, x1, y2 - 50*workspace.zoom);
      line(x1, y2 - 50*workspace.zoom, x2, y2 - 50*workspace.zoom);
      line(x2, y2-50*workspace.zoom, x2, y2);
    }
    else if (x1 > x2 && y1 > y2)
    {
      workspace.wires[i].drawPoints[3] = workspace.wires[i].drawPoints[1];
      workspace.wires[i].drawPoints[1].x = x1;
      workspace.wires[i].drawPoints[1].y = y2 + 50*workspace.zoom;
      workspace.wires[i].drawPoints[2].x = x2;
      workspace.wires[i].drawPoints[2].y = y2 + 50*workspace.zoom;
      workspace.wires[i].nrOfDrawPoints = 4;
      line(x1, y1, x1, y2 + 50*workspace.zoom);
      line(x1, y2 + 50*workspace.zoom, x2, y2 + 50*workspace.zoom);
      line(x2, y2 + 50*workspace.zoom, x2, y2);
    }
    else{
      workspace.wires[i].drawPoints[2] = workspace.wires[i].drawPoints[1];
      workspace.wires[i].drawPoints[1].x = x1;
      workspace.wires[i].drawPoints[1].y = y2;
      workspace.wires[i].nrOfDrawPoints = 3;
      line(x1, y1, x1, y2);
      line(x1, y2, x2, y2);
    }
  }
}

void drawCustomWire(Electron workspace, int x1, int y1, int x2, int y2, bool direction1, bool direction2)
{
  setrgbcolor(WIRES);
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

void drawWires(Electron& workspace)
{
  for (int i = 0; i < workspace.nrOfWires; i++)
  { 
    drawWire(workspace, i);
  }
}

void activateWires(Electron& workspace)
{
  int w = activeWire(workspace);
  if (w != -1 && ismouseclick(WM_LBUTTONDOWN))
  {
    WirePoint aux = workspace.wires[w].points[0];
    workspace.wires[w].points[0] = workspace.wires[w].points[1];
    workspace.wires[w].points[1] = aux;
  }
  if (w != -1 && ismouseclick(WM_RBUTTONDOWN))
  {
    eradicateWire(workspace, w);
  }
}

void eradicateWire(Electron& workspace, int w)
{
  for (int i = w; i < workspace.nrOfWires-1; i++)
    workspace.wires[i] = workspace.wires[i+1];
  workspace.nrOfWires--;
}