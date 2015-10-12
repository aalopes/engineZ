/**
 * @file
 *
 * @brief Header user.cpp
 *
 * @class Class for the user - it has some basic properties
 *        such as position, speed, health and a spritesheet 
 *        corresponding to its animation.
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
 * (at your option) any later version.
 *
 * EngineZ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EngineZ. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef USER_H
#define USER_H

#include "sprite.h"

class User: public Sprite 
{
    public:

        // Constructor
        User(int width, int height, int nSprites, std::string filename);

        // Destructor
        ~User();

        // Get HP
        int getHP();

        // Set HP
        bool setHP(int hp);

    private:
        // Ammount of HP
        int mHP;
};
#endif
