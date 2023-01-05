#ifndef BOXES_ELECTRON_H
#define BOXES_ELECTRON_H
struct Color{
int r;
int g;
int b;
};
void getColor(Color &color,int r, int g, int b);
void smallBox(int x, int y, int x2, int y2,Color color);
void bigBox(int x, int y, int w, int h, int size,Color color);
void hollowBox(int x, int y, int x2, int y2,Color color);
void buttonBox(int x, int y, int w, int h,Color color);
void longButtonBox(int x, int y, int w, int h, bool reverse,Color color);

#endif