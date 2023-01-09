#include "menu.h"
#include "../core/project.h"
#include "../interactive/menu.h"


//////////////////////////////////////////////////////////////////////////////
/// M A I N   F U N C T I O N S //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void initMenuBar(MenuBar& menuBar)
{
  std::ifstream menuFile("assets/menubar.gui");
  menuFile >> menuBar.nrOfElements;
  int x = 0;
  menuBar.open = -1;
  for (int i = 0; i < menuBar.nrOfElements; i++)
  {
    menuFile >> menuBar.menuBarElement[i].name;
    menuBar.menuBarElement[i].x = x;
    menuFile >> menuBar.menuBarElement[i].w;
    menuFile >> menuBar.menuBarElement[i].optionsWidth;
    menuBar.menuBarElement[i].open = false;
    x += menuBar.menuBarElement[i].w;

    char id;
    // READ OPTIONS
    menuFile >> menuBar.menuBarElement[i].nrOfOptions;
    for (int j = 0; j < menuBar.menuBarElement[i].nrOfOptions; j++)
    {
      menuFile >> id;
      menuBar.menuBarElement[i].options[j].functionId = id - '0';
      menuFile.getline(menuBar.menuBarElement[i].options[j].name, 50);
    }
  }
}

void initMenu(Menu& menu)
{
  menu.show = true;
  menu.width = WIDTH/5;
  menu.height = HEIGHT-60; // 36 + 24
  menu.elementHeigth = menu.height/12;
  menu.buttonWidth = 20;
  menu.scroll = 0;
  
  std::ifstream menuFile("assets/menu.gui");
  menuFile >> menu.nrOfColumns;

  char text[30];
  int cat = -1; // iterator for categories
  int com = 0; // iterator for components
  // reading all the columns
  menuFile.getline(text, 30); // reads a space or smth
  for (int i = 0; i < menu.nrOfColumns; i++)
  {
    menuFile.getline(text, 30);
    if (strstr(text, "CATEGORY"))
    {
      // CREATE NEW CATEGORY
      cat++;
      strcpy(menu.categories[cat].name, text + 9); // +9 so it skips "CATEGORY "
      menu.categories[cat].nrOfColumns = 0;
      // UPDATE COLUMN
      char content[3] = { "A" };
      content[1] = { '0' };
      content[1] += cat;
      strcpy(menu.columns[i].content, content); 
      menu.columns[i].visible = true;
    }
    else
    {
      // CREATE NEW COMPONENT
      menu.categories[cat].nrOfColumns++; // add column to current category
      char* componentName;
      componentName = strtok(text, " ");
      // first one
      initComponent(menu.components[com], componentName);
      // UPDATE COLUMN
      char content[3] = { "O" };
      content[1] = { '0' };
      content[1] += com;
      com++;
      componentName = strtok(NULL, " "); // next component
      if (componentName != NULL)
      {
        initComponent(menu.components[com], componentName);
        content[2] = { '0' };
        content[2] += com;
        com++;
      }
      content[3] = '\0'; // don't ask why, just leave it here
      strcpy(menu.columns[i].content, content); 
      menu.columns[i].visible = true;
    }
  }
}


// AUX FUNCTIONS FOR drawMenu
void drawMenuScroll(Menu menu);
void drawMenuClosed(Menu menu);
void drawMenuComponents(Menu menu, int c, int i, bool twoComponents);
void drawMenuComponentsRow(Menu menu, int i);
// Draws the menu on the built-in SDL_Surface
void drawMenu(Menu menu)
{
  if (menu.show) {
    // BACKGROUND
    //86 82 98
    setcolor(COLOR(
      (RED_VALUE   (6) + 60 > 255? 255: RED_VALUE   (6) + 60), 
      (GREEN_VALUE (6) + 55 > 255? 255: GREEN_VALUE (6) + 55),
      (BLUE_VALUE  (6) + 55 > 255? 255: BLUE_VALUE  (6) + 55)));
    setfillstyle(SOLID_FILL, getcolor());
    bar(0, 36, menu.width, 36 + menu.height);

    // SCROLL BAR
    drawMenuScroll(menu);

    // MENU ROWS
    int c = menu.scroll;
    for (int i = 0; i < 12; i++)
    {
      // ROW OUTLINE
      setcolor(COLOR(36,35,39));
      rectangle(0, 36 + menu.elementHeigth * i, menu.width - menu.buttonWidth, 36 + menu.elementHeigth * (i + 1));
      // IF THE ROW IS A C(A)TEGORY NAME
      if (menu.columns[c+i].content[0] == 'A')
      {
        bigBox(0, 36 + menu.elementHeigth * i, menu.width - menu.buttonWidth, menu.elementHeigth, 1);
        if (WIDTH == 1920)
          settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
        else
          settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
        settextjustify (CENTER_TEXT, CENTER_TEXT);
        setrgbcolor(MENU_TEXT);
        outtextxy(0 + menu.width/2 - menu.buttonWidth/2, 36 + menu.elementHeigth * i + menu.elementHeigth/2, menu.categories[(int)menu.columns[c+i].content[1]-'0'].name);
      }
      // IF THE ELEMENT IS A C(O)MPONENT
      else
      {
        drawMenuComponentsRow(menu, i);
        // TWO COMPONENT ON ROW
        if (menu.columns[c+i].content[2])
          drawMenuComponents(menu, c, i, 1);
        // ONE COMPONENTS ON ROW
        else
          drawMenuComponents(menu, c, i, 0);
      }
    }
  }
  else
    drawMenuClosed(menu);
}



void drawMenuBar(MenuBar menuBar)
{
  bigBox(0, 0, WIDTH, 36, 1, 1);
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
  
  for (int i = 0; i < menuBar.nrOfElements; i++)
  {
    bigBox(menuBar.menuBarElement[i].x, 0, menuBar.menuBarElement[i].w, 36, 1, 1);
    setrgbcolor(MENU_BAR_TEXT);
    settextjustify (CENTER_TEXT, CENTER_TEXT);
    outtextxy(menuBar.menuBarElement[i].x + menuBar.menuBarElement[i].w/2, 18, menuBar.menuBarElement[i].name);
    
    
    if (menuBar.menuBarElement[i].open)
    {
      drawMenuBarOptions(menuBar.menuBarElement[i]);
    }
  }
}





//////////////////////////////////////////////////////////////////////////////
/// A U X   F U N C T I O N S ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// Draws menu scroll bar
void drawMenuScroll(Menu menu)
{
  // BACKGROUND
  setfillstyle(SOLID_FILL, COLOR(176,168,159));
  
  bar(menu.width - menu.buttonWidth, 36, menu.width, 36 + menu.height);
  longButtonBox(menu.width - menu.buttonWidth, 36, menu.buttonWidth, menu.height/2 - 20, 0);
  longButtonBox(menu.width - menu.buttonWidth, 36 + menu.height/2 + 20, menu.buttonWidth, menu.height/2 - 20, 1);

  // LINES
  setcolor(COLOR(36,35,39));
  rectangle(menu.width - menu.buttonWidth, 36, menu.width, 36 + menu.height);
  buttonBox(menu.width - menu.buttonWidth, 36 + menu.height/2-20, menu.buttonWidth, 40);
  setcolor(COLOR(36,35,39));
  line(menu.width - menu.buttonWidth, 36 + menu.height/2-20, menu.width, 36 + menu.height/2-20);
  line(menu.width - menu.buttonWidth, 36 + menu.height/2+20, menu.width, 36 + menu.height/2+20);


  // DETAILS
  // plz replace this with some arrows...
  setrgbcolor(SCROLL_DETAIL);
  for(int i=0;i<=1;i++)
  {
    //n
    line(menu.width - menu.buttonWidth/2-i, 40 + menu.buttonWidth/2-3, menu.width - menu.buttonWidth/2-4-i, 40 + menu.buttonWidth/2+3);
    line(menu.width - menu.buttonWidth/2+i, 40 + menu.buttonWidth/2-3, menu.width - menu.buttonWidth/2+4+i, 40 + menu.buttonWidth/2+3);
    line(menu.width - menu.buttonWidth/2-i, 40 + menu.buttonWidth/2*3-3,menu.width - menu.buttonWidth/2-4-i,40 + menu.buttonWidth/2*3+3);
    line(menu.width - menu.buttonWidth/2-i, 40 + menu.buttonWidth/2*3-3,menu.width - menu.buttonWidth/2+4-i,40 + menu.buttonWidth/2*3+3);
    line(menu.width - menu.buttonWidth/2-i, 40 + menu.buttonWidth/2*5-3,menu.width - menu.buttonWidth/2-4-i,40 + menu.buttonWidth/2*5+3);
    line(menu.width - menu.buttonWidth/2-i, 40 + menu.buttonWidth/2*5-3,menu.width - menu.buttonWidth/2+4-i,40 + menu.buttonWidth/2*5+3);
  }
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
  settextjustify (CENTER_TEXT, CENTER_TEXT);
  outtextxy(menu.width - menu.buttonWidth/2+2, 36 + menu.height/2, (char*)"<");
  for(int i=0;i<=1;i++)
  {
    //u
  line(menu.width - menu.buttonWidth/2-i, 32 + menu.height - menu.buttonWidth/2*5+3,menu.width - menu.buttonWidth/2-4-i,32 + menu.height - menu.buttonWidth/2*5-3);
  line(menu.width - menu.buttonWidth/2+i, 32 + menu.height - menu.buttonWidth/2*5+3,menu.width - menu.buttonWidth/2+4-i,32 + menu.height - menu.buttonWidth/2*5-3);
  line(menu.width - menu.buttonWidth/2-i, 32 + menu.height - menu.buttonWidth/2*3+3,menu.width - menu.buttonWidth/2-4-i,32 + menu.height - menu.buttonWidth/2*3-3);
  line(menu.width - menu.buttonWidth/2+i, 32 + menu.height - menu.buttonWidth/2*3+3,menu.width - menu.buttonWidth/2+4-i,32 + menu.height - menu.buttonWidth/2*3-3);
  line(menu.width - menu.buttonWidth/2-i, 32 + menu.height - menu.buttonWidth/2+3,menu.width - menu.buttonWidth/2-4-i,32 + menu.height - menu.buttonWidth/2-3);
  line(menu.width - menu.buttonWidth/2+i, 32 + menu.height - menu.buttonWidth/2+3,menu.width - menu.buttonWidth/2+4-i,32 + menu.height - menu.buttonWidth/2-3);
  }
}

// Draws menu when it's closed
void drawMenuClosed(Menu menu)
{
  // INACTIVE AREA - BACKGROUND
  setfillstyle(SOLID_FILL, COLOR(138,132,155));
  bigBox(0, 36, menu.buttonWidth, menu.height/2-20, 1);
  bigBox(0, 36 + menu.height/2 + 20, menu.buttonWidth, menu.height/2-20, 1);
  //bar(0, 36, menu.buttonWidth, 36 + menu.height);
  

  // BUTTON AREA - BACKGROUND
  setfillstyle(SOLID_FILL, COLOR(176,168,159));
  buttonBox(0, 36 + menu.height/2 - 20, menu.buttonWidth, 40);


  // BUTTON AREA - LINES
  setcolor(COLOR(36,35,39));
  rectangle(0, 36, menu.buttonWidth, 36 + menu.height);
  line(0, 36 + menu.height/2-20, menu.buttonWidth, 36 + menu.height/2-20);
  line(0, 36 + menu.height/2+20, menu.buttonWidth, 36 + menu.height/2+20);
  // BUTTON AREA - TEXT
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
  settextjustify (CENTER_TEXT, CENTER_TEXT);
  outtextxy(menu.buttonWidth/2, 36 + menu.height/2, (char*)">");
}

// Draws components for the components line
void drawMenuComponents(Menu menu, int c, int i, bool twoComponents)
{
  // COMPONENT - TEXT
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
  settextjustify (CENTER_TEXT, CENTER_TEXT);
  setrgbcolor(MENU_COMPONENT_TEXT);
  outtextxy(0 + menu.width/4 - menu.buttonWidth/2, 36 + menu.elementHeigth * i + menu.elementHeigth - 10, menu.components[(int)menu.columns[c+i].content[1]-'0'].name);
  
  // COMPONENT - IMAGE
  moveComponent(menu.components[(int)menu.columns[c+i].content[1]-'0'], 0 + menu.width/4 - menu.buttonWidth/2, 36 + menu.elementHeigth * i + menu.elementHeigth/2 - 10);
  drawComponent(menu.components[(int)menu.columns[c+i].content[1]-'0']);

  if (twoComponents)
  {
    moveComponent(menu.components[(int)menu.columns[c+i].content[2]-'0'], 0 + menu.width/4*3 - menu.buttonWidth/2, 36 + menu.elementHeigth * i + menu.elementHeigth/2 - 10);
    drawComponent(menu.components[(int)menu.columns[c+i].content[2]-'0']);
    setrgbcolor(MENU_COMPONENT_TEXT);
    outtextxy(0 + menu.width/4*3 - menu.buttonWidth/2, 36 + menu.elementHeigth * i + menu.elementHeigth - 10, menu.components[(int)menu.columns[c+i].content[2]-'0'].name);
  }
}

// Draws a row containing components
void drawMenuComponentsRow(Menu menu, int i)
{
  // LINE SEPARATING THE COMPONENTS
  setcolor(COLOR(36,35,39));
  line(menu.width/2 - menu.buttonWidth, 36 + menu.elementHeigth * i, menu.width/2 - menu.buttonWidth, 36 + menu.elementHeigth * (i + 1));
  
  // BOXES
  setfillstyle(SOLID_FILL, COLOR(87,87,87));
  hollowBox(2, 38 + menu.elementHeigth * i, menu.width/2 - menu.buttonWidth -2, 36 + menu.elementHeigth * (i + 1) - 2);
  hollowBox(2 + menu.width/2 - menu.buttonWidth, 38 + menu.elementHeigth * i, menu.width - menu.buttonWidth - 2, 36 + menu.elementHeigth * (i + 1) - 2);
  // bar(2, 26 + menu.elementHeigth * i, menu.width/2 - menu.buttonWidth -2, 36 + menu.elementHeigth * (i + 1) - 2);
  // bar(2 + menu.width/2 - menu.buttonWidth, 26 + menu.elementHeigth * i, menu.width - menu.buttonWidth - 2, 36 + menu.elementHeigth * (i + 1) - 2);
}


//////////////////////////////////////////////////////////////////////////////
/// D E B U G ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void printMenu(Menu menu)
{
  std::cout << "Nr of columns: " << menu.nrOfColumns << '\n';
  for (int i = 0; i < menu.nrOfColumns; i++)
  {
    std::cout << menu.columns[i].content << "\n";
  }
}

