#include <iostream>
#include <fstream>
#include <cstring>
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

void loadFile(char* fileName, Electron& electron)
{
  char filePath[100] = { "files/" };
  strcat(filePath, fileName);
  strcat(filePath,".file");
  std::ifstream file (filePath);

  // LOADING COMPONENTS
  char text1[30];
  char text2[30];
  file >> electron.nrOfComponents;
  for (int i = 0; i < electron.nrOfComponents; i++)
  {
    file >> text1;
    initComponent(electron.components[i], text1);
    file >> text1;
    file >> text2;
    moveComponent(electron.components[i], charToInt(text1), charToInt(text2));
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

void newFile(Electron& workspace, char* fileName)
{
  char filePath[100] = { "files/" };
  strcat(filePath, fileName);
  strcat(filePath,  ".file");
  std::ofstream f(filePath);
  strcpy(workspace.currentFile, fileName);
}

void printFile(Electron electron)
{
  std::cout << electron.nrOfComponents;
  for (int i = 0; i < electron.nrOfComponents; i++)
    std::cout << electron.components[i].name << ' ' << electron.components[i].x << ' ' << electron.components[i].y << '\n';
}