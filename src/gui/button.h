#ifndef BUTTON_ELECTRON_H
#define BUTTON_ELECTRON_H

struct Button
{
  char label[100];

  // drawing info
  // coordonates refer to center of button
  int x;
  int y;
  int width;
  int size;

  // pointer to a function
  void (*onClick)(); 
};

void createButton(Button &button, int x, int y, const char* label, int size, void (*onClick)());
void drawButton(Button button);
void activateButton(Button button);
bool IsMouseOnButton(Button button);
void bCredits();
void bVoid();

#endif