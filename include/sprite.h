/**
 * @file
 *
 * @brief Defines class dealing with sprites
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

#ifndef SPRITE_H
#define SPRITE_H

#include <stdexcept>
#include <utility>

#include <SDL.h>
#include <SDL_image.h>

#include "global.h"

class Sprite
{
    public:

        // Constructor
        // Since we will be loading a sprite sheet, we need
        // to know the height and width of every sprite,
        // the number of sprites in the sheet and the filename
        // of the sheet
        Sprite(int width, int height, int nSprites, std::string filename);

        // Destructor
        ~Sprite();

        // Get position (x,y)
        std::pair<int, int> getPos() const;

        // Get X position
        int getPosX() const;

        // Get Y position
        int getPosY() const;

        // Get speed (vx, vy)
        std::pair<int, int> getV() const;

        // Get x speed
        int getVX() const;

        // Get y speed
        int getVY() const;

        // Get mask
        SDL_Surface* getMask() const;

        // Set sprite position
        void setPos(int x, int y);

        // Set sprite x position
        void setPosX(int x);

        // Set sprite y position
        void setPosY(int y);

        // Set sprite speed
        void setV(int vX, int vY);

        // Set sprite x speed
        void setVX(int vX);

        // Set sprite y speed
        void setVY(int vY);

        // Update sprite X position by a given number of pixels
        void updatePosX(int x);

        // Update sprite Y position by a given number of pixels
        void updatePosY(int y);

        // Update sprite according to the velocity
        // x <- x + vx
        // y <- y + vy
        void updatePos();

        // Set speed
        void setSpeed(int vx, int vy);

        // Draw current sprite to screen
        void draw( );

        // Update sprite animation by a certain number of frames
        void updateFrame(unsigned int frame);

        // Update sprite animation exactly one frame
        void updateFrame();

        // Puts sprite back into the screen if it left it
        void enforceBoundary();

        
    private:
        //@{
        /*
            mHeight    - height of sprite sprite
            mWidth     - width of sprite sprite
            mPosX      - x position of sprite
            mPosY      - y position of sprite
            mVX        - x velocity of sprite
            mVY        - y velocity of sprite
            mFrame     - frame number (Note: first frame is = 0. The last one is = nSprites - 1)
            mNSprites  - number of sprites of the sprite
            mSprtSheet - a pointer to the loaded sprite sheet (SDL_Texture)
            mMask      - a pointer to the loaded mask (SDL_Surface)
         */
        int mHeight, mWidth;
        int mPosX, mPosY, mVX, mVY;
        unsigned int mFrame, mLife;
        unsigned int mNSprites;
        SDL_Texture* mSprtSheet;
        SDL_Surface* mMask;
        //@}

        // Loads sprite sheet
        SDL_Texture* loadSpriteSheet(std::string filename);

        // Loads mask 
        SDL_Surface* loadMask(std::string filename);

};
#endif
