#include <graphics.h>
#include "components.h"
#include <cmath>
#include <fstream>
#include <cstring>
#include <iostream>
#include "project.h"

//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


/// I N I T I A L I Z A T I O N //////////////////////////////////////////////

// aux functions
void readDrawInstructions(Component& component, std::ifstream& compFile);
void readLogicInstructions(Component& component, std::ifstream& compFile);
// Initializes a component
// Type must be the same as the file name that holds the component info
void initComponent(Component &component, const char* type)
{
    strcpy(component.name, type);
    component.x    =  { 0 };
    component.y    =  { 0 };
    // TODO: make this readable from file
    component.size = { 15 };

    // component-specific data is stored in a file
    char filePath[100] = { "assets/" };
    strcat(filePath,   type);
    strcat(filePath,".comp");
    std::ifstream compFile(filePath);

    compFile.getline(component.description, 1000);

    readDrawInstructions(component, compFile);

}

/// D R A W I N G ////////////////////////////////////////////////////////////

// Draws component on sdl surface
void drawComponent(Component component)
{
    // TODO use color from theme,,,

    setrgbcolor(COMPONENTS);

    // Coordonates are stored in an array, and we need a separate iterator
    // because different instructions use a different ammount of points
    int coord = { 0 };

    for (int i = 0; i < component.nrOfInstructions; i++)
    {
        switch (component.drawInstrType[i])
        {
            case 'L': 
                line
                (
                    component.x + component.drawCoordinates[coord]   * component.size, 
                    component.y + component.drawCoordinates[coord+1] * component.size, 
                    component.x + component.drawCoordinates[coord+2] * component.size, 
                    component.y + component.drawCoordinates[coord+3] * component.size
                );
                coord += 4; // we've used 4 coordinates
                break;
            case 'R': 
                rectangle
                (
                    component.x + component.drawCoordinates[coord]   * component.size, 
                    component.y + component.drawCoordinates[coord+1] * component.size, 
                    component.x + component.drawCoordinates[coord+2] * component.size, 
                    component.y + component.drawCoordinates[coord+3] * component.size
                );
                coord += 4;
                break;
            case 'C':
                circle
                (
                    component.x + component.drawCoordinates[coord]   * component.size, 
                    component.y + component.drawCoordinates[coord+1] * component.size, 
                    component.drawCoordinates[coord+2]               * component.size
                );
                coord += 3;
                break;
            case 'E':
                ellipse
                (
                    component.x + component.drawCoordinates[coord]   * component.size, 
                    component.y + component.drawCoordinates[coord+1] * component.size, 
                    component.drawCoordinates[coord+2], 
                    component.drawCoordinates[coord+3],
                    component.drawCoordinates[coord+4] * component.size, 
                    component.drawCoordinates[coord+5] * component.size
                );
                coord += 6;
                break;
            default:
                // Devious
                std::cerr << component.name << " Eroare fa1\n";
        }
    }
}

/// O T H E R ////////////////////////////////////////////////////////////////

// Moves component to specified location
void moveComponent(Component& component, int x, int y)
{
    component.x = x;
    component.y = y;
}

//////////////////////////////////////////////////////////////////////////////
/// A U X ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// aux aux,,,
int getNrOfPointsUsed(char instructionType);
// Reads the drawing instructions from component file
void readDrawInstructions (Component& component, std::ifstream& compFile)
{
    compFile >> component.nrOfInstructions;
    component.nrOfDrawCoordinates = 0; // total number of points for drawing
    int pointsPerInstruction      = 0; // number of points that an instruction uses
    for (int i = 0; i < component.nrOfInstructions; i++)
    {
        // A single character that describes the drawing function to be used
        compFile >> component.drawInstrType[i];
        // Different types of instructions require a diff ammount of points
        pointsPerInstruction = getNrOfPointsUsed(component.drawInstrType[i]);

        // The coordinates are stored in an array
        for (int j = 0; j < pointsPerInstruction; j++)
        {
            compFile >> component.drawCoordinates[component.nrOfDrawCoordinates];
            component.nrOfDrawCoordinates++;
        }
    }
    compFile >> component.nrOfBonds;

    for (int i = 0; i < component.nrOfBonds; i++)
    {
        compFile >> component.bonds[0][i] >> component.bonds[1][i];
    }
}

// Reads the logic info from component file (bonding points)
void readLogicInstructions(Component& component, std::ifstream& compFile)
{
    compFile >> component.nrOfBonds;
    for (int i = 0; i < component.nrOfBonds; i++)
    {
        compFile >> component.bonds[0][i]; // x
        compFile >> component.bonds[1][i]; // y
    }
}

// Returns number of points that an instruction uses
int getNrOfPointsUsed(char instructionType)
{
    switch (instructionType)
    {
        case 'L':  // does this thing even need break;?...
            return 4;
            break;
        case 'R': 
            return 4;
            break;
        case 'E':
            return 6;
            break;
        case 'C':
            return 3;
            break;
        default:
            return -1;
            std::cerr << "Eroare fa\n";
    }
    return -1;
}

//////////////////////////////////////////////////////////////////////////////
/// D E B U G ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// for debugging purposes...
void printComponent(Component component)
{
    std::cout << component.name << '\n';
    std::cout << component.description << '\n';
    std::cout << component.nrOfInstructions << '\n';
    for (int i = 0; i < component.nrOfInstructions; i++)
        std::cout << component.drawInstrType[i] << ' ';
    std::cout << '\n';

    std::cout << component.nrOfDrawCoordinates << '\n';
    for (int i = 0; i < component.nrOfDrawCoordinates; i++)
    {
        std::cout << component.drawCoordinates[i] <<  '\n';
    }

    std::cout << component.nrOfBonds << '\n';
    for (int i = 0; i < component.nrOfBonds; i++)
    {
        std::cout << component.bonds[0][i] <<  ' ';
        std::cout << component.bonds[1][i] << '\n';
    }
}
