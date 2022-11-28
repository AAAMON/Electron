#ifndef BUTTON_ELECTRON_H
#define BUTTON_ELECTRON_H

struct Button
{
  // coordonates of the button (top left corner)
  int x;
  int y;

  char label[100];

  // will determine scaling
  int size;

  // pointer to a function
  void (*onClick)(Button); 
};

void createButton(Button button, int x, int y, const char* label, int size, void (*onClick)(Button));
void drawButton(Button button);
void bStart(Button);

#endif