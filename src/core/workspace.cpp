#include "workspace.h"


void activateZooming(Electron& workspace)
{
  int x = mousex();
  while (workspace.menu.show && isMouseOnBox(workspace.menu.width, 24, WIDTH, HEIGHT) && ismouseclick(WM_RBUTTONDOWN) && ismouseclick(WM_MBUTTONDOWN))
  {
    if (mousex() - x > 0)
    {
      workspace.zoom += 0.007;
      workspace.panningX -= 5;
      workspace.panningY -= 2.5;
    }
    if (mousex() - x < 0)
    {
      workspace.zoom -= 0.007;
      workspace.panningX += 5;
      workspace.panningY += 2.5;
    }
    cleardevice();
    draw(workspace);
    refresh();
  }
  while (!workspace.menu.show && isMouseOnBox(workspace.menu.buttonWidth, 24, WIDTH, HEIGHT) && ismouseclick(WM_RBUTTONDOWN) && ismouseclick(WM_MBUTTONDOWN))
  {
    if (mousex() - x > 0)
    {
      workspace.zoom += 0.007;
      workspace.panningX -= 5;
      workspace.panningY -= 2.5;
    }
    if (mousex() - x < 0)
    {
      workspace.zoom -= 0.007;
      workspace.panningX += 5;
      workspace.panningY += 2.5;
    }
    cleardevice();
    draw(workspace);
    refresh();
  }
}

void activatePanning(Electron& workspace)
{
  int panPrevX = workspace.panningX;
  int panPrevY = workspace.panningY;
  int x = mousex();
  int y = mousey();
  while (workspace.menu.show && isMouseOnBox(workspace.menu.width, 24, WIDTH, HEIGHT) && ismouseclick(WM_MBUTTONDOWN)  && !ismouseclick(WM_RBUTTONDOWN))
  {
    workspace.panningX = panPrevX + mousex() - x;
    workspace.panningY = panPrevY + mousey() - y;
    cleardevice();
    draw(workspace);
    refresh();
  }
  while (!workspace.menu.show && isMouseOnBox(workspace.menu.buttonWidth, 24, WIDTH, HEIGHT) && ismouseclick(WM_MBUTTONDOWN)  && !ismouseclick(WM_RBUTTONDOWN))
  {

    workspace.panningX = panPrevX + mousex() - x;
    workspace.panningY = panPrevY + mousey() - y;
    cleardevice();
    draw(workspace);
    refresh();
  }
}

bool isMouseOnWorkspace(Electron workspace)
{
  if (workspace.menu.show)
  {
    if (isMouseOnBox(workspace.menu.width, 0, WIDTH, HEIGHT))
      return YEAH;
    return NOPE;
  }
  else
  {
    if (isMouseOnBox(workspace.menu.buttonWidth, 0, WIDTH, HEIGHT))
      return YEAH;
    return NOPE;
  }
}

int activeComponent(Electron workspace)
{
  int c = -1;
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    if (isMouseOnComponent(workspace, workspace.components[i].x-100, workspace.components[i].y-100, workspace.components[i].x+100, workspace.components[i].y+100))
    {
      c = i;
    }
  }
  return c;
}

int activeBond(Electron workspace)
{
  int b = -1;
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
        b = j;
      }
    }
  }
  return b;
}

int activeWire(Electron workspace)
{
  int w = -1;
  for (int i = 0; i < workspace.nrOfWires; i++)
  {
    if (isMouseOnWire(workspace, i) && isMouseOnWorkspace(workspace))
    {
      w = i;
    }
  }
  return w;
}

void drawWorkspaceComponent(Electron workspace, Component component)
{
  component.x = workspace.panningX + component.x * workspace.zoom;
  component.y = workspace.panningY + component.y * workspace.zoom;
  component.size = 15*workspace.zoom;
  drawComponent(component);
}

bool isMouseOnWire(Electron workspace, int i)
{
  bool ok = false;
  int x1;
  int y1;
  int x2;
  int y2;
  // checking each individual line
  for (int j = 0; j < workspace.wires[i].nrOfDrawPoints - 1; j++)
  {
    if (workspace.wires[i].drawPoints[j].x < workspace.wires[i].drawPoints[j+1].x)
    {
      x1 = workspace.wires[i].drawPoints[j].x;
      x2 = workspace.wires[i].drawPoints[j+1].x;
    }
    else
    {
      x1 = workspace.wires[i].drawPoints[j+1].x;
      x2 = workspace.wires[i].drawPoints[j].x;
    }
    if (workspace.wires[i].drawPoints[j].y < workspace.wires[i].drawPoints[j+1].y)
    {
      y1 = workspace.wires[i].drawPoints[j].y;
      y2 = workspace.wires[i].drawPoints[j+1].y;
    }
    else
    {
      y1 = workspace.wires[i].drawPoints[j+1].y;
      y2 = workspace.wires[i].drawPoints[j].y;
    }
    if (mousex() > x1-10 && mousex() < x2+10 && mousey() > y1-10 && mousey() < y2+10)
      ok = true;
  }
  return ok;
}

bool isMouseOnComponent(Electron workspace, int x1, int y1, int x2, int y2)
{
  if ((mousex() - workspace.panningX)/workspace.zoom > x1 && (mousex() - workspace.panningX)/workspace.zoom < x2)
    if ((mousey() - workspace.panningY)/workspace.zoom > y1 && (mousey() - workspace.panningY)/workspace.zoom < y2)
      {
        return YEAH;
      }
  return NOPE;
}