/*  ConnectFour Copyright (c) 2008 Glenn Heylen and Bert Lemmens

	This file is part of ConnectFour.

    ConnectFour is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ConnectFour is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ConnectFour.  If not, see <http://www.gnu.org/licenses/>.*/

#include "menu.h"
#include "console.h"

#include <stdio.h>
#include <windows.h>

/****
    * This function works as a contructor for a menu.
    *
    * Accepts:  A pointer to a menu;
    *           The title of the new menu in string format.
    *
    * Returns:  void.
****/
void constructMenu(menu *menu, char *title)
{
    menu->count = 0;
    menu->choses = NULL;
    menu->menuName = title;
}

/****
    * This function add another chose to the menu.
    *
    * Accepts:  A pointer to a menu;
    *           The chose to be added in string format.
    *
    * Returns:  void.
****/
void addChose(menu *menu, char* chose)
{
    menu->count++;

    menu->choses = realloc(menu->choses, menu->count * sizeof(char*));

    *(menu->choses + menu->count - 1) = chose;
}

/****
    * This function frees the allocated heap for a menu.
    *
    * Accepts:  A pointer to a menu.
    *
    * Returns:  void.
****/
void freeMenu(menu *menu)
{
    free(menu->choses);
}

/****
    * This function handles a menu's loop until an option is chosen.
    *
    * Accepts:  A pointer to a menu.
    *
    * Returns:  The chose picked.
****/
int getChose(menu *menu)
{
    int chose = -1;
    int activeChose = 0;

    setConsoleTitle(menu->menuName);
    clearScreenAndDrawMenu(menu, activeChose);
    resetAsyncKeyStates();  // Otherwise menu might be activated immediately. (artf1025)

    while(chose < 0)
    {
        Sleep(99);
        if(!isConsoleActive())
            continue;   //Don't abuse processor-res if user isn't working in console window. (artf1025)
        if(isDownArrowPressed() && (activeChose + 1 < menu->count))
            clearScreenAndDrawMenu(menu, ++activeChose);
        if(isUpArrowPressed() && (activeChose > 0))
            clearScreenAndDrawMenu(menu, --activeChose);
        if(isEnterPressed())
            chose = activeChose;
    }

    return chose;
}

/****
    * This function handles the actual drawing of a menu.
    *
    * Accepts:  A pointer to a menu;
    *           The current activeChose.
    *
    * Returns:  void.
****/
void clearScreenAndDrawMenu(menu *menu, int active)
{
    int i;

    system("cls");

    printf("+");  //first line (0)
    for(i = 0; i < MENU_WIDTH - 2; i++) //first line (1)
        printf("-");
    printf("+\n"); //first line (2)

	printf("|  ");  //second line (0)
	printFormatted(menu->menuName, YELLOW);   //second line (1)
	printf("%*s", MENU_WIDTH - strlen(menu->menuName) - 4, " ");  //second line (2)
	printf("|\n");  //second line (3)

    printf("|");  //tirth line (0)
    for(i = 0; i < MENU_WIDTH - 2; i++) //tirth line (1)
        printf("-");
    printf("|\n"); //tirth line (2)

    //all the other lines
    for(i = 0; i < menu->count; i++)
    {
        printf("|  ");
        (active == i ? printFormatted(*(menu->choses + i), HIGHLIGHT) : printf(*(menu->choses + i)));
        printf("%*s", MENU_WIDTH - strlen(*(menu->choses + i)) - 4, " ");
        printf("|\n");
    }

    printf("+");  //final line (0)
    for(i = 0; i < MENU_WIDTH - 2; i++) //final line (1)
        printf("-");
    printf("+\n"); //final line (2)
}
