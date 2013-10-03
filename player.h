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

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "color.h"

#define PLAYER_NAMES_COUNT 12

/****
    * New value type to group variables of a single player.
****/
typedef struct{
	char *humanoidName;
	int id;
	int isAiControlled;
	enum color color;
} player;

void constructPlayers(player**, int, int);
int getNextAvailableColor(player**, int);
char* getNextAvailableName(player**, int);
void addPlayer(player**, int, int, int, int, char*);
void freePlayers(player**, int);
int getColorFromPlayer(player**, int, int);

#endif
