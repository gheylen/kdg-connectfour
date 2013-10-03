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

#include "game.h"
#include "console.h"
#include "ai.h"

#include <windows.h>
#include <stdio.h>

/****
    * This function clears the console and draws the game. (refresh)
    *
    * Accepts:  A pointer to a game struct.
    *
    * Returns:  void.
****/
void drawGame(game *game)
{
    //init
    int i, j;
    system("cls");

    //player names
    printf("%2s", " ");
    for(i = 0; i < game->playersCount; i++)
    {
        (game->playerActive == (game->players + i)->id ? printFormatted((game->players + i)->humanoidName, HIGHLIGHT) : printFormatted((game->players + i)->humanoidName, (game->players + i)->color));
        printf("%2s%c%2s"," ", '|', " ");
    }
    printf("\n");

    //header line
    for(i = 0; i < CONSOLE_WIDTH; i++)
        printf("-");
    printf("\n");

    //moveable top row
    for(i = 0; i < game->board.sizeX; i++)
    {
        if(game->columnActive == i)
            printFormatted("O", getColorFromPlayer(&game->players, game->playerActive, game->playersCount));
        else
            printf(" ");
        printf(" ");
    }
    printf("\n");

    //gameboard itself
    for(i = game->board.sizeY - 1; i > -1; i--)
    {
        for(j = 0; j < game->board.sizeX; j++)
        {
            if(*(*(game->board.data + j) + i) == 0)
                printf(". ");
            else
                printFormatted("O ", getColorFromPlayer(&game->players, *(*(game->board.data + j) + i) , game->playersCount));
        }
        printf("\n");
    }
}

/****
    * This function initializes and allocates memory for a new game.
    *
    * Accepts:  A pointer to a game;
    *           The width of the board;
    *           The height of the board;
    *           The amount of players joining the game;
    *           The amount of ai's playing.
    *
    * Returns:  void.
****/
void constructGame(game *game, int boardWidth, int boardHeight, int playerCount, int aiCount, int aiDif)
{
    game->columnActive = (int)(boardWidth / 2);
    game->playerActive = 1;
    game->playersCount = playerCount + aiCount;
    game->aiDif = aiDif;

    constructBoard(&game->board, boardWidth, boardHeight);
    constructPlayers(&game->players, playerCount, aiCount);
}

/****
    * This represents the mainloop for a single threaded game.
    *
    * Accepts:  A pointer to a game.
    *
    * Returns:  void.
****/
void loopGame(game *game)
{
    int won = 0;

    setConsoleTitle("ConnectFour");
    drawGame(game);
    resetAsyncKeyStates();  // (artf1030)


    while(!won && !isBoardFull(&game->board) && !isEscPressed())    // (artf1036)
    {
        Sleep(99);

        if(!isConsoleActive())
            continue;

        //Ai move?
        if((game->players + game->playerActive - 1)->isAiControlled)    // Why -1? -> Array counts from 0; 0 means "empty" on board, so players start to count from 1.
        {
            int action = getAction(game, game->playerActive, game->aiDif);

            while(game->columnActive < action)
            {
                Sleep(333);
                game->columnActive++;
                drawGame(game);
            }
            while(game->columnActive > action)
            {
                Sleep(333);
                game->columnActive--;
                drawGame(game);
            }

            dropElement(&game->board, game->columnActive, game->playerActive);
            nextPlayer(game);
            drawGame(game);
            resetAsyncKeyStates();  // (artf1034)
        }
        //Player move?
        else
        {
            if(isRightArrowPressed() && game->columnActive + 1 < game->board.sizeX)
            {
                game->columnActive++;
                drawGame(game);
            }
            if(isLeftArrowPressed() && game->columnActive - 1 > -1)
            {
                game->columnActive--;
                drawGame(game);
            }
            if(isDownArrowPressed() && !isColumnFull(&game->board, game->columnActive))
            {
                dropElement(&game->board, game->columnActive, game->playerActive);
                nextPlayer(game);
                drawGame(game);
            }
        }

        won = hasWon(&game->board);
    }

    if(isBoardFull(&game->board))
        printf("\nDraw: gameboard filled!");
    else if(won)    // Forgot an "else" (artf1028)
        printf("\n%s has won the game!", (game->players + won - 1)->humanoidName);

    printf("\n\n");
    system("PAUSE");
}

/****
    * This function clears the memory allocated by the game constructor.
    *
    * Accepts:  A pointer to a game.
    *
    * Returns:  void.
****/
void destructGame(game *game)
{
    freeBoard(&game->board);
    freePlayers(&game->players, game->playersCount);
}

/****
    * This function switches to the next player.
    *
    * Accepts:  A pointer to a game.
    *
    * Returns:  void.
****/
void nextPlayer(game *game)
{
    if(game->playerActive + 1 > game->playersCount)
        game->playerActive = 1;
    else
        game->playerActive++;
}
