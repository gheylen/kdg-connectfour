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

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "color.h"

#define _WIN32_WINNT 0x0500 //required for several win api calls.
#define CONSOLE_WIDTH 80

/****
    * Virtual key values.
    *
    * Note: Depricated. Already defined in WIN API;
    *       Will be removed in later revisions.
****/
/*
#define VK_LEFT			0x25
#define VK_UP			0x26
#define VK_RIGHT        0x27
#define VK_DOWN         0x28
*/

/****
    * Enumeration with the possible output formatting styles for the console.
    *
    * Note: Depricated. Use of global "color.h" - headerfile;
    *       Will be removed in later revisions.
****/
/*enum consoleColorOption
{
    FRONT_YELLOW,
    FRONT_RED,
    FRONT_BLUE,
    BACK_WHITE,
    DEFAULT
};*/

int isEscPressed(void);
int isUpArrowPressed(void);
int isRightArrowPressed(void);
int isDownArrowPressed(void);
int isLeftArrowPressed(void);
int isEnterPressed(void);
int isConsoleActive(void);
int setConsoleTitle(char*);
int setConsoleColorTo(enum color);
void printFormatted(char*, enum color);
void resetAsyncKeyStates(void);

#endif

