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

#ifndef _GAME_H_
#define _GAME_H_

#include "player.h"
#include "board.h"

/****
    * New value type to group variables of a single game
****/
typedef struct{
	board board;
	player *players;
	int playersCount;
	int columnActive;
	int playerActive;
	int aiDif;
} game;

void drawGame(game*);
void constructGame(game*, int, int, int, int, int);
void loopGame(game*);
void destructGame(game*);
void nextPlayer(game*);

#endif
