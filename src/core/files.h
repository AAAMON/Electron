#ifndef FILES_ELECTRON_H
#define FILES_ELECTRON_H
#include "components.h"
#include "project.h"

//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void loadTheme(int init);
void loadFile(Electron& workspace, bool init);
void saveFile(Electron& workspace, char* fileName);
void newFile(Electron& workspace);
void deleteFile(Electron& workspace);
void getInput(Electron& workspace, char* input);
int charToInt(char* cstring);

#endif