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
	float bonds[2][5];
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

struct WirePoint
{
	char type;
	int id;
	int id2;
	int length;
	bool direction;
};

struct DrawPoint
{
	int x;
	int y;
};

struct Wire
{
	int nrOfPoints;
	WirePoint points[200];

	int nrOfDrawPoints;
	DrawPoint drawPoints[10];

	bool current;
};

//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void initComponent(Component &component, const char* type);
void drawComponent(Component component);
void moveComponent(Component& component, int x, int y);
void rotateComponent(Component& component, int s, int c);
//////////////////////////////////////////////////////////////////////////////
/// D E B U G ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void printComponent(Component component);

#endif