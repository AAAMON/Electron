#ifndef COMPONENTS_ELECTRON_H
#define COMPONENTS_ELECTRON_H

// an electronic component
struct Component 
{
	// basic info
	char name[30];
	char description[300];

	// logic info
	int nrOfBonds;
	int bonds[2][5];

	// drawing info
	int x;
	int y;
	int size;
	int orientation;
	int nrOfInstr;
	char drawInstrType[10];
	int drawInstr[2][10];
};

void initComponent(Component &component, const char* type);
void drawComponent(Component component);

#endif