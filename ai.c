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

/****
    * Note: This AI works well up to mediocre level. The structure is very limited.
    *       More advanced checks will be hard to implement unless structure is reviewed.
    *       (Using an array to store "last moves" and a method to "undo last moves" will
    *       help. (e.g.: "void undoMoves(moves *moves, int count);"))
****/

#include "game.h"
#include "ai.h"
#include "random.h"

#include <windows.h>

/****
    * This is the "entry point" for functions outside this file. Use the "depth" parameter
    * to specify the AI's intelligence.
    *
    * Accepts:  A pointer to a game struct;
    *           The id of the current active player;
    *           The intelligence of the AI (depth):
    *               1: Easy;
    *               2: Medium;
    *               3: Expert; (Not included "yet" in this revision: Should learn more about FourOnARow before programming an artifact to play as an expert)
    *               Other: Random.
    *
    * Returns: The column integer value which has been picked by the AI.
    *
    * Note: Should never be called if board is full!
****/
int getAction(game *game, int playerId, int depth)
{
    int i, action, direction;

    // Calculated moves
    if(depth > 0)
    {
        action = getElementaryAction(game, playerId);
        if(action > -1)
            return action;
    }
    if(depth > 1)
    {
        action = getDeeperAction(game, playerId);
        if(action > -1)
            return action;
    }

    // Randomized moves (Why so many lines for a random move? Still want to return an "optimized" random. It should be "save" for starters..)
    for(i = 0; i < 33; i++)
    {
        action = getRandom(game->board.sizeX, 9);
        if(!isColumnFull(&game->board, action) && isSaveMove(game, action, playerId))
            return action;

        Sleep(1);   // (Partly artf1027)
    }
    direction = getRandom(2, 3);
    for(i = (direction > 0 ? game->board.sizeX - 1 : 0); (direction > 0 ? i > -1 : i < game->board.sizeX); (direction > 0 ? i-- : i++))
        if(!isColumnFull(&game->board, i) && isSaveMove(game, i, playerId))
            return i;
    for(i = (direction > 0 ? game->board.sizeX - 1 : 0); (direction > 0 ? i > -1 : i < game->board.sizeX); (direction > 0 ? i-- : i++)) // (artf1029)
        if(!isColumnFull(&game->board, i))
            return i;

    // NEVER comes down here (Bad function structure? Not sure. This works well and it's relatively short.)
    return 0;
}

/****
    * This module of the AI handles two simple and elementary checks:
    *   Can active ID win by a single action?
    *   Is there anyone else who is winning to block?
    *
    * Accepts:  A pointer to a game;
    *           The id of a player which is calling AI.
    *
    * Returns:  -1 if there is no "win" - situation found;
    *           Other(columnid) if an elementary move should be done.
****/
int getElementaryAction(game *game, int playerId)
{
    int i, column;

    // Can we win by a single move? Great!
    column = canWinInstantly(game, playerId);
    if(column > -1)
        return column;

    // Check whether someone else can win by a single move or not. Eliminate first danger, even if it's not a savemove.
    for(i = 1; i < game->playersCount + 1; i++)
    {
        column = canWinInstantly(game, i);
        if(column > -1)
            return column;
    }

    return -1;
}

/****
    * This module does the same as the first, it only checks deeper:
    *   Is there anyone else who is winning in two actions to block?
    *   Can active ID win by two actions?
    *
    * Accepts:  A pointer to a game;
    *           The id of a player which is calling AI.
    *
    * Returns:  > -1 if a "better" move can be played;
    *           -1 if there is nothing special going on.
****/
int getDeeperAction(game *game, int playerId)
{
    int i, closeWin;

    for(i = 1; i < game->playersCount + 1; i++)
    {
        if(playerId == i)   //skip self
            continue;

        closeWin = canWinAlmost(game, i);
        if(closeWin > -1 && isSaveMove(game, closeWin, playerId))
            return closeWin;
    }

    closeWin = canWinAlmost(game, playerId);
    if(closeWin > -1 && isSaveMove(game, closeWin, playerId))
        return closeWin;

    return -1;
}

/****
    * This module checks if it is possible to win in 2 steps.
    *
    * Accepts:  A pointer to a game;
    *           The ID of a player.
    *
    * Returns:  > 0 if a good move can be done;
    *           -1 if there is no "win" - situation was found in several moves.
    *
    * Note: Shouldn't come down to this function if anyone can win instantly;
    *       Uses a random direction to make it less obvious. (left<->right)
****/
int canWinAlmost(game *game, int playerId)
{
    int i, column, direction = getRandom(2, 3);

    for(i = (direction > 0 ? game->board.sizeX - 1 : 0); (direction > 0 ? i > -1 : i < game->board.sizeX); (direction > 0 ? i-- : i++))
    {
        if(isColumnFull(&game->board, i))
            continue;

        dropElement(&game->board, i, playerId);
        column = canWinInstantly(game, playerId);
        removeElement(&game->board, i);

        if(column > -1)
            return i;
    }

    return -1;
}

/****
    * Determines whether a move is save to play or not. An unsave move makes
    * someone else win the game, which it's ment to be.
    *
    * Accepts:  A pointer to a game;
    *           A specific column;
    *           The ID of a player.
    *
    * Returns:  1 if the move specified (column) is save or;
    *           0 if the move specified creates a win-situation for another player.
****/
int isSaveMove(game *game, int column, int playerId)
{
    int i, won, save = 1;

    if(isColumnFull(&game->board, column))
        return 1;

    dropElement(&game->board, column, playerId);
    for(i = 1; i < game->playersCount + 1; i++)
    {
        if(playerId == i)
            continue;

        won = canWinInstantly(game, i);
        if(won > -1)
        {
            save = 0;
            break;
        }
    }
    removeElement(&game->board, column);

    return save;
}

/****
    * Determines if it's possible to win instantly by doing a single element drop. (Helper)
    *
    * Accepts:  A pointer to a game;
    *           The ID of a player.
    *
    * Returns:  -1 if the player with id "playerId" can't win by a single action (-1 because 0 is a column);
    *           The column number if the player with id "playerId" can win by a single action.
****/
int canWinInstantly(game *game, int playerId)
{
    int i, haswon;

    for(i = 0; i < game->board.sizeX; i++)
    {
        if(isColumnFull(&game->board, i))
            continue;

        dropElement(&game->board, i, playerId);
        haswon = hasWon(&game->board);
        removeElement(&game->board, i);

        if(haswon)
            return i;
    }

    return -1;
}
