#ifndef COMPONENTS_ELECTRON_H
#define COMPONENTS_ELECTRON_H

// An electronic component
struct Component 
{
	// basic info
	char name[30];
	char description[1000];

	// logic info
	int nrOfBonds;
	// 0 is x coordonate of bond point, 1 is y
	int bonds[2][5];
	bool isBondActive[5];
	bool current;

	// drawing info
	int x;
	int y;
	// TODO: make it scalable
	int size;
	int orientation;

	// drawing instructions that are read from file
	int      nrOfInstructions;
	int   nrOfDrawCoordinates;
	char 	drawInstrType[10];
	float drawCoordinates[50];
};

struct Wire
{
	int component1;
	int bond1;
	int component2;
	int bond2;

	bool current;
};

//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void initComponent(Component &component, const char* type);
void drawComponent(Component component);
void moveComponent(Component& component, int x, int y);

//////////////////////////////////////////////////////////////////////////////
/// D E B U G ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void printComponent(Component component);

#endif