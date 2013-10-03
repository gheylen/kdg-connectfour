/*  ConnectFour Copyright (c) 2008 Glenn Heylen

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
#include "game.h"
#include "main.h"

/****
    * The entry point: a simple mainloop to keep the process alive.
    *
    * Accepts:  void.
    *
    * Returns:  Process status code:
    *               1 if successfully ran;
    *               Other if ran agains't an exception.
****/
int main(void)
{
    menu mainMenu;
    buildMainMenu(&mainMenu);

    game mainGame;

    int action = getChose(&mainMenu);
    while (action != mainMenu.count - 1)
    {
        switch (action)
        {
            case 0:
                constructGame(&mainGame, 7, 6, 2, 0, 0);
                break;
            case 1:
                constructGame(&mainGame, 7, 6, 1, 1, 1);
                break;
            case 2:
                constructGame(&mainGame, 7, 6, 1, 1, 2);
                break;
            case 3:
                constructGame(&mainGame, 14, 12, 2, 0, 0);
                break;
            case 4:
                constructGame(&mainGame, 14, 12, 1, 1, 2);
                break;
            case 5:
                constructGame(&mainGame, 14, 12, 5, 0, 0);
                break;
            case 6:
                constructGame(&mainGame, 14, 12, 1, 5, 2);
                break;
        }

        loopGame(&mainGame);
        destructGame(&mainGame);

        action = getChose(&mainMenu);
    }

    freeMenu(&mainMenu);
    return 1;
}


/****
    * A small helper to construct a menu. Put in function to improve readablity.
    *
    * Accepts:  A pointer to a menu struct.
    *
    * Returns:  void.
****/
void buildMainMenu(menu *mainMenu)
{
    constructMenu(mainMenu, "Connect Four");

    addChose(mainMenu, "Start PVP Game");
    addChose(mainMenu, "Start Medium Game");
    addChose(mainMenu, "Start Impossible Game");
    addChose(mainMenu, "Demo PVP 1");
    addChose(mainMenu, "Demo AI 1");
    addChose(mainMenu, "Demo PVP 2");
    addChose(mainMenu, "Demo AI 2");
    addChose(mainMenu, "Exit");
}
