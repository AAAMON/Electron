#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "components.h"
#include "project.h"
#include "files.h"

int charToInt(char* cstring)
{
  int nr = 0;
  for (int i = 0; i < (int)strlen(cstring); i++)
  {
    nr = nr*10 + (int)cstring[i] - '0';
  }
  return nr;
}

void loadFile(Electron& workspace, bool init)
{
  char filePath[100] = { "files/" };
  char fileName[100];
  if (init)
  {
    strcpy(fileName, "test");
  }
  else
  {
    getInput(fileName);
  }
  strcat(filePath, fileName);
  strcat(filePath,".file");
  std::ifstream file (filePath);

  if (file)
  {
    // LOADING COMPONENTS
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
    }
  }
  else
  {
    std::cout << "file does not exist\n";
    bigBox(WIDTH/3, HEIGHT/2 - 200, WIDTH/3, 200, 1);
    settextstyle (SIMPLEX_FONT, HORIZ_DIR, 4);
    settextjustify (CENTER_TEXT, TOP_TEXT);
    setcolor(COLOR(255,255,255));
    outtextxy(WIDTH/2, HEIGHT/2 - 180, (char*)"FILE DOES NOT EXIST ");
    refresh();
    delay(1000);
    loadFile(workspace, 0);
  }
}

void saveFile(Electron& workspace, char* fileName)
{
  char filePath[100] = { "files/" };
  strcat(filePath, fileName);
  strcat(filePath,  ".file");
  std::ofstream f(filePath);
  f << workspace.nrOfComponents << '\n';
  for (int i = 0; i < workspace.nrOfComponents; i++)
    f << workspace.components[i].name << ' ' << workspace.components[i].x << ' ' << workspace.components[i].y << '\n';
}

void newFile(Electron& workspace)
{
  char filePath[100] = { "files/" };
  char fileName[100];
  getInput(fileName);
  strcat(filePath, fileName);
  strcat(filePath,  ".file");
  std::ofstream f(filePath);
  strcpy(workspace.currentFile, fileName);
  workspace.nrOfComponents = 0;
}

void deleteFile(Electron& workspace)
{
  char filePath[100]={"files/"};
  char fileName[100];
  getInput(fileName);
  strcat(filePath, fileName);
  strcat(filePath,  ".file");
  remove(filePath);
}
void getInput(Electron workspace, char* input);
void deleteFile(Electron& workspace)
{
  char filePath[100]={"files/"};
  char fileName[100];
  getInput(workspace, fileName);
  strcat(filePath, fileName);
  strcat(filePath,  ".file");
  remove(filePath);
}

void printFile(Electron electron)
{
  std::cout << electron.nrOfComponents;
  for (int i = 0; i < electron.nrOfComponents; i++)
    std::cout << electron.components[i].name << ' ' << electron.components[i].x << ' ' << electron.components[i].y << '\n';
}

void getInput(char* input)
{
  bigBox(WIDTH/3, HEIGHT/2 - 200, WIDTH/3, 200, 1);
  settextstyle (SIMPLEX_FONT, HORIZ_DIR, 4);
  settextjustify (CENTER_TEXT, TOP_TEXT);
  setcolor(COLOR(255,255,255));
  outtextxy(WIDTH/2, HEIGHT/2 - 180, (char*)"Insert file name (only lowercase letters): ");
      bigBox(WIDTH/3 + 140, HEIGHT/2 - 120, WIDTH/3 - 280, 40, 1);
    hollowBox(WIDTH/3 + 150, HEIGHT/2 - 110, WIDTH/3*2-150, HEIGHT/2 - 90);
  int i = 0;
  int c = getch();
  char text[100];

  while (c != KEY_RET)
  {
    bigBox(WIDTH/3, HEIGHT/2 - 200, WIDTH/3, 200, 1);


    settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
    settextjustify (CENTER_TEXT, CENTER_TEXT);
    if (c < 97 || c > 122)
    {
      setcolor(COLOR(255,0,0));
      outtextxy(WIDTH/2, HEIGHT/2 - 30, (char*)"Invalid character! ");
    }
    else
    {
      bigBox(WIDTH/3, HEIGHT/2 - 200, WIDTH/3, 200, 1);
      text[i] = c;
      text[i+1] = '\0';
      i++;
    }
    settextstyle (SIMPLEX_FONT, HORIZ_DIR, 4);
    settextjustify (CENTER_TEXT, TOP_TEXT);
    setcolor(COLOR(255,255,255));
    outtextxy(WIDTH/2, HEIGHT/2 - 180, (char*)"Insert file name (only lowercase letters): ");

    bigBox(WIDTH/3 + 140, HEIGHT/2 - 120, WIDTH/3 - 280, 40, 1);
    hollowBox(WIDTH/3 + 150, HEIGHT/2 - 110, WIDTH/3*2-150, HEIGHT/2 - 90);
    setcolor(COLOR(255,255,255));
    settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
    settextjustify (CENTER_TEXT, CENTER_TEXT);
    outtextxy(WIDTH/2, HEIGHT/2 - 100, text);
    c = getch();
  }
  strcpy(input, text);
}