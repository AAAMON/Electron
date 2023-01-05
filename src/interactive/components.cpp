#include "components.h"
#include "../core/workspace.h"
#include "wiring.h"

void moveComponents(Electron& workspace)
{
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    while (isMouseOnWorkspace(workspace) && isMouseOnComponent(workspace, workspace.components[i].x-100, workspace.components[i].y-100, workspace.components[i].x+100, workspace.components[i].y+100) 
           && ismouseclick(WM_LBUTTONDOWN))
    { 
      workspace.components[i].x = (mousex() - workspace.panningX)/workspace.zoom;
      workspace.components[i].y = (mousey() - workspace.panningY)/workspace.zoom;
      cleardevice();
      draw(workspace);
      setcolor(RED);
      //workspace.panningX + component.x * workspace.zoom
      rectangle(          
        workspace.components[i].x*workspace.zoom-75*workspace.zoom + workspace.panningX, 
        workspace.components[i].y*workspace.zoom-75*workspace.zoom + workspace.panningY,
        workspace.components[i].x*workspace.zoom+75*workspace.zoom + workspace.panningX, 
        workspace.components[i].y*workspace.zoom+75*workspace.zoom + workspace.panningY);
      refresh();
    }
  }
}

// fix wire overlapping
void activateComponents(Electron& workspace)
{
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    if (isMouseOnComponent(workspace, workspace.components[i].x-100, workspace.components[i].y-100, workspace.components[i].x+100, workspace.components[i].y+100))
    {
      strcpy(workspace.currentMessage, workspace.components[i].name);
    }
  }
  wireComponents(workspace);
  moveComponents(workspace);
}

