/**
 * @file
 *
 * @brief Defines class dealing with sprites
 *
 * @author Alexandre Lopes
 *
 * @tbd updatePos - updates position by x pixels
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
 * You should have received a copy of the GNU General Public License
 * along with EngineZ. If not, see <http://www.gnu.org/licenses/>.
 */

#include "sprite.h"

/**
 * @class Class for sprites. All collidable objects, which are sprites, should
 * be instances of a class derived from this one.
 */
Sprite::Sprite(int width, int height, int nSprites, std::string filename)
{
    // Initialization
    mWidth    = width;
    mHeight   = height;
    mNSprites = nSprites;

    // Default values
    mPosX  = 0;
    mPosY  = 0;
    mVX    = 0;
    mVY    = 0;
    mFrame = 1;

    // Load sprite sheet
    mSprtSheet = loadSpriteSheet(filename);

    // Load mask
    mMask = loadMask(filename);
}

// Destructor
Sprite::~Sprite()
{

}

/**
 * @brief Get sprite position
 */
std::pair<int, int> Sprite::getPos() const
{
    std::pair<int, int> pos;
    pos = std::make_pair(mPosX, mPosY);

    return pos;
}

/**
 * @brief Get sprite X position
 */
int Sprite::getPosX() const
{
    return mPosX;
}

/**
 * @brief Get sprite Y position
 */
int Sprite::getPosY() const
{
    return mPosY;
}

/**
 * @brief Get sprite speed
 */
std::pair<int, int> Sprite::getV() const
{
    std::pair<int, int> v; 
    v = std::make_pair(mPosX, mPosY);

    return v;
}


/**
 * @brief Get sprite speed x direction
 */
int Sprite::getVX() const
{
    return mVX;
}


/**
 * @brief Get sprite speed y direction
 */
int Sprite::getVY() const
{
    return mVY;
}

/**
 * @brief Set sprite position
 */
void Sprite::setPos(int x, int y)
{
   mPosX = x;
   mPosY = y;
}

/**
 * @brief Set sprite position in the x direction
 */
void Sprite::setPosX(int x)
{
   mPosX = x;
}

/**
 * @brief Set sprite position in the y direction
 */
void Sprite::setPosY(int y)
{
   mPosY = y;
}

/**
 * @brief Set sprite speed
 */
void Sprite::setV(int vX, int vY)
{
    mVX = vX;
    mVY = vY;
}


/**
 * @brief Set sprite speed in the x direction
 */
void Sprite::setVX(int vX)
{
    mVX = vX;
}

/**
 * @brief Set sprite speed in the y direction
 */
void Sprite::setVY(int vY)
{
    mVY = vY;
}


/**
 * @brief Update sprite X position by a given number of pixels
 */
void Sprite::updatePosX(int x)
{
    mPosX += x;
}

/**
 * @brief Update sprite Y position by a given number of pixels
 */
void Sprite::updatePosY(int y)
{
    mPosY += y;
}

/**
 * @brief Update sprite according to speed
 */
void Sprite::updatePos()
{
    mPosX += mVY;
    mPosY += mVX;
}

/**
 * @brief Draw sprite to screen
 */
void Sprite::draw()
{
    // Draw sprite from sprite sheet corresponding to the current fram to the screen 
    // at the current sprite position

    //Clipping - grabbing the correct sprite from sheet
    SDL_Rect spriteLimits;
    spriteLimits.x = mWidth*mFrame;
    spriteLimits.y = 0;
    spriteLimits.w = mWidth*(mFrame+1);
    spriteLimits.h = mHeight;

    //Render sprite to the right position

    // The rectangle where we'll render to
    SDL_Rect renderQuad = { mPosX, mPosY, mPosX+mWidth, mPosY + mHeight }; 

    // Set clip rendering dimensions 
    renderQuad.w = mWidth; 
    renderQuad.h = mHeight; 


    // Render to screen 
    SDL_RenderCopy( renderer, mSprtSheet, &spriteLimits, &renderQuad );
}

/**
 * @brief Update current animation frame to a desired frame
 */
void Sprite::updateFrame(unsigned int frame)
{
    // Throw exception whenever nSprites = 0
    if (0 == mNSprites)
    {
        throw std::length_error(" Number of sprites in sheet %s is 0! Cannot increment frame!");
    }
    else
    {
        // Use modular arithmetic, so it wraps around
        mFrame = frame % mNSprites ;
    }
}

/**
 * @brief Update current animation frame to the next frame
 */
void Sprite::updateFrame()
{
    int frame = mFrame + 1;
    // Throw exception whenever nSprites = 0
    if (0 == mNSprites)
    {
        throw std::length_error(" Number of sprites in sheet %s is 0! Cannot increment frame!");
    }
    else
    {
        // Use modular arithmetic, so it wraps around
        mFrame =  frame % mNSprites;
    }
}

/**
 * @brief Put sprite back into screen if it left it
 */
void Sprite::enforceBoundary()
{
    if (mPosX < 0)
    {
        mPosX = 0;
    }
    else if (mPosX > WINDOW_WIDTH - mWidth)
    {
        mPosX = WINDOW_WIDTH - mWidth;
    }

    if (mPosY < 0)
    {
        mPosY = 0;
    }
    else if (mPosY > WINDOW_HEIGHT - mHeight)
    {
        mPosY = WINDOW_HEIGHT - mHeight;
    }
}

/**
 * @brief Load sprite sheet
 */
SDL_Texture* Sprite::loadSpriteSheet(std::string filename)
{
	 //Texture
	SDL_Texture* texture = NULL; 

	//First we load surface
	SDL_Surface* surface = IMG_Load( filename.c_str() ); 
	if( surface == NULL ) 
	{ 
		printf( "Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError() ); 
	} 
	else 
	{ 
		//Set color key (for transparency)
		SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, COLOR_KEY[0], 
			             COLOR_KEY[1], COLOR_KEY[2] ) );
		//Create texture from surface
		texture = SDL_CreateTextureFromSurface( renderer, surface ); 
		if( texture == NULL ) { 
			printf( "Unable to create texture from %s! SDL Error: %s\n", filename.c_str(), SDL_GetError() );
		} 
		//Get rid of old loaded surface 
		SDL_FreeSurface( surface ); 
	} 

	return texture;
}

/**
 * @brief Load collision mask
 * The bonding box will be taken to be the size of the loaded sprite
 * This should, however, be overridable, in case the actual object
 * is much smaller than the loaded sprite
 *
 * @tbd Make bounding box size overridable
 */
SDL_Surface* Sprite::loadMask(std::string filename)
{
	SDL_Surface* surface = IMG_Load( filename.c_str() ); 
	if( surface == NULL ) 
	{ 
		printf( "Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError() ); 
	} 
	else 
	{ 
		//Set color key (for transparency)
		SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, COLOR_KEY[0], 
			             COLOR_KEY[1], COLOR_KEY[2] ) );
    }
    return surface;
}

/**
 * @brief Gets mask
 * Returns a pointer to an SDL_Surface struct
 *
 */
SDL_Surface* Sprite::getMask() const
{
    return mMask;
}

