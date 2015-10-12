/**
 * @file
 *
 * @brief Main function
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
 
#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>

#include <SDL.h>
#include <SDL_mixer.h>

#include "sdlInit.h"
#include "enemy.h"
#include "user.h"
#include "spriteFunctions.h"
//#include "game.h"

//Game music
Mix_Music *music = NULL;

int main(int argvc, char* argv[])
{
    //Quit flag for game loop
    bool quit = false;

    //Start up SDL, create window and renderer
    if( !sdlInit() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        try
        {
            //Load music
            music = Mix_LoadMUS( DATADIR "/audio/576220_Dante-Rabanow.mp3" ); 
            if( music == NULL ) 
            { 
                printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() ); 
            }
            //Play music
            Mix_PlayMusic( music, -1 );


            //Create player
            int spriteWidth  = 128;
            int spriteHeight = 64;
            unsigned int nSprites = 2;
            std::string filename = DATADIR "/graphics/ship.png";
            User player(spriteWidth, spriteHeight, nSprites, filename);
            
            //Allocate vector for enemies
            //Since we are not calling the constructor
            //This avoids loading sprites and actually wasting memory
            //Since the number of enemies is not constant
            std::vector<Enemy> enemies;

            // Initializes RNG
            std::default_random_engine generator;
            std::uniform_int_distribution<unsigned> distribution(1,100);
            

            //Game loop
            while(!quit)
            {
                //Event handling -------------------

                //SDL Event
                SDL_Event evt;
                while( SDL_PollEvent( &evt ) != 0 )
                {
                    //Closing window
                    if( evt.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }

                //Key states handling
                //N.B. we don't use "else if" otherwise we would
                //only register one key at a time! (i.e. no diagonal movement!)
                const Uint8* keyStates = SDL_GetKeyboardState( NULL );

                if( keyStates[ SDL_SCANCODE_UP ] )
                {
                    player.updatePosY(-5);
                }
                if( keyStates[ SDL_SCANCODE_DOWN ])
                {
                    player.updatePosY(5);
                }
                if( keyStates[ SDL_SCANCODE_LEFT ])
                {
                    player.updatePosX(-5);
                }
                if( keyStates[ SDL_SCANCODE_RIGHT ])
                {
                    player.updatePosX(5);
                }
                
                //Game logic ---------------------

                // Enforce boundary
                player.enforceBoundary();

                // Create enemy with a certain probability
                if (distribution(generator) < 4) 
                {
                    enemies.push_back(Enemy(spriteWidth, spriteHeight, nSprites, filename));

                    // randomize position
                    enemies.back().setPosX(distribution(generator) + 100);
                    enemies.back().setPosY(distribution(generator) + 100);
                }

                // Erase enemies if they leave screen
                for(int i = 0; i < enemies.size(); i++)
                {
                    if (enemies[i].getPosX() < 0)
                    {
                        enemies.erase (enemies.begin() + i);
                    }
                }
                // Check for collisions
                for(int i = 0; i < enemies.size(); i++)
                {
                    if ( spriteCollision(player, enemies[i]) )
                    {
                        std::cout << "Collision!";
                    }
                }
                //Update animation
                player.updateFrame();

                // Update enemies
                for (int i = 0; i < enemies.size(); i++)
                {
                    enemies[i].setPosX(enemies[i].getPosX() + enemies[i].getVX());
                    enemies[i].updateFrame();
                }

                // Check for collisions
                //TBD

                //Drawing ------------------------

                //Clear screen
                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                SDL_RenderClear( renderer );

                player.draw();

                // Draw enemies
                for(int i = 0; i< enemies.size(); i++)
                {
                    enemies[i].draw();
                }
                
                //Update screen
                SDL_RenderPresent( renderer );

            }
        }
        catch(...)
        {
            //Displays error message
            //SDL_MessageBoxData* msgData;
            //msgData->flags = SDL_MESSAGEBOX_INFORMATION;
            //msgData->message = "asdasd";
            //msgData->title = "";
            //msgData->colorScheme = NULL;
            //msgData->buttons = butarray;

            //int SDL_ShowMessageBox(SDL_MessageBoxData* msgData, int* buttonId);

            //Kill program, with exit code -1
            return -1;
        }

        return 0;
    }
}
