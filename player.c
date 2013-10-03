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

#include "player.h"
#include "random.h"

#include <windows.h>

/****
    * This is the constructor for an array of players.
    *
    * Accepts:  A pointer to an array of player structures;
    *           The size of the array above;
    *           The number AI's joining the game.
    *
    * Returns:  void.
****/
void constructPlayers(player **players, int playerCount, int aiCount)
{
    int i;
    char *playerString; // buffer
    char buffer[3]; // buffer (ultimately limits players to a number of 2 digits)
    *players = NULL;

    for(i = 1; i < playerCount + 1; i++)
    {
        playerString = (char*)malloc(sizeof(char) * 10);
        strcpy(playerString, "Player ");
        strcat(playerString, itoa(i, buffer, 10));
        addPlayer(players, i, 0, getNextAvailableColor(players, i - 1), i - 1, playerString);
    }
    for(; i < playerCount + aiCount + 1; i++)
        addPlayer(players, i, 1, getNextAvailableColor(players, i - 1), i - 1, getNextAvailableName(players, i - 1));
}

/****
    * This function return the next available color for a particular player.
    *
    * Accepts:  A pointer to an array of player structures;
    *           The size of the array above.
    *
    * Returns:  The next available colorId.
    *
    * Note:     Stalls if there are no colors available;
    *           Will get slow on picking a color when options decrease. (random picks)
****/
int getNextAvailableColor(player **players, int count)
{
    int suggestedColor;
    int done = 0;
    int i;

    while(!done)
    {
        suggestedColor = getRandom(MAX_COLORS, 9);

        if(count < 1)
            done = 1;

        for(i = 0; i < count && suggestedColor != (int)(*players + i)->color; i++)
            if(i == count - 1)
                done = 1;

        Sleep(1);   // (Partly artf1027)
    }

    return suggestedColor;
}

/****
    * This function return the next available name for a particular player.
    *
    * Accepts:  A pointer to an array of player structures;
    *           The size of the array above.
    *
    * Returns:  The next available name.
    *
    * Note:     Will get stuck in a loop if there are no names available;
    *           Will get slow on picking a name when options decrease. (random picks)
****/
char* getNextAvailableName(player **players, int count)
{
    static char *playerNames[] = {"Jacob", "Emily", "Michael", "Isabella", "Ethan", "Emma", "Joshua", "Ava", "Daniel", "Madison", "Christopher", "Sophia"};
    int suggestedName;
    int done = 0;
    int i;

    while(!done)
    {
        suggestedName = getRandom(PLAYER_NAMES_COUNT, 9);

        if(count < 1)
            done = 1;

        for(i = 0; i < count && playerNames[suggestedName] != (*players + i)->humanoidName; i++)
            if(i == count - 1)
                done = 1;

        Sleep(1);   // (Partly artf1027)
    }

    return playerNames[suggestedName];
}

/****
    * This function will dynamicly add a player to an existing array.
    *
    * Accepts:  A pointer to an array of player structures;
    *           The id of the player to be added;
    *           Whether the player is Ai-controlled or not;
    *           The colorId of the player;
    *           The size of the array of player structures;
    *           The name of the player.
    *
    * Returns:  void.
****/
void addPlayer(player **players, int id, int AiControlled, int color, int playerCount, char *playerName)
{
    playerCount++;  //always provide one more space than current size!

    *players = realloc(*players, playerCount * sizeof(player));

    (*players + playerCount - 1)->id = id;
    (*players + playerCount - 1)->isAiControlled = AiControlled;
    (*players + playerCount - 1)->color = color;
    (*players + playerCount - 1)->humanoidName = playerName;
}

/****
    * This function will clean up the dynamicly allocated array of player structures.
    *
    * Accepts:  A pointer to an array of player structures;
    *           The amount of players.
    *
    * Returns:  void.
****/
void freePlayers(player **players, int count)
{
    int i;

    for(i = 0; i < count; i++)
        free((*players + i)->humanoidName);

    free(*players);
}

/****
    * This function gets the color of a specific player.
    *
    * Accepts:  A pointer to the array of players;
    *           The id from a player;
    *           The number of players.
    *
    * Returns:  > -1 The color of a player;
    *           -1 If the player id couldn't be found.
****/
int getColorFromPlayer(player **players, int id, int count)
{
    int i;

    for(i = 0; i < count; i++)
        if(id == (*players + i)->id)
            return (*players + i)->color;

    return -1;
}
