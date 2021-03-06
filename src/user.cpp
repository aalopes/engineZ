/**
 * @file
 *
 * @brief Defines class for holding user data
 *
 * @author Alexandre Lopes
 *
 * @copyright (c) 2015 Alexandre Lopes. This project is released under the GNU Public License.
 *
 */

/* This file is part of EngineZ.
 *
 * EngineZ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.s
 *
 * EngineZ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 * along with EngineZ.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "user.h"


// Constructor
User::User(int width, int height, int nSprites, std::string filename)
     :Sprite(width, height, nSprites, filename)
{
    //Default values
    mHP  = 100;
}

//Destructor
User::~User()
{

}

/**
 * @brief Get HP
 */
int User::getHP()
{
    return mHP;
}

/**
 * @brief Set HP
 * Returns 1 if it falls under 0, 0 otherwise
 */
bool User::setHP(int hp)
{
    mHP = hp;    
    if (mHP < 0)
    {
        return 1;
    }

    return 0;
}
