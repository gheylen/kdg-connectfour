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

#ifndef _BOARD_H_
#define _BOARD_H_

/****
    * New value type to group variables of board
****/
typedef struct{
	int **data;
	int sizeX;
	int sizeY;
} board;

int isColumnFull(board*, int);
int isBoardFull(board*);
void freeBoard(board*);
void constructBoard(board*, int, int);
int hasWon(board*);
int wonHelperMethod(int**, int, int, int, int, int);
void dropElement(board*, int, int);
void removeElement(board*, int);
int getNextAvailableColumn(board*);

#endif
