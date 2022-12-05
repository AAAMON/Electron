#include <graphics.h>
#include "components.h"
#include <cmath>
#include <fstream>
#include <cstring>
#include <iostream>


// initializes a component
// type must be the same as the file name that holds the component info
void initComponent(Component &component, const char* type)
{
    strcpy(component.name, type);
    char loc[100] = { "src/" };
    strcat(loc, type);
    strcat(loc,".comp");
    std::cout << loc;

    std::ifstream compFile(loc);

    compFile.getline(component.description, 300);
    compFile >> component.nrOfInstr;

    int pCount = 0;
    int instrPts = 0;
    for (int i = 0; i < component.nrOfInstr; i++)
    {
        compFile >> component.drawInstrType[i];
        // Different types of instructions require a diff ammount of points
        switch (component.drawInstrType[i])
        {
            case 'L': 
                instrPts = 2;
                break;
            case 'R': 
                instrPts = 2;
                break;
            case 'E':
                instrPts = 6;
                break;
            case 'C':
                instrPts = 3;
                break;
            default:
                std::cerr << "Eroare fa\n";
        }
        // Read the necessary points
        for (int j = 0; j < instrPts; j++)
        {
            // VERIFY IF CIRCLE DUMB DUMB!!!!!
            compFile >> component.drawInstr[0][pCount];
            compFile >> component.drawInstr[1][pCount];
            pCount++;
        }
    }
    compFile >> component.nrOfBonds;
    for (int i = 0; i < component.nrOfBonds; i++)
    {
        compFile >> component.bonds[0][i];
        compFile >> component.bonds[1][i];
    }
}
void drawComponent(Component component)
{
    int pCount { 0 };
    for (int i = 0; i < component.nrOfInstr; i++)
    {
        // Different types of instructions require a diff ammount of points
        switch (component.drawInstrType[i])
        {
            case 'L': 
                line(component.drawInstr[0][pCount], component.drawInstr[1][pCount++], component.drawInstr[0][pCount], component.drawInstr[1][pCount++]);
                break;
            case 'R': 
                rectangle(component.drawInstr[0][pCount], component.drawInstr[1][pCount++], component.drawInstr[0][pCount], component.drawInstr[1][pCount++]);
                break;
            case 'E':
                break;
            case 'C':
                break;
            default:
                std::cerr << "Eroare fa\n";
        }
    }
}