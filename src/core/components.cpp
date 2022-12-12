#include <graphics.h>
#include "components.h"
#include <cmath>
#include <fstream>
#include <cstring>
#include <iostream>


//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


// initializes a component
// type must be the same as the file name that holds the component info
void initComponent(Component &component, const char* type)
{
    strcpy(component.name, type);
    char filePath[100] = { "assets/" };
    strcat(filePath,   type);
    strcat(filePath,".comp");

    component.x = 400;
    component.y = 400;
    component.size = 15;

    // opening the file with the component data
    std::ifstream compFile(filePath);

    // read the component description
    compFile.getline(component.description, 300);

    // read the drawing instructions
    compFile >> component.nrOfInstr;
    component.nrOfDrawCoordinates = 0; // total number of points for drawing
    int instrPoints               = 0; // number of points that an instruction uses
    for (int i = 0; i < component.nrOfInstr; i++)
    {
        compFile >> component.drawInstrType[i];
        // Different types of instructions require a diff ammount of points
        instrPoints = getNrOfPointsUsed(component.drawInstrType[i]);
        // Read the necessary coordinates
        for (int j = 0; j < instrPoints; j++)
        {
            compFile >> component.drawCoordinates[component.nrOfDrawCoordinates];
            component.nrOfDrawCoordinates++;
        }
    }

    // reading the logic info (bonding points)
    compFile >> component.nrOfBonds;
    for (int i = 0; i < component.nrOfBonds; i++)
    {
        compFile >> component.bonds[0][i]; // x
        compFile >> component.bonds[1][i]; // y
    }
}


// Immediately draws component on screen
void drawComponent(Component component)
{
    setcolor(COLOR(153,200,153));
    int coord = 0; // iterator for drawing coordinates
    // doing each instruction
    for (int i = 0; i < component.nrOfInstr; i++)
    {
        // Different types of instructions require a diff ammount of points
        switch (component.drawInstrType[i])
        {
            case 'L': 
                line(
                    component.x + component.drawCoordinates[coord]   * component.size, component.y + component.drawCoordinates[coord+1] * component.size, 
                    component.x + component.drawCoordinates[coord+2] * component.size, component.y + component.drawCoordinates[coord+3] * component.size);
                coord += 4; // we've used 4 coordinates
                break;
            case 'R': 
                rectangle(
                    component.x + component.drawCoordinates[coord]   * component.size, component.y + component.drawCoordinates[coord+1] * component.size, 
                    component.x + component.drawCoordinates[coord+2] * component.size, component.y + component.drawCoordinates[coord+3] * component.size);
                coord += 4;
                break;
            case 'C':
                circle(
                    component.x + component.drawCoordinates[coord]   * component.size, component.y + component.drawCoordinates[coord+1] * component.size, 
                    component.drawCoordinates[coord+2] * component.size);
                coord += 3;
                break;
            case 'E':
                ellipse(
                    component.x + component.drawCoordinates[coord]   * component.size, component.y + component.drawCoordinates[coord+1] * component.size, 
                    component.drawCoordinates[coord+2], component.drawCoordinates[coord+3],                                  // angle
                    component.drawCoordinates[coord+4] * component.size, component.drawCoordinates[coord+5] * component.size // radius
                );
                coord += 6;
                break;
            default:
                std::cerr << "Eroare fa\n";
        }
    }
}


//////////////////////////////////////////////////////////////////////////////
/// M I S C //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// returns number of points that an instruction uses
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

// Moves component to specified location
void moveComponent(Component& component, int x, int y)
{
    component.x = x;
    component.y = y;
}

//////////////////////////////////////////////////////////////////////////////
/// D E B U G ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// for debugging purposes...
void printComponent(Component component)
{
    std::cout << component.name << '\n';
    std::cout << component.description << '\n';
    std::cout << component.nrOfInstr << '\n';
    for (int i = 0; i < component.nrOfInstr; i++)
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