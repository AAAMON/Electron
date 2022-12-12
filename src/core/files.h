#include "components.h"
#ifndef FILES_ELECTRON_H
#define FILES_ELECTRON_H

void loadFile(char* fileName, Electron& electron);
void saveFile(char* fileName);
void newFile(char* fileName);

void printFile(Electron electron);

#endif