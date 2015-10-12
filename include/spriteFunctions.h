/**
 * @file
 *
 * @brief Functions for dealing with sprites that didn't make it as methods of the sprite
 * class.
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

#ifndef SPRITE_FUNCTIONS_H
#define SPRITE_FUNCTIONS_H

#include "sprite.h"

/**
 * @brief Pixel step used in per-pixel collisions
 * Setting it too low will slow down things.
 * Setting it too high will defeat the purpose of
 * using this kind of collision.
 * 
 */
#define PIXEL_STEP 30

// Check for collision
bool spriteCollision(Sprite sprite_1, Sprite sprite_2);

// Get pixel color
SDL_Color getPixel(SDL_Surface *surface, int x, int y);

// Check whether pixel is black
bool isBlack(SDL_Surface *surface, int x, int y);

#endif
