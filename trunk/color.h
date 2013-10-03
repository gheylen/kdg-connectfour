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

#ifndef _COLOR_H_
#define _COLOR_H_

#define MAX_COLORS 13

/****
    * Enumeration with possible colors.
    *
    * Note: this also virtually defines the max-limit of different players on the gameboard.
    *       Signed values are abstract colors.
****/
enum color
{
    RESET = -2,
    HIGHLIGHT = -1,
    RED = 0,
    iPURPLE = 1,
    //BLUE = 1,
    GREEN = 2,
    YELLOW = 3,
    WHITE = 4,
    BLUE_GREEN = 5,
    PURPLE = 6,
    iRED = 7,
    iGREEN = 8,
    iBLUE = 9,
    iYELLOW = 10,
    iWHITE = 11,
    iBLUE_GREEN = 12
};

#endif

