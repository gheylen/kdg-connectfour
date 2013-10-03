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

#include "board.h"
#include "random.h"

#include <windows.h>

/****
    * Determines if a column is filled or not.
    *
    * Accepts:  A pointer to the gameboard;
    *           The ID of the column;
    *
    * Returns:  1 if a column specified is full;
    *           0 if a column specified isn't full.
****/
int isColumnFull(board *board, int column)
{
    int i;

    for (i = 0; i < board->sizeY; i++)
        if (*(*(board->data + column) + i) == 0)
            return 0;
    return 1;
}

/****
    * Determines whether the board is filled or not.
    *
    * Accepts:  A pointer to the gameboard;
    *
    * Returns:  1 if a gameboard is full;
    *           0 if a gameboard isn't full.
****/
int isBoardFull(board *board)
{
    int i;

    for(i = 0; i < board->sizeX; i++)
        if(!isColumnFull(board, i))
            return 0;
    return 1;
}

/****
    * This function frees the allocated heap for the gameboard.
    *
    * Accepts:  A pointer to a gameboard.
    *
    * Returns:  void.
****/
void freeBoard(board *board)
{
    int i;
    for (i = 0; i < board->sizeX; i++)
        free(*(board->data + i));

    free(board->data);
}

/****
    * This is a constructor for the gameboard.
    *
    * Accepts:  A pointer to a gameboard;
    *           The width;
    *           The Height.
    *
    * Returns:  void.
    *
    * Note: Sets all cells to zero.
****/
void constructBoard(board *board, int width, int height)
{
    int i, j;

    board->sizeX = width;
    board->sizeY = height;
    board->data = NULL;

    //alloc pointer array to x pointers
    board->data = malloc(board->sizeX * sizeof(int*));
    //alloc for each pointer enough space to store y int's
    for (i = 0; i < board->sizeX; i++)
        *(board->data + i) = malloc(board->sizeY * sizeof(int));

    //init to zero
    for (i = 0; i < board->sizeX; i++)
        for (j = 0; j < board->sizeY; j++)
            *(*(board->data + i) + j) = 0;
}

/****
    * One big "Has any player won yet?"-function. Every check in one function
    * because there is no need for individual calls.
    *
    * Works 100% with dynamicly alloc'd memory: custom boardsizes supported.
    *
    * Accepts:  A pointer to a gameboard;
    *
    * Returns:  The player ID which has won or;
    *           0 is nobody has won just yet.
    *
    * Note: Not using buffervars to shorten the function && to minimalize memory usage.
****/
int hasWon(board *board)
{
    int i;

    //check horizantal
    for (i = 0; i < board->sizeY; i++)
        if (wonHelperMethod(board->data, 0, i, 1, 0, board->sizeX - 1))
            return wonHelperMethod(board->data, 0, i, 1, 0, board->sizeX - 1);

    //check vertical
    for (i = 0; i < board->sizeX; i++)
        if (wonHelperMethod(board->data, i, 0, 0, 1, board->sizeY - 1))
            return wonHelperMethod(board->data, i, 0, 0, 1, board->sizeY - 1);

    //start from 3(+1) (can't connect four with less than four elements on each direction)
    //this isn't a "speedy" return; diagonal checks run on artifacts if this block is removed
    if (board->sizeX < 4 || board->sizeY < 4)
        return 0;

    //check diagonal "left up corner" to "right corner down"
    for (i = 3; i < board->sizeY; i++)
    {
        if(i >= board->sizeX)
            if (wonHelperMethod(board->data, 0, i, 1, -1, board->sizeX - 1))
                return wonHelperMethod(board->data, 0, i, 1, -1, board->sizeX - 1);
        if(i < board->sizeX)
            if (wonHelperMethod(board->data, 0, i, 1, -1, i))
                return wonHelperMethod(board->data, 0, i, 1, -1, i);
    }
    for(i = 1; i < board->sizeX - 3; i++)  //absolute corner has been checked; skip (i = 1)
        if (wonHelperMethod(board->data, i, board->sizeY - 1, 1, -1, board->sizeX - i - 1))
            return wonHelperMethod(board->data, i, board->sizeY - 1, 1, -1, board->sizeX - i - 1);

    //check diagonal "right up corner" to "left corner down"
    for (i = 3; i < board->sizeY; i++)
    {
        if(i >= board->sizeX)
            if (wonHelperMethod(board->data, board->sizeX - 1, i, -1, -1, board->sizeX - 1))
                return wonHelperMethod(board->data, board->sizeX - 1, i, -1, -1, board->sizeX - 1);
        if(i < board->sizeX)
            if (wonHelperMethod(board->data, board->sizeX - 1, i, - 1, -1, i))
                return wonHelperMethod(board->data, board->sizeX - 1, i, - 1, -1, i);
    }
    for(i = board->sizeX - 2; i > 2; i--)  //absolute corner has been checked; skip (i = maxX - 2)
        if (wonHelperMethod(board->data, i, board->sizeY - 1, -1, -1, i))
            return wonHelperMethod(board->data, i, board->sizeY - 1, -1, -1, i);

    return 0;
}

/****
    * Runs one check in a specified direction. It's unaware of the
    * board's dimensions.
    *
    * Accepts:  A pointer to the actual gameboard;
    *           The startpoint on the X - axis;
    *           The startpoint on the Y - axis;
    *           The incrementValue of the X - value;
    *           The incrementValue of the Y - value;
    *           The number of times to loop.
    *
    * Returns:  The player ID which has won or;
    *           0 is nobody has won (just yet).
    *
    * Note: Helper function. Dependancy of "hasWon(board *board)".
****/
int wonHelperMethod(int **data, int x, int y, int deltaX, int deltaY, int count)    //using array notation to make it more obvious
{
    int same = 0, i;

    for (i = 0; i < count; i++)
    {
        if (data[x][y] == data[x + deltaX][y + deltaY] && data[x][y] > 0)
        {
            same++;
            if (same == 3) //alright! 4 (3+1) on a row!
                return data[x][y];
        }
        else
            same = 0;

        x += deltaX;
        y += deltaY;
    }

    return 0;
}

/****
    * This drops a game-element in a specific column. It does nothing
    * if a column is filled already.
    *
    * Accepts:  A pointer to the gameboard;
    *           The ID of the column;
    *           The player id.
    *
    * Returns:  void.
****/
void dropElement(board *board, int column, int player)
{
    int i;

    for (i = 0; i < board->sizeY; i++)
        if (*(*(board->data + column) + i) == 0)
        {
            *(*(board->data + column) + i) = player;
            break;
        }
}

/****
    * This removes the last game-element from a specified column.
    * It does nothing if there is nothing to be replaced by a zero.
    *
    * Accepts:  A pointer to the gameboard;
    *           The ID of the column;
    *
    * Returns:  void.
****/
void removeElement(board *board, int column)
{
    int i;

    for (i = board->sizeY - 1; i > -1; i--)
        if (*(*(board->data + column) + i) != 0)
        {
            *(*(board->data + column) + i) = 0;
            break;
        }
}

/****
    * This method returns the next available column.
    *
    * Accepts:  A pointer to the gameboard;
    *
    * Returns:  The next available column;
    *           -1 if none was found.
    *
    * Note: Shouldn't be called if board is full.
****/
int getNextAvailableColumn(board *board)
{
    int i, direction = getRandom(2, 3);

    for(i = (direction > 0 ? board->sizeX - 1 : 0); (direction > 0 ? i > -1 : i < board->sizeX); (direction > 0 ? i-- : i++))
        if(!isColumnFull(board, i))
            return i;

    return -1;
}
