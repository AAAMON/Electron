#include <iostream>
#include <graphics.h>
#include <cmath>
#include "button.h"
#include "boxes.h"
#include "../core/project.h"
#include "../core/files.h"


//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// Initialises the button
void createButton(Button &button, int x, int y, const char* label, int size, void (*onClick)())
{
  button.x = x;
  button.y = y;
  strcpy(button.label, label);
  button.size = size;
  button.onClick = onClick;

  // funky formula that sets the button width based on label and button size
  // it's put in a variable so this thing doesn't need to be rewriten
  button.width = (pow(1.11, button.size)*log(button.size)*(int)strlen(button.label)*3.6+15) * 2;
  // button height is easy to calculate so we wont use a variable for it
}

// Imediately draws the button on screen
void drawButton(Button button)
{
  // box
  setcolor(COLOR(0, 0, 0));
  setalpha (getcolor (), 1); // has weird behaviour,,,
  setfillstyle (SOLID_FILL, getcolor ());
  bar(
      button.x - button.width/2, button.y - 5*button.size, 
      button.x + button.width/2, button.y + 8*button.size
     );
  
  // label
  settextstyle  (GOTHIC_FONT, HORIZ_DIR, button.size);
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  // setcolor      (COLOR(1, 0, 26));
  setcolor(BLACK);
  outtextxy(button.x+2, button.y, button.label);
  outtextxy(button.x+2, button.y+1, button.label);
  setcolor(WHITE);
  outtextxy(button.x, button.y, button.label);

  // so the START button on the title screen is a bit wider
  if (button.size == 9)
    outtextxy(button.x+1, button.y, button.label);
  refresh();
}

// replace this with isMouseOnBox
// Checks if the mouse if hovering over the button
bool IsMouseOnButton(Button button)
{
  if (mousex() > button.x - button.width/2 && mousex() < button.x + button.width/2)
    if (mousey() > button.y - 5*button.size && mousey() < button.y + 8*button.size)
      {
        return YEAH;
      }
  return NOPE;
}

// Activates the button if it is left-clicked 
// (put it in a loop)
void activateButton(Button button)
{
  if (ismouseclick(WM_LBUTTONDOWN) && IsMouseOnButton(button))
    button.onClick(); 
}



//////////////////////////////////////////////////////////////////////////////
/// O N - C L I C K   F U N C T I O N S //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// Void function for button (does nothing)
void bVoid()
{
  ;
}

// Button function for showing the credits
void bCredits()
{
  // abandoned, rest in peace
}


//////////////////////////////////////////////////////////////////////////////
/// D E B U G ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

