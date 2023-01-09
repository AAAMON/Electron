#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "components.h"
#include "project.h"
#include "files.h"


//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


/// B A S I C   O P E R A T I O N S //////////////////////////////////////////

// aux
void loadThisFile(Electron& workspace, std::ifstream& file);
void fileDoesNotExist(Electron& workspace, int operation);
// Loads a file, 1 for initial file (test.file) 0 for other
void loadFile(Electron& workspace, bool init)
{
  char filePath[100] = { "files/" };
  char fileName[100] = { "" };

  // on start-up we always load the same file
  if (init)
    strcpy(fileName, "test");
  else
    getInput(workspace, fileName);

  strcat(filePath, fileName);
  strcat(filePath,  ".file");
  std::ifstream file (filePath);

  if (file)
    loadThisFile(workspace,  file);
  else if (strlen(fileName) == 0)
    return;
  else
    fileDoesNotExist(workspace, LOAD_FILE);
  workspace.input = false;
}

// Saves specified file
void saveFile(Electron& workspace, char* fileName)
{
  char filePath[100] = { "files/" };
  strcat(filePath, fileName);
  strcat(filePath,  ".file");
  std::ofstream f(filePath);

  f << workspace.nrOfComponents << '\n';
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    f << workspace.components[i].name << ' ';
    f << workspace.components[i].x    << ' ';
    f << workspace.components[i].y    << ' ';
    f << workspace.components[i].orientation << '\n';
  }

  // WIRES
  f << workspace.nrOfWires << '\n';
  for (int i = 0; i < workspace.nrOfWires; i++)
  {
    f << workspace.wires[i].nrOfPoints << '\n';
    for (int j = 0; j < workspace.wires[i].nrOfPoints; j++)
    {
      f << workspace.wires[i].points[j].type << ' ';
      f << workspace.wires[i].points[j].id << ' ' << workspace.wires[i].points[j].id2 << '\n';
    }
  }
}

// Creates a new file with .file extension
void newFile(Electron& workspace)
{
  char filePath[100] = { "files/" };
  char fileName[100];
  getInput(workspace, fileName);
  strcat(filePath, fileName);
  strcat(filePath,  ".file");
  std::ofstream f(filePath);

  strcpy(workspace.currentFile, fileName);
  workspace.nrOfComponents = 0;
  workspace.nrOfWires = 0;
  workspace.input = false;
}

// Deletes specified file
void deleteFile(Electron& workspace)
{
  char filePath[100] = { "files/" };
  char fileName[100];
  getInput(workspace, fileName);
  strcat(filePath, fileName);
  strcat(filePath,  ".file");
  std::ifstream file (filePath);

  if (file)
  {
    // if we don't close the file it won't delete
    // i think,,
    file.close();
    remove(filePath);
  }
  else if (strlen(fileName) == 0)
    return;
  else
    fileDoesNotExist(workspace, DELETE_FILE);
  workspace.input = false;
}


// aux
void drawOuterBox();
void drawInnerBox();
void handleInput(char* text, char c, int& i);
// Asks the user for some text input (only lowercase letters)
void getInput(Electron& workspace, char* input)
{
  workspace.input = true;
  draw(workspace);
  drawOuterBox();
  drawInnerBox();
  refresh();
  // iterator for text input cursor
  int i = { 0 };
  // the last key that was pressed
  int c = getch();
  char text[100];

  while (c != KEY_RET)
  {
    // Got to draw it on every frame
    draw(workspace);
    drawOuterBox();
    handleInput(text, c, i);
    drawInnerBox();
    if (i)
      outtextxy(WIDTH/2, HEIGHT/2 - 100, text);

    // next input character
    c = getch();
  }

  strcpy(input, text);
}

// Draws outer box for getInput
void drawOuterBox()
{
  bigBox         (WIDTH/3, HEIGHT/2 - 200, WIDTH/3, 200, 1);
  settextstyle   (SIMPLEX_FONT, HORIZ_DIR, 4);
  settextjustify (CENTER_TEXT,  TOP_TEXT);
  setcolor(COLOR(255,255,255));
  outtextxy(WIDTH/2, HEIGHT/2 - 180, 
    (char*)"Insert file name (only lowercase letters): ");
}

// Draws inner box for getInput
void drawInnerBox()
{
  bigBox    (WIDTH/3 + 140, HEIGHT/2 - 120, WIDTH/3 - 280, 40, 1);
  hollowBox (WIDTH/3 + 150, HEIGHT/2 - 110, WIDTH/3*2-150, HEIGHT/2 - 90);
  setcolor  (COLOR(255,255,255));
  settextstyle   (DEFAULT_FONT, HORIZ_DIR, 1);
  settextjustify (CENTER_TEXT,  CENTER_TEXT);
}

// Either shows an error message or adds character to string
void handleInput(char* text, char c, int& i)
{
  // if it's not a lowercase letter
  if (c < 97 || c > 122)
  {
    settextstyle   (DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(COLOR(255,0,0));
    outtextxy(WIDTH/2, HEIGHT/2 - 30, 
      (char*)"Invalid character! ");
  }
  else
  {
    text[i]   = c;
    text[i+1] = '\0';
    i++;
  }
}

void loadTheme(int init)
{
  char filePath[100] = { "assets/" };
  char fileName[100];

  // on start-up we always load the same file
  if (init==1)
    strcpy(fileName, "classic");
  else
    switch(init)
    {
    case 6:
      strcpy(fileName, "classic");
      break;
    case 7: 
      strcpy(fileName, "cherry");
      break;
    case 8:
      strcpy(fileName, "carbon");
      break;
    case 0:
      strcpy(fileName, "secret");
      break;
    default:
          std::cerr << "ERROR: in function activateMenuBarOption: Invalid function id\n";

    }
  strcat(filePath, fileName);
  strcat(filePath,  ".theme");
  std::ifstream file (filePath);
  int r;
  int g;
  int b;
  int nrOfColors;
  file >> nrOfColors;
  for (int i = 0; i < nrOfColors; i++)
  {
    file >> r >> g >> b;
    setrgbpalette (i, r, g, b);
  }
}

//////////////////////////////////////////////////////////////////////////////
/// A U X ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// Display error message and try again
void fileDoesNotExist(Electron& workspace, int operation)
{
  std::cout << "file does not exist\n";
  bigBox(WIDTH/3, HEIGHT/2 - 200, WIDTH/3, 200, 1);
  settextstyle (SIMPLEX_FONT, HORIZ_DIR, 4);
  settextjustify (CENTER_TEXT, TOP_TEXT);
  setcolor(COLOR(255,255,255));
  outtextxy(WIDTH/2, HEIGHT/2 - 180, (char*)"FILE DOES NOT EXIST");
  refresh();

  // Let the user ponder on their sins for a moment
  delay(1000);

  // What operation to try again
  switch (operation)
  {
  case LOAD_FILE:
    loadFile(workspace, 0);
    break;
  case DELETE_FILE:
    deleteFile(workspace);
    break;
  default:
    std::cerr << "Error: fileDoesNotExist: Unknown file operation boo wtf\n";
    break;
  }
}

// Loads specified file
void loadThisFile(Electron& workspace, std::ifstream& file)
{
  // LOADING COMPONENTS
  // we require 2 text variables for moveComponent
  char text1[30];
  char text2[30];
  file >> workspace.nrOfComponents;
  for (int i = 0; i < workspace.nrOfComponents; i++)
  {
    file >> text1;
    initComponent(workspace.components[i], text1);
    file >> text1;
    file >> text2;
    moveComponent(workspace.components[i], charToInt(text1), charToInt(text2));
    file >> workspace.components[i].orientation;
    for (int r = 0; r < workspace.components[i].orientation; r += 90)
      rotateComponent(workspace.components[i], 1, 0);
  }
  
  char c;
  // WIRES
  file >> workspace.nrOfWires;
  std::cout << workspace.nrOfWires << '\n';
  for (int i = 0; i < workspace.nrOfWires; i++)
  {
    file >> workspace.wires[i].nrOfPoints;
    for (int j = 0; j < workspace.wires[i].nrOfPoints; j++)
    {
      file >> c;
      workspace.wires[i].points[j].type = c;
      file >> workspace.wires[i].points[j].id >> workspace.wires[i].points[j].id2;
      workspace.wires[i].points[j].direction = workspace.wires[i].points[j].id2;
    }
  }
}

// Converts a string number to int
int charToInt(char* cstring)
{
  int nr = 0;
  for (int i = 0; i < (int)strlen(cstring); i++)
  {
    nr = nr*10 + (int)cstring[i] - '0';
  }
  return nr;
}
