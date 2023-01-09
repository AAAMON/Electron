#ifndef BOXES_ELECTRON_H
#define BOXES_ELECTRON_H

void smallBox(int x, int y, int x2, int y2);
void bigBox(int x, int y, int w, int h, int size, bool differentColor = 0);
void hollowBox(int x, int y, int x2, int y2);
void buttonBox(int x, int y, int w, int h);
void longButtonBox(int x, int y, int w, int h, bool reverse);
#endif