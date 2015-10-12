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

#include "spriteFunctions.h"

/**
 * @brief Check two sprites for collisions
 *
 * @note Could be implemented as a method of the sprite class, sort of check for collisions
 * against _this_ sprite.
 */
bool spriteCollision(Sprite sprite_1, Sprite sprite_2)
{
    // Get Mask
    SDL_Surface* mask1 = sprite_1.getMask();
    SDL_Surface* mask2 = sprite_2.getMask();

    // Get all the needed data
    //   Bounding box size
    int sizeH_1 = mask1->h;
    int sizeW_1 = mask1->w;
    int sizeH_2 = mask2->h;
    int sizeW_2 = mask2->w;

    //  Position
    int posX_1 = sprite_1.getPosX();
    int posY_1 = sprite_1.getPosY();
    int posX_2 = sprite_2.getPosX();
    int posY_2 = sprite_2.getPosY();
    
    //   For ease of implementation, calculate length of rectangle edges
    //   Some of these assignments are useless but it makes the implementation
    //   cleaner
    int edgeLeft_1   = posX_1;
    int edgeTop_1    = posY_1;
    int edgeBottom_1 = posY_1 + sizeH_1;
    int edgeRight_1  = posX_1 + sizeW_1;
    int edgeLeft_2   = posX_2;
    int edgeTop_2    = posY_2;
    int edgeBottom_2 = posY_2 + sizeH_2;
    int edgeRight_2  = posX_2 + sizeW_2;

    // First check for collision of the bounding box
    int xOverlap = std::max(0, std::min(edgeRight_1,  edgeRight_2)  - std::max(edgeLeft_1, edgeLeft_1));
    int yOverlap = std::max(0, std::min(edgeBottom_1, edgeBottom_2) - std::max(edgeTop_1,  edgeTop_2));
    

    // Then check for collisions on a per-pixel basis, but do not iterate over all pixels.
    if ((xOverlap != 0) && (yOverlap != 0))
    {
        // Top-left corner of intersecting rectangle
        int xInter = std::max(posX_1, posX_2);
        int yInter = std::max(posY_1, posY_2);

        // iterate only over overlapping pixels - with a certain PIXEL_STEP
        for (int x = xInter; x < xInter + xOverlap; x += PIXEL_STEP)
        {
            for (int y = yInter; y < yInter + yOverlap; y += PIXEL_STEP)
            {
                if( isBlack(mask1, x, y) && isBlack(mask2, x, y))
                    return true;
            }
        }
        // test only bounding box
        return true;
    } 
    return false;
}

/**
 * @brief Get pixel color of SDL surface for pixel at (x,y)
 * @return An SDL_Color struct
 *
 * @note If alpha is needed, SDL_GetRBGA should be used instead.
 */
SDL_Color getPixel(SDL_Surface *surface, int x, int y)
{
    // Pixel RGB color
    Uint8 r ;
    Uint8 g ;
    Uint8 b ;
    SDL_Color color;

    // Get pixel coordinate (pixels are stored as a 1D array)
    Uint32 pixel = *( ( Uint32* )surface->pixels + y * surface->w + x ) ;

    // Get color
    SDL_GetRGB( pixel, surface->format ,  &r, &g, &b );
    color.r = r; // red
    color.g = g; // green
    color.b = b; // blue
    color.a = 0; // alpha - we won't be using this

    return color;

}


/**
 * @brief Detect if pixel is black
 *
 * @return 1 if black, 0 otherwise
 *
 */
bool isBlack(SDL_Surface *surface, int x, int y)
{

    SDL_Color color = getPixel(surface, x, y);

    if ( (color.r == 0)&& (color.g == 0) && (color.b == 0) )
    {
        return true;
    } 
    else
    {
        return false;
    }
}
