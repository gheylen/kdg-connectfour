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

#include "random.h"

#include <stdlib.h>
#include <time.h>

/****
    * A randomize function. So why another if it exists?
    *   Everything in one single function instead of two: srand & rand;
    *   "More random" "random number": possibility to seed multiple times;
    *   Less headerfiles to include: time.h, stdlib.h, etc.
    *
    * Accepts:  The limit of the random number requested;
    *           The amount of seeding times before returned.
    *
    * Returns:  The random number obtained.
    *
    * Note: Two files for one function? I think it is worth it.
****/
int getRandom(int limit, int seedingCount)
{
    int i, random;

    srand(time(NULL));
    random = rand();

    for(i = 0; i < seedingCount; i++)
    {
        srand(random);
        random = rand();
    }

    return random % limit;
}
