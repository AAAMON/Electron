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
	int size; // default, can be scaled by user in-program
	int orientation;
	// drawing instructions that are read from file
	int nrOfInstr;
	int nrOfDrawCoordinates;
	char drawInstrType[10];
	float drawCoordinates[50];
};

void initComponent(Component &component, const char* type);
void drawComponent(Component component);
int getNrOfPointsUsed(char instructionType);

// DEBUGGING
void printComponent(Component component);

#endif