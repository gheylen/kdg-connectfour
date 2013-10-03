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

#include "console.h"

#include <stdio.h>
#include <windows.h>

/****
    * This function determines wheterEscape has been pressed since last check or not
    *
    * Accepts:  void.
    *
    * Returns:  1 if Escape has been pressed since last check;
    *           0 if Escape hasn't been pressed since last check.
****/
int isEscPressed(void)
{
    return GetAsyncKeyState(VK_ESCAPE);
}

/****
    * This function determines wheter the "Up" - arrow has been pressed since last check or not
    *
    * Accepts:  void.
    *
    * Returns:  1 if the "Up" - arrow has been pressed since last check;
    *           0 if the "Up" - arrow hasn't been pressed since last check.
****/
int isUpArrowPressed(void)
{
    return GetAsyncKeyState(VK_UP);
}

/****
    * This function determines wheter the "Right" - arrow has been pressed since last check or not
    *
    * Accepts:  void.
    *
    * Returns:  1 if the "Right" - arrow has been pressed since last check;
    *           0 if the "Right" - arrow hasn't been pressed since last check.
****/
int isRightArrowPressed(void)
{
    return GetAsyncKeyState(VK_RIGHT);
}

/****
    * This function determines wheter the "Down" - arrow has been pressed since last check or not
    *
    * Accepts:  void.
    *
    * Returns:  1 if the "Down" - arrow has been pressed since last check;
    *           0 if the "Down" - arrow hasn't been pressed since last check.
****/
int isDownArrowPressed(void)
{
    return GetAsyncKeyState(VK_DOWN);
}

/****
    * This function determines wheter the "Left" - arrow has been pressed since last check or not
    *
    * Accepts:  void.
    *
    * Returns:  1 if the "Left" - arrow has been pressed since last check;
    *           0 if the "Left" - arrow hasn't been pressed since last check.
****/
int isLeftArrowPressed(void)
{
    return GetAsyncKeyState(VK_LEFT);
}

/****
    * This function determines wheter "Enter" has been pressed since last check or not
    *
    * Accepts:  void.
    *
    * Returns:  1 if "Enter" has been pressed since last check;
    *           0 if "Enter" hasn't been pressed since last check.
****/
int isEnterPressed(void)
{
    return GetAsyncKeyState(VK_RETURN);
}

/****
    * This function determines wheter the console window is the foreground window.
    * (The window where the user is working in)
    *
    * Accepts:  void.
    *
    * Returns:  1 if the console window is the active window;
    *           0 if the console window isn't the active window.
****/
int isConsoleActive(void)
{
    return (GetForegroundWindow() == GetConsoleWindow());
}

/****
    * This function changes the title of in the consolewindow.
    *
    * Accepts:  A char pointer containing the new title.
    *
    * Returns:  Nonzero on success;
    *           0 if the api call failed.
****/
int setConsoleTitle(char *title)
{
    return SetConsoleTitle(title);
}

/****
    * This function changes the way how the console formats it's output.
    *
    * Accepts:  An enum - value containing the formatting information.
    *
    * Returns:  Nonzero on success;
    *           0 if the api call failed.
****/
int setConsoleColorTo(enum color color)
{
    switch(color)
    {
        case YELLOW:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
        case RED:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        //case BLUE:
        //    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
        case GREEN:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        case WHITE:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
        case BLUE_GREEN:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
        case PURPLE:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED);
        case iYELLOW:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        case iRED:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        case iBLUE:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        case iGREEN:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        case iWHITE:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        case iBLUE_GREEN:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        case iPURPLE:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        case HIGHLIGHT:
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        default:    //reset
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | 0);
    }
}

/****
    * This function is a combo of the "setConsoleColorTo" - function and a simple "printf".
    *
    * Accepts:  A char pointer containing the output string;
    *           An enum - value containing the formatting information.
    *
    * Returns:  void.
****/
void printFormatted(char *text, enum color color)
{
    setConsoleColorTo(color);
	printf(text);
    setConsoleColorTo(RESET);
}

/****
    * This function resets the AsyncKeyCheck to current events instead of earlier.
    * Normally the functions checks whether is has been pressed or not since last check,
    * so it might still have other events hooked to the function.
    *
    * Accepts:  void.
    *
    * Returns:  void.
****/
void resetAsyncKeyStates()
{
    isEnterPressed();
    isUpArrowPressed();
    isDownArrowPressed();
    isLeftArrowPressed();
    isRightArrowPressed();
    isEscPressed();
}
