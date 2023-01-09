#include "components.h"
#include "../core/workspace.h"
#include "wiring.h"

void moveComponents(Electron& workspace)
{
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    while (isMouseOnWorkspace(workspace) && isMouseOnComponent(workspace, workspace.components[i].x-55, workspace.components[i].y-55, workspace.components[i].x+55, workspace.components[i].y+55) 
           && ismouseclick(WM_LBUTTONDOWN))
    { 
      workspace.components[i].x = (mousex() - workspace.panningX)/workspace.zoom;
      workspace.components[i].y = (mousey() - workspace.panningY)/workspace.zoom;
      cleardevice();
      draw(workspace);
      setrgbcolor(SELECTION_ACTIVE);
      //workspace.panningX + component.x * workspace.zoom
      rectangle(          
        workspace.components[i].x*workspace.zoom-55*workspace.zoom + workspace.panningX, 
        workspace.components[i].y*workspace.zoom-55*workspace.zoom + workspace.panningY,
        workspace.components[i].x*workspace.zoom+55*workspace.zoom + workspace.panningX, 
        workspace.components[i].y*workspace.zoom+55*workspace.zoom + workspace.panningY);
      refresh();
    }
  }
}

void activateComponents(Electron& workspace)
{
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    if (
      isMouseOnWorkspace(workspace) && 
      isMouseOnComponent(workspace, workspace.components[i].x-55, workspace.components[i].y-55, workspace.components[i].x+55, workspace.components[i].y+55))
    {
      setrgbcolor(SELECTION_INACTIVE);
      rectangle(          
        workspace.components[i].x*workspace.zoom-55*workspace.zoom + workspace.panningX, 
        workspace.components[i].y*workspace.zoom-55*workspace.zoom + workspace.panningY,
        workspace.components[i].x*workspace.zoom+55*workspace.zoom + workspace.panningX, 
        workspace.components[i].y*workspace.zoom+55*workspace.zoom + workspace.panningY);
      strcpy(workspace.currentMessage, workspace.components[i].name);
            // remove
      if (ismouseclick(WM_RBUTTONDOWN))
      {
        if (workspace.components[i].orientation == 270)
          workspace.components[i].orientation = 0;
        else
        {
          workspace.components[i].orientation += 90;
        }
        rotateComponent(workspace.components[i], 1, 0);
        delay(200);
      }
    }
  }
  wireComponents(workspace);
  moveComponents(workspace);
}

