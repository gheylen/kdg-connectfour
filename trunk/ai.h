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

#ifndef _AI_H_
#define _AI_H_

int getAction(game*, int, int);
int getElementaryAction(game*, int);
int getDeeperAction(game*, int);
int canWinAlmost(game*, int);
int isSaveMove(game*, int, int);
int canWinInstantly(game*, int);

#endif
