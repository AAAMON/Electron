#include <string>
#ifndef COMPONENTS_ELECTRON_H
#define COMPONENTS_ELECTRON_H
struct Component 
{
	string name;
	string description;

	int x;
	int y;
	int size;
	int nrOfBonds;
	int bonds[2][5];
	int orientation;

	// for drawing
	int nrOfInstr;
	int drawInstr[2][10];
};

void initComponent(Component component, string type);
void drawComponent(Component component);

void fir(int x1, int y1, int x2, int y2);
void baterie(int x, int y, int l);
void intrerupator(int x, int y, int l);
void rezistor(int x, int y, int l);
void bec(int x, int y, int l);
void dioda(int x, int y, int l);
void capacitor(int x, int y, int l);
void condensator(int x, int y, int l);
void servomotor(int x, int y, int l);
void zenner(int x, int y, int l);
void tranzistor();

#endif