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

void drawWorkspaceComponent(Electron workspace, Component component)
{
  component.x = workspace.panningX + component.x * workspace.zoom;
  component.y = workspace.panningY + component.y * workspace.zoom;
  component.size = 15*workspace.zoom;
  drawComponent(component);
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