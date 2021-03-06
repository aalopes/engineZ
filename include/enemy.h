/**
 * @file
 *
 * @brief Header file for enemy.cpp
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

#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"

class Enemy: public Sprite
{
    public:

        // Constructor
        Enemy(int width, int height, int nSprites, std::string filename);

        // Destructor
        ~Enemy();

        // Get HP
        int getHP();

        // Set HP
        bool setHP(int hp);

    private:
        // Ammount of HP
        int mHP;
};
#endif
