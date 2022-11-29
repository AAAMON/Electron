#ifndef BUTTON_ELECTRON_H
#define BUTTON_ELECTRON_H

struct Button
{
  // coordonates of the button (top left corner)
  int x;
  int y;
  int width;

  char label[100];

  // will determine scaling
  int size;

  // pointer to a function
  void (*onClick)(); 
};
void createButton(Button &button, int x, int y, const char* label, int size, void (*onClick)());
void drawButton(Button button);
void activateButton(Button button);
bool IsMouseOnButton(Button button);
void bStart();
void bVoid();

#endif