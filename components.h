#ifndef COMPONENTS_ELECTRON_H
#define COMPONENTS_ELECTRON_H

struct Component 
{
	char name[30];
	char description[300];

	int x;
	int y;
	int size;
	int nrOfBonds;
	int bonds[2][5];
	int orientation;

	// for drawing
	int nrOfInstr;
	char drawInstrType[10];
	int drawInstr[2][10];
};

void initComponent(Component &component, const char* type);
void drawComponent(Component component);

void fir(int x1, int y1, int x2, int y2);
void intrerupator(int x, int y, int l);
void tranzistor();

#endif