#include <graphics.h>
#include "components.h"
#include <cmath>
#include <fstream>
#include <cstring>
#include <iostream>



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
    int pCount = 0;
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

void fir(int x1, int y1, int x2, int y2)
{
    line(x1, y1, (x1 + x2) / 2, y1);
    line((x1 + x2) / 2, y1, (x1 + x2) / 2, y2);
    line((x1 + x2) / 2, y2, x2, y2);
}


void baterie(int x, int y, int l)
{
    line(x, y, x + l / 3, y);
    line(x + 2 * l / 3, y, x + l, y);
    line(x + l / 3, y - l / 6, x + l / 3, y + l / 6);
    line(x + 2 * l / 3, y - l / 12, x + 2 * l / 3, y + l / 12);
}

void intrerupator(int x, int y, int l)
{
    line(x, y, x + l / 3, y);
    line(x + 2 * l / 3, y, x + l, y);
    line(x + l / 3, y, x + 2 * l / 3, y - l / 3 * floor(sqrt(2)));
}

void rezistor(int x, int y, int l)
{
    line(x, y, x + l / 3, y);
    line(x + 2 * l / 3, y, x + l, y);
    rectangle(x + l / 3, y - l / 12, x + 2 * l / 3, y + l / 12);
}

void bec(int x, int y, int l)
{
    line(x, y, x + l / 3, y);
    line(x + 2 * l / 3, y, x + l, y);
    circle(x + l / 2, y, l / 6);
    line(x + l / 3 + l / 12, y - l / 6 * ceil(1 / sqrt(2)), x + 2 * l / 3 - l / 12, y + l / 6 * ceil(1 / sqrt(2)));
    line(x + l / 3 + l / 12, y + l / 6 * ceil(1 / sqrt(2)), x + 2 * l / 3 - l / 12, y - l / 6 * ceil(1 / sqrt(2)));
}

void dioda(int x, int y, int l)
{
    line(x, y, x + l / 3, y);
    line(x + 2 * l / 3, y, x + l, y);
    line(x + l / 3, y - l / 6, x + l / 3, y + l / 6);
    line(x + l / 3, y - l / 6, x + 2 * l / 3, y);
    line(x + 2 * l / 3, y, x + l / 3, y + l / 6);
    line(x + 2 * l / 3, y - l / 6, x + 2 * l / 3, y + l / 6);
}

void capacitor(int x, int y, int l)
{
    line(x, y, x + l / 3, y);
    line(x + 2 * l / 3, y, x + l, y);
    line(x + l / 4 + l / 8, y - l / 6, x + l / 4 + l / 8, y + l / 6);
    line(x + 2 * l / 4 + l / 8, y - l / 6, x + 2 * l / 4 + l / 8, y + l / 6);
}

void condensator(int x, int y, int l)
{
    line(x, y, x + l, y);
    line(x + l / 2, y - l / 6, x + l / 2, y + l / 6);
    line(x + l / 2, y, x + l / 2 + l / 4, y - l / 6);
    line(x + l / 2, y, x + l / 2 + l / 4, y + l / 6);
    line(x + l / 2 + l / 4, y - l / 6, x + l / 2 + l / 4 + l / 16, y - l / 6 + l / 12);
    line(x + l / 2 + l / 4, y + l / 6, x + l / 2 + l / 4 + l / 16, y + l / 6 - l / 12);
}

void servomotor(int x, int y, int l)
{
    line(x, y, x + l / 4, y);
    line(x + 3 * l / 4, y, x + l, y);
    rectangle(x + l / 4, y - l / 8, x + 3 * l / 4, y + l / 8);
    ellipse(x + l / 2, y, 0, 360, l / 4, l / 8);
}

void zenner(int x, int y, int l)
{
    line(x, y, x + l / 3, y);
    line(x + 2 * l / 3, y, x + l, y);
    line(x + l / 3, y - l / 6, x + l / 3, y + l / 6);
    line(x + l / 3, y - l / 6, x + 2 * l / 3, y);
    line(x + 2 * l / 3, y, x + l / 3, y + l / 6);
    line(x + 2 * l / 3, y - l / 6, x + 2 * l / 3, y + l / 6);
    line(x + 2 * l / 3, y - l / 6, x + 2 * l / 3 + l / 12, y - l / 6);
    line(x + 2 * l / 3, y + l / 6, x + 2 * l / 3 - l / 12, y + l / 6);
}

void tranzistor()
{
;
}